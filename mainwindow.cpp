#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->initForm();

    // 系统初始化
    InitSystem();

    //开启摄像头识别
    connect(&theTimer, SIGNAL(timeout()), this, SLOT(updateImage()));

    //显示日期时间
    connect(&local_timer, SIGNAL(timeout()), this, SLOT(updatetime()));

}

MainWindow::~MainWindow()
{
    if(capture.isOpened())
        capture.release();

    theTimer.stop();
    local_timer.stop();
    bg_movie->stop();

    delete ui;
}

void MainWindow::InitSystem()   // 系统初始化
{
    //加载模型
    mtcnn.Set_model_path("model");
    cout<<"已加载mtcnn模型"<<endl;

    mobilefacenet.Set_model_path("model");
    cout<<"已加载mobilefacenet模型"<<endl;

    //加载数据库
    CreatDb();
    OpenDb();
    //CreateTable();
\
    //加载背景图
    bg_movie = new QMovie("image/bg.gif");
    ui->label_show->setMovie(bg_movie);
    ui->label_show_2->setMovie(bg_movie);
    bg_movie->start();

    cv::Mat Image = cv::imread("image/facebg.jpg");
    cv::cvtColor(Image, Image, CV_BGR2RGB);
    QImage Img = QImage((const unsigned char*)(Image.data),Image.cols,Image.rows,Image.step,QImage::Format_RGB888);
    facebg = QPixmap::fromImage(Img.scaled(ui->label_show_4->size(),Qt::KeepAspectRatio));//图片按比例缩放

    //初始化界面
    ui->stackedWidget->setCurrentWidget(ui->page);
    ui->label_show_4->setPixmap(facebg);
    ui->label_show_3->setPixmap(facebg);

    //初始化表格
    Init_table_recognition();
    Init_table_face();
    Init_table_record();

    //设置当前日期
    current_date_time =QDateTime::currentDateTime();
    current_date =current_date_time.toString("yyyy.MM.dd");
    //current_date =current_date_time.toString("yyyy.MM.dd hh:mm");
    ui->lineEdit_date->setText(current_date);

    //管理人脸，按id输入类型设置为int
    QValidator *validator=new QIntValidator(0,100000,this);
    ui->lineEdit_id->setValidator(validator);
    ui->lineEdit_id_2->setValidator(validator);
    ui->lineEdit_id_3->setValidator(validator);

    //显示日期时间
    local_timer.start(1000);

    //数据库人脸数据存储到内存中
    update_face_data();
    cout<<"数据库人脸数据存储到内存中"<<endl;

}

void MainWindow::initForm() //初始化主题
{
    on_action5_triggered();
}

void MainWindow::loadStyle(const QString &qssFile)  //加载qss文件
{
    //加载样式表
    QString qss;
    QFile file(qssFile);
    if (file.open(QFile::ReadOnly)) {
        //用QTextStream读取样式文件不用区分文件编码 带bom也行
        QStringList list;
        QTextStream in(&file);
        //in.setCodec("utf-8");
        while (!in.atEnd()) {
            QString line;
            in >> line;
            list << line;
        }

        file.close();
        qss = list.join("\n");
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(paletteColor));
        qApp->setStyleSheet(qss);
    }
}

void MainWindow::Init_table_recognition()  //初始化人脸识别表格
{
    this->model = new QStandardItemModel;   //创建一个标准的条目模型
    this->ui->tableView->setModel(model);   //将tableview设置成model这个标准条目模型的模板, model设置的内容都将显示在tableview上

    this->model->setHorizontalHeaderItem(0, new QStandardItem("序号") );
    this->model->setHorizontalHeaderItem(1, new QStandardItem("id"));
    this->model->setHorizontalHeaderItem(2, new QStandardItem("姓名"));
    this->model->setHorizontalHeaderItem(3, new QStandardItem("校园码"));
    this->model->setHorizontalHeaderItem(4, new QStandardItem("日期时间"));
    this->model->setHorizontalHeaderItem(5, new QStandardItem("准确率%"));

    this->ui->tableView->setColumnWidth(0, 50);    //设置列的宽度
    this->ui->tableView->setColumnWidth(1, 100);
    this->ui->tableView->setColumnWidth(2, 100);
    this->ui->tableView->setColumnWidth(3, 100);
    this->ui->tableView->setColumnWidth(4, 200);
    this->ui->tableView->setColumnWidth(5, 70);

    ui->tableView->verticalHeader()->setVisible(false);//显示或隐藏序列行
    ui->tableView->setAutoScroll(true);//自动滚动条
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
}

void MainWindow::add_table_recognition(int col,int id,QString name,QString code,QString datetime,double distance)  //人脸识别表格记录增加
{
    /*setItem设置条目栏中的一个格子的信息*/
    this->model->setItem(col, 0, new QStandardItem(QString::number(col + 1)));
    this->model->setItem(col, 1, new QStandardItem(QString::number(id)));
    this->model->setItem(col, 2, new QStandardItem(name));
    this->model->setItem(col, 3, new QStandardItem(code));
    this->model->setItem(col, 4, new QStandardItem(datetime));
    this->model->setItem(col, 5, new QStandardItem(QString::number(distance,'f',2)));

    this->model->item(col, 0)->setTextAlignment(Qt::AlignCenter);
    this->model->item(col, 1)->setTextAlignment(Qt::AlignCenter);
    this->model->item(col, 2)->setTextAlignment(Qt::AlignCenter);
    this->model->item(col, 3)->setTextAlignment(Qt::AlignCenter);
    this->model->item(col, 4)->setTextAlignment(Qt::AlignCenter);
    this->model->item(col, 5)->setTextAlignment(Qt::AlignCenter);

    col_table_recognition +=1;

    ui->tableView->scrollToBottom();//保持滚动条在底部
}

void MainWindow::Init_table_face()  //初始化人脸数据库表
{
    this->model_face = new QStandardItemModel;
    this->ui->tableView_2->setModel(model_face);

    this->model_face->setHorizontalHeaderItem(0, new QStandardItem("id") );
    this->model_face->setHorizontalHeaderItem(1, new QStandardItem("姓名"));
    this->model_face->setHorizontalHeaderItem(2, new QStandardItem("校园码"));
    this->model_face->setHorizontalHeaderItem(3, new QStandardItem("图片路径"));
    this->model_face->setHorizontalHeaderItem(4, new QStandardItem("特征向量"));

    this->ui->tableView_2->setColumnWidth(0, 50);
    this->ui->tableView_2->setColumnWidth(1, 100);
    this->ui->tableView_2->setColumnWidth(2, 75);
    this->ui->tableView_2->setColumnWidth(3, 225);
    this->ui->tableView_2->setColumnWidth(4, 162);

    ui->tableView_2->verticalHeader()->setVisible(false);
    ui->tableView_2->setAutoScroll(true);
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::add_table_face(int id,QString name,QString code,QString image_path,QString feature)  //人脸数据库表添加
{
    this->model_face->setItem(col_table_face, 0, new QStandardItem(QString::number(id)));
    this->model_face->setItem(col_table_face, 1, new QStandardItem(name));
    this->model_face->setItem(col_table_face, 2, new QStandardItem(code));
    this->model_face->setItem(col_table_face, 3, new QStandardItem(image_path));
    this->model_face->setItem(col_table_face, 4, new QStandardItem(feature));

    this->model_face->item(col_table_face, 0)->setTextAlignment(Qt::AlignCenter);
    this->model_face->item(col_table_face, 1)->setTextAlignment(Qt::AlignCenter);
    this->model_face->item(col_table_face, 2)->setTextAlignment(Qt::AlignCenter);
    this->model_face->item(col_table_face, 3)->setTextAlignment(Qt::AlignCenter);
    this->model_face->item(col_table_face, 4)->setTextAlignment(Qt::AlignCenter);

    col_table_face +=1;
}

void MainWindow::Init_table_record()  //初始化信息统计表
{
    this->model_record = new QStandardItemModel;
    this->ui->tableView_3->setModel(model_record);

    this->model_record->setHorizontalHeaderItem(0, new QStandardItem("序号") );
    this->model_record->setHorizontalHeaderItem(1, new QStandardItem("id"));
    this->model_record->setHorizontalHeaderItem(2, new QStandardItem("姓名"));
    this->model_record->setHorizontalHeaderItem(3, new QStandardItem("校园码"));
    this->model_record->setHorizontalHeaderItem(4, new QStandardItem("日期时间"));

    this->ui->tableView_3->setColumnWidth(0, 50);
    this->ui->tableView_3->setColumnWidth(1, 100);
    this->ui->tableView_3->setColumnWidth(2, 150);
    this->ui->tableView_3->setColumnWidth(3, 100);
    this->ui->tableView_3->setColumnWidth(4, 200);

    ui->tableView_3->verticalHeader()->setVisible(false);
    ui->tableView_3->setAutoScroll(true);
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::add_table_record(int No,int id,QString name,QString code,QString datetime)  //信息统计表
{
    this->model_record->setItem(col_table_record, 0, new QStandardItem(QString::number(No)));
    this->model_record->setItem(col_table_record, 1, new QStandardItem(QString::number(id)));
    this->model_record->setItem(col_table_record, 2, new QStandardItem(name));
    this->model_record->setItem(col_table_record, 3, new QStandardItem(code));
    this->model_record->setItem(col_table_record, 4, new QStandardItem(datetime));

    this->model_record->item(col_table_record, 0)->setTextAlignment(Qt::AlignCenter);
    this->model_record->item(col_table_record, 1)->setTextAlignment(Qt::AlignCenter);
    this->model_record->item(col_table_record, 2)->setTextAlignment(Qt::AlignCenter);
    this->model_record->item(col_table_record, 3)->setTextAlignment(Qt::AlignCenter);
    this->model_record->item(col_table_record, 4)->setTextAlignment(Qt::AlignCenter);

    col_table_record +=1;
}

void MainWindow::update_face_data()  //更新内存中的人脸数据
{
    map_name.clear();
    map_code.clear();
    map_feature.clear();

    QString select_all_sql = "select * from facedata";
    QSqlQuery sql_query;
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug() << "face data  failed!" <<endl;
    }
    else
    {
        while(sql_query.next())
        {
            int id = sql_query.value(0).toInt();
            QString name = sql_query.value(1).toString();
            QString code = sql_query.value(2).toString();
            QString feature = sql_query.value(4).toString();

            map_name.insert(pair < int,QString > (id,name));
            map_code.insert(pair < int,QString > (id,code));
            map_feature.insert(pair < int,QString > (id,feature));
        }
    }
}

void MainWindow::on_tableView_2_doubleClicked(const QModelIndex &index) //人脸数据库查看保存人脸
{
    if (index.isValid())
    {
        QString img_path = model_face->data(model_face->index(index.row(),3)).toString();

        QPixmap mmp;
        if(mmp.load(img_path))
        {
            mmp = mmp.scaled(ui->label_show_3->size(),Qt::KeepAspectRatio);
            ui->label_show_3->setPixmap(mmp);
        }
        else
        {
            QMessageBox::information(this,"提示","未找到该图片！");
        }
    }
}

void MainWindow::updateImage()  //摄像头更新图片
{
    capture>>srcImage;
    cv::flip(srcImage, image_fliped, 1);

    if(image_fliped.data)
    {
        cvtColor(image_fliped, image_fliped, CV_BGR2RGB);//Qt中支持的是RGB图像, OpenCV中支持的是BGR

        //识别
        if(is_recognize)
        {
            QImage image1 = face_recognition(image_fliped);
            ui->label_show->setPixmap(QPixmap::fromImage(image1));
            ui->label_show->resize(image1.size());
            ui->label_show->show();

            theTimer.setInterval(face_recognition_frame_time);
        }
        else
        {
            QImage image1 = QImage((uchar*)(image_fliped.data), image_fliped.cols, image_fliped.rows, QImage::Format_RGB888);
            ui->label_show_2->setPixmap(QPixmap::fromImage(image1));
            ui->label_show_2->resize(image1.size());
            ui->label_show_2->show();
        }

    }
}

void MainWindow::updatetime()  //显示日期时间
{
    current_date_time =QDateTime::currentDateTime();
    current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss");

    ui->label_datetime->setText(current_date);
}

QImage MainWindow::face_recognition(cv::Mat image_fliped)   //人脸识别，与数据库进行比对
{
    double time_start = clock();
    ncnn::Mat in = ncnn::Mat::from_pixels_resize(image_fliped.data, ncnn::Mat::PIXEL_RGB, image_fliped.cols, image_fliped.rows, image_fliped.cols, image_fliped.rows);
    std::vector<Bbox> finalBbox;
    mtcnn.detect(in,finalBbox);

    QImage Img = QImage((const unsigned char*)(image_fliped.data),image_fliped.cols,image_fliped.rows,image_fliped.step,QImage::Format_RGB888);

//    cout<<finalBbox.size()<<"张人脸"<<endl;
    ui->label_detectnum->setText(QString::number(finalBbox.size()));

    int left,top,right,bottom;
    QPainter painter(&Img);
    QPen pen;
    QFont font;

    int face_recognition_count = 0;

    for (int i = 0; i < finalBbox.size(); i++)
    {
        left = finalBbox[i].x1;
        top = finalBbox[i].y1;
        right = finalBbox[i].x2;
        bottom = finalBbox[i].y2;

        int mtcnn_landmark[10];

//        for(int j = 0; j < 5; j++)
//        {
//            int x = finalBbox[i].ppoint[j];
//            int y = finalBbox[i].ppoint[j + 5];
//            painter.drawPoint(x,y);
//        }

        for(int j = 0; j < 10; j++)
        {
            mtcnn_landmark[j] = finalBbox[i].ppoint[j];
        }

        cv::Mat img_face = image_fliped(cv::Rect(left, top, right - left, bottom - top)).clone();
        ncnn::Mat in_face = ncnn::Mat::from_pixels_resize(img_face.data, ncnn::Mat::PIXEL_RGB, img_face.cols, img_face.rows, 112, 112);
        for(int j = 0; j < 5; j++)
        {
            mtcnn_landmark[j] = (mtcnn_landmark[j] - left)*112/(right - left);
            mtcnn_landmark[j + 5] = (mtcnn_landmark[j + 5] - top)*112/(bottom - top);
        }

        ncnn::Mat det = mobilefacenet.preprocess(in_face, mtcnn_landmark);
        std::vector<float> feature;
        mobilefacenet.start(det, feature);

        //与数据库中已有数据进行比对
        map<double,int> map_similar;
        std::vector<float> feature2;
        map <int, QString>::iterator iter;
        for(iter = map_feature.begin(); iter != map_feature.end(); iter++)
        {
            int face_ = iter->first;
            QString feature_all = iter->second;
            QStringList feature_list = feature_all.split(" ");

            for (int i = 0; i < 128; i++)
            {
                QString tmp = feature_list[i];
                feature2.push_back(tmp.toFloat());
            }

            double similar = Face::calculSimilar(feature, feature2, confidence_set);

            map_similar.insert(pair<double,int>(similar,face_));

            feature2.clear();
        }

        font.setPointSize(25);
        painter.setFont(font);

        map <double,int>::iterator iter2;

        if(confidence_set == 0)
        {
            iter2=map_similar.begin();
            double max_similar = iter2->first;

            if(max_similar <= threshold_0)
            {
                int face_id = iter2->second;

                if(map_code[face_id] == "red")
                {
                    pen.setColor(Qt::red);
                    pen.setWidth(3);
                    painter.setPen(pen);
                }
                else
                {
                    pen.setColor(Qt::green);
                    pen.setWidth(3);
                    painter.setPen(pen);
                }

                painter.drawRect(left,top,right-left,bottom-top);
                QString face_name = map_name[face_id];
                painter.drawText(left,top,face_name);

                face_recognition_count++;

                //人脸识别记录表数据增加
                current_date_time =QDateTime::currentDateTime();
                current_date =current_date_time.toString("yyyy.MM.dd hh:mm");
                add_table_recognition(col_table_recognition,face_id,face_name,map_code[face_id],current_date,max_similar);
                InsertRecord(face_id, face_name, map_code[face_id], current_date);
            }
            else
            {
                pen.setColor(Qt::blue);
                pen.setWidth(3);
                painter.setPen(pen);

                painter.drawRect(left,top,right-left,bottom-top);
                painter.drawText(left,top,"Unknown face");

                //人脸识别记录表数据增加
                current_date_time =QDateTime::currentDateTime();
                current_date =current_date_time.toString("yyyy.MM.dd hh:mm");
                add_table_recognition(col_table_recognition,-1,"未知","未知",current_date,-1);
            }
        }
        else if(confidence_set == 1)
        {
            iter2=map_similar.end();
            iter2--;
            double max_similar = iter2->first;

            //qDebug()<<max_similar<<endl;

            if(max_similar >= threshold_1)
            {

                max_similar = max_similar*100.0;

                int face_id = iter2->second;

                if(map_code[face_id] == "red")
                {
                    pen.setColor(Qt::red);
                    pen.setWidth(3);
                    painter.setPen(pen);
                }
                else
                {
                    pen.setColor(Qt::green);
                    pen.setWidth(3);
                    painter.setPen(pen);
                }

                painter.drawRect(left,top,right-left,bottom-top);
                QString face_name = map_name[face_id];
                painter.drawText(left,top-10,face_name);

                face_recognition_count++;

                //人脸识别记录表数据增加
                current_date_time =QDateTime::currentDateTime();
                current_date =current_date_time.toString("yyyy.MM.dd hh:mm");
                add_table_recognition(col_table_recognition,face_id,face_name,map_code[face_id],current_date,max_similar);
                InsertRecord(face_id, face_name, map_code[face_id], current_date);
            }
            else
            {
                pen.setColor(Qt::blue);
                pen.setWidth(3);
                painter.setPen(pen);

                painter.drawRect(left,top,right-left,bottom-top);
                painter.drawText(left,top,"Unknown face");

                //人脸识别记录表数据增加
                current_date_time =QDateTime::currentDateTime();
                current_date =current_date_time.toString("yyyy.MM.dd hh:mm");
                add_table_recognition(col_table_recognition,-1,"未知","未知",current_date,0);
            }
        }

    }
    double time_end = clock();
    face_recognition_frame_time = time_end-time_start;
    ui->label_recognizenum->setText(QString::number(face_recognition_count));
    ui->label_recognizetime->setText(QString::number(time_end-time_start,'f',1));
    return Img;
}

void MainWindow::on_action1_triggered() //人脸识别界面
{
    is_recognize = TRUE;
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void MainWindow::on_action2_triggered() //人脸录入界面
{
    is_recognize = FALSE;
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void MainWindow::on_action3_triggered() //人脸管理界面
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

void MainWindow::on_action4_triggered() //信息统计界面
{
    ui->stackedWidget->setCurrentWidget(ui->page_4);
}

void MainWindow::on_action5_triggered() //设置蓝色主题
{
    loadStyle(":/qss/lightblue.css");
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{font:14pt;}");
}

void MainWindow::on_action6_triggered() //设置黑色主题
{
    loadStyle(":/qss/blacksoft.css");
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{font:14pt;}");
}

void MainWindow::on_action7_triggered() //设置灰色主题
{
    loadStyle(":/qss/flatgray.css");
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{font:14pt;}");
}

void MainWindow::on_pushButton_camera_clicked() //开启/关闭摄像头
{
    bg_movie->stop();
    if (capture.isOpened())
    {
        capture.release();
        theTimer.stop();

        ui->pushButton_camera->setText("开启摄像头");
        ui->pushButton_photo->setEnabled(true);
        ui->label_camera_status->setText("关闭");

        return;
    }

    if (capture.open(200)) {
        ui->pushButton_camera->setText("关闭摄像头");
        ui->pushButton_photo->setEnabled(false);
        ui->label_camera_status->setText("开启");
        srcImage = cv::Mat::zeros(capture.get(CV_CAP_PROP_FRAME_HEIGHT), capture.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3);
        theTimer.start(face_recognition_frame_time);
    }
    else {
        capture.release();
        QMessageBox::information(this,"提示","摄像头打开失败！");
    }
}

void MainWindow::on_pushButton_photo_clicked()  //选择图片识别
{
    bg_movie->stop();
    QString fileName = QFileDialog::getOpenFileName(this,QString("选择图片文件"),"/apps/SACS/image/",QString("图片文件(*jpg)"));
    if(fileName != "")
    {
        cv::Mat Image = cv::imread(fileName.toStdString());
        cv::cvtColor(Image, Image, CV_BGR2RGB);

        QImage Img = face_recognition(Image);
        QPixmap pixmap = QPixmap::fromImage(Img.scaled(ui->label_show->size(),Qt::KeepAspectRatio));//图片按比例缩放
        ui->label_show->setPixmap(pixmap);

        cv::Mat mat = cv::Mat(Img.height(), Img.width(), CV_8UC3, (void*)Img.constBits(), Img.bytesPerLine());
        cv::cvtColor(mat, mat, CV_RGB2BGR);
        QString image_name = "photo_recognition.jpg";

        cv::imwrite(image_name.toStdString(), mat);
    }
}

void MainWindow::on_comboBox_confidence_currentIndexChanged(int index)  //选择特征计算方法,取消此功能
{
    confidence_set = index;

    if(confidence_set == 0)
    {
        ui->lineEdit_threshold->setText(QString::number(threshold_0_0,'f',2));
    }
    else if(confidence_set == 1)
    {
        ui->lineEdit_threshold->setText(QString::number(threshold_1_1,'f',2));
    }
}

void MainWindow::on_pushButton_setconfidence_clicked()  //设置置信度
{
    double tmp_data = ui->lineEdit_threshold->text().toDouble();

    if(tmp_data>100 || tmp_data<0)
    {
        QMessageBox::information(this,"提示","请输入正确的置信度！（0~100）");

        return;
    }

    if(confidence_set == 0)
    {
        threshold_0_0 = ui->lineEdit_threshold->text().toDouble();

        threshold_0 = threshold_0_0*2/100.0;
    }
    else if(confidence_set == 1)
    {
        threshold_1_1 = ui->lineEdit_threshold->text().toDouble();

        threshold_1 = threshold_1_1/100.0;
    }

    QMessageBox::information(this,"提示","修改置信度成功！");
}

void MainWindow::on_pushButton_camera_2_clicked()   //开启摄像头
{
    bg_movie->stop();
    if (capture.isOpened())
    {
        capture.release();
        theTimer.stop();

        ui->pushButton_camera_2->setText("开启摄像头");
        ui->pushButton_photo_2->setEnabled(true);
        ui->pushButton_getphoto->setEnabled(false);
        ui->label_camera_status_2->setText("关闭");

        return;
    }

    if (capture.open(200)) {
        ui->pushButton_camera_2->setText("关闭摄像头");
        ui->pushButton_photo_2->setEnabled(false);
        ui->pushButton_getphoto->setEnabled(true);
        ui->label_camera_status_2->setText("开启");
        srcImage = cv::Mat::zeros(capture.get(CV_CAP_PROP_FRAME_HEIGHT), capture.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3);
        theTimer.start(100);
    }
    else {
        capture.release();
        QMessageBox::information(this,"提示","摄像头打开失败！");
    }
}

void MainWindow::on_pushButton_getphoto_clicked()   //拍照
{
    if (!capture.isOpened())
        return;

    char image_name[64] = {0};
    cv::Mat frame1;
    QPixmap mmp;

    QDateTime time = QDateTime::currentDateTime();
    QString dateStr =time.toString("yyyy-MM-dd");

    capture >> frame1;
    cv::flip(frame1, frame1, 1);

    if (frame1.empty())
    {
        std::cout << "frame1 is empty" << std::endl;
    }else{
        cout<<"index="<< index + 1 <<", frame1.size= "<<frame1.size<<endl;
        sprintf(image_name,"%s%s_%d-%d-%d_%d%s","/apps/SACS/image/", dateStr.toStdString().c_str(),
                            time.time().hour(),time.time().minute(),time.time().second(), index++,".jpg");
        cout<<image_name<<endl;
        //保存图片
        cv::imwrite(image_name, frame1);

        Select_Image = frame1;
        cv::cvtColor(Select_Image, Select_Image, CV_BGR2RGB);

        sleep(1);

        //关闭摄像头
        on_pushButton_camera_2_clicked();

        //显示图片
        mmp.load(image_name);
        mmp = mmp.scaled(ui->label_show_2->size());
        ui->label_show_2->setPixmap(mmp);

        QMessageBox::information(this,"提示","拍照成功！");
    }


}

void MainWindow::on_pushButton_photo_2_clicked()    //选择图片
{
    bg_movie->stop();
    QString fileName = QFileDialog::getOpenFileName(this,QString("选择图片文件"),"/apps/SACS/image/",QString("图片文件(*png *jpg)"));
    if(fileName != "")
    {
        cv::Mat Image = cv::imread(fileName.toStdString());
        cv::cvtColor(Image, Image, CV_BGR2RGB);

        Select_Image = Image;

        QImage Img = QImage((const unsigned char*)(Image.data),Image.cols,Image.rows,Image.step,QImage::Format_RGB888);
        QPixmap pixmap = QPixmap::fromImage(Img.scaled(ui->label_show_2->size(),Qt::KeepAspectRatio));//图片按比例缩放
        ui->label_show_2->setPixmap(pixmap);
    }
}

void MainWindow::on_pushButton_register_clicked()   //录入
{
    QString id = ui->lineEdit_id_3->text();
    QString name = ui->lineEdit_name->text();
    if(id == "" || name == "")
    {
        QMessageBox::information(this,"提示","请输入正确的id和姓名！");
        ui->lineEdit_id_3->setText("");
        ui->lineEdit_name->setText("");
        return;
    }

    if(!Select_Image.data)
    {
        QMessageBox::information(this,"提示","未检测到图片，录入失败！");
        return;
    }

    cv::Mat img = Select_Image;
    ncnn::Mat in = ncnn::Mat::from_pixels_resize(img.data, ncnn::Mat::PIXEL_RGB, img.cols, img.rows, img.cols, img.rows);
    std::vector<Bbox> finalBbox;
    mtcnn.detect(in,finalBbox);

    cout<<finalBbox.size()<<"张人脸"<<endl;

    if(finalBbox.size() == 0)
    {
        QMessageBox::information(this,"提示","未检测到人脸，录入失败！");
        return;
    }

    if(finalBbox.size() > 1)
    {
        QMessageBox::information(this,"提示","检测到多个人脸，录入失败！");
        return;
    }

    QString select_sql = "select * from facedata where id = :id";
    QSqlQuery sql_query;
    sql_query.prepare(select_sql);
    sql_query.bindValue(":id", id);
    if(!sql_query.exec())
    {}
    else
    {
        int count = 0;
        while(sql_query.next())
        {
            count += 1;
        }

        if(count == 0)
        {}
        else
        {
            QMessageBox::information(this,"提示","id重复，请重新录入！");
            ui->lineEdit_id_3->setText("");
            ui->lineEdit_name->setText("");
            return;
        }
    }

    int left,top,right,bottom;
    int mtcnn_landmark[10];
    for (int i = 0; i < finalBbox.size(); i++)
    {
        left = finalBbox[i].x1;
        top = finalBbox[i].y1;
        right = finalBbox[i].x2;
        bottom = finalBbox[i].y2;

        for(int j = 0; j < 10; j++)
        {
            mtcnn_landmark[j] = finalBbox[i].ppoint[j];
        }
    }

    cv::Mat img_face = img(cv::Rect(left, top, right - left, bottom - top)).clone();
    ncnn::Mat in_face = ncnn::Mat::from_pixels_resize(img_face.data, ncnn::Mat::PIXEL_RGB, img_face.cols, img_face.rows, 112, 112);
    for(int j = 0; j < 5; j++)
    {
        mtcnn_landmark[j] = (mtcnn_landmark[j] - left)*112/(right - left);
        mtcnn_landmark[j + 5] = (mtcnn_landmark[j + 5] - top)*112/(bottom - top);
    }

    ncnn::Mat det = mobilefacenet.preprocess(in_face, mtcnn_landmark);
    std::vector<float> feature;
    mobilefacenet.start(det, feature);

    QString feature2;
    for(int i = 0; i<feature.size() - 1;i++)
    {
        feature2 = feature2 + QString::number(feature[i],'f',10) + " ";
    }

    feature2 = feature2 + QString::number(feature[127],'f',10);

    //保存和显示人脸
    QString save_file = "facesave/"+ id + "_" + name + ".jpg";
    cv::cvtColor(img_face, img_face, CV_BGR2RGB);
    cv::imwrite(save_file.toStdString(), img_face);
    QPixmap mmp;
    mmp.load(save_file);
    mmp = mmp.scaled(ui->label_show_4->size(),Qt::KeepAspectRatio);
    ui->label_show_4->setPixmap(mmp);

    //添加入数据库
    InsertFaceData(id.toInt(),name,"green",save_file,feature2);

    QMessageBox::information(this,"提示","录入成功！");
    ui->lineEdit_id_3->setText("");
    ui->lineEdit_name->setText("");
}

void MainWindow::on_pushButton_query_clicked()  //查询人脸
{
    QString name = ui->lineEdit_name_2->text();
    QString id = ui->lineEdit_id->text();

    model_face->removeRows(0,model_face->rowCount()); //删除所有行

    col_table_face = 0;
    if(name != "" && id == "")
        QueryFaceData(name);
    else if(name == "" && id != "")
        QueryFaceData_2(id.toInt());
    else
    {
        QMessageBox::information(this,"提示","请正确输入人脸id或姓名，注意不能同时输入！");
    }

    //清空
    ui->lineEdit_name_2->setText("");
    ui->lineEdit_id->setText("") ;
    ui->lineEdit_newname->setText("") ;
}

void MainWindow::on_pushButton_delete_clicked() //删除人脸
{
    QString id = ui->lineEdit_id->text();
    if(id != "")
        DeleteFaceData(id.toInt());
    else
    {
        QMessageBox::information(this,"提示","请正确输入人脸id！");
    }

    //清空
    ui->lineEdit_name_2->setText("");
    ui->lineEdit_id->setText("") ;
    ui->lineEdit_newname->setText("") ;
}

void MainWindow::on_pushButton_update_clicked() //修改姓名
{
    QString id = ui->lineEdit_id->text();
    QString new_name = ui->lineEdit_newname->text();

    if(new_name != "" && id != "")
    {
        UpdateFaceData(id.toInt(), new_name) ;
    }
    else
    {
        QMessageBox::information(this,"提示","请正确输入人脸id和新姓名！");
    }

    //清空
    ui->lineEdit_name_2->setText("");
    ui->lineEdit_id->setText("") ;
    ui->lineEdit_newname->setText("") ;
}

void MainWindow::on_pushButton_queryall_clicked()   //查询所有数据
{
    model_face->removeRows(0,model_face->rowCount()); //删除所有行
    col_table_face = 0;
    QueryFaceData();
}

void MainWindow::on_pushButton_today_clicked()  //当天所有记录
{
    QString datetime = ui->lineEdit_date->text();
    model_record->removeRows(0,model_record->rowCount()); //删除所有行
    col_table_record = 0;
    QueryRecord(datetime);
}

void MainWindow::on_pushButton_people_clicked() //某人的记录
{
    QString name = ui->lineEdit_name_3->text();
    QString id = ui->lineEdit_id_2->text();

    model_record->removeRows(0,model_record->rowCount()); //删除所有行

    col_table_record = 0;
    if(name != "" && id == "")
        QueryRecord_2_2(name);
    else if(name == "" && id != "")
        QueryRecord_2(id.toInt());
    else
    {
        QMessageBox::information(this,"提示","请正确输入人脸id或姓名，注意不能同时输入！");
    }

    //清空
    ui->lineEdit_name_3->setText("");
    ui->lineEdit_id_2->setText("") ;
}

void MainWindow::on_pushButton_green_clicked()  //绿码记录
{
    model_record->removeRows(0,model_record->rowCount()); //删除所有行
    QueryRecord_3();
}

void MainWindow::on_pushButton_red_clicked()    //红码记录
{
    model_record->removeRows(0,model_record->rowCount()); //删除所有行
    QueryRecord_4();
}

//
//  数据库操作函数
//

void MainWindow::CreatDb()  //创建数据库
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db_all = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        db_all = QSqlDatabase::addDatabase("QSQLITE");
        db_all.setDatabaseName("db_all.db");

        //db_all.setUserName("test");
        //db_all.setPassword("test");
    }
}

bool MainWindow::OpenDb()   //判断是否已经打开数据库
{
    if(!db_all.open())
    {
        qDebug() << "Error: Failed to connect database." << endl;
        return false;
    }
    else
    {
        qDebug() << "secceed to connect database." <<endl;
    }

    return true;
}

void MainWindow::CloseDb()  //关闭数据库
{
    db_all.close();

    qDebug() << "secceed to database." <<endl;
}

void MainWindow::CreateTable()  //创建数据表
{
    QSqlQuery sql_query;
    QString creat_sql = "create table facedata (id int primary key, name varchar(50), code varchar(10), image_path varchar(100), feature varchar(3000))";
    sql_query.prepare(creat_sql);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << endl;
    }
    else
    {
        qDebug() << "Table created!";
    }

    creat_sql = "create table record (No int primary key, id int, name varchar(100), code varchar(20), datetime varchar(50))";
    sql_query.prepare(creat_sql);
    if(!sql_query.exec())
    {
        qDebug() << "Error: Fail to create table." << endl;
    }
    else
    {
        qDebug() << "Table created!";
    }
}

void MainWindow::QueryFaceData() //遍历人脸数据
{
    QString select_all_sql = "select * from facedata";
    QSqlQuery sql_query;
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        //qDebug() << "Query failed!" <<endl;
        QMessageBox::information(this,"提示","查询所有数据失败，请重新查询！");
    }
    else
    {
        while(sql_query.next())
        {
            int id = sql_query.value(0).toInt();
            QString name = sql_query.value(1).toString();
            QString code = sql_query.value(2).toString();
            QString image_path = sql_query.value(3).toString();
            QString feature = sql_query.value(4).toString();
            //qDebug()<<QString("id:%1   name:%2  code:%3  image_path:%4   feature:%5").arg(id).arg(name).arg(code).arg(image_path).arg(feature);

            add_table_face(id,name,code,image_path,feature);
        }

        QMessageBox::information(this,"提示","查询所有数据成功！");
    }
}

void MainWindow::InsertFaceData(int id, QString name, QString code, QString img, QString feature)   //插入人脸数据
{
    QString insert_sql = "insert into facedata(id,name,code,image_path,feature) values (?, ?, ?, ?, ?)";
    QSqlQuery sql_query;
    sql_query.prepare(insert_sql);

    sql_query.addBindValue(id);
    sql_query.addBindValue(name);
    sql_query.addBindValue(code);
    sql_query.addBindValue(img);
    sql_query.addBindValue(feature);
    if(!sql_query.exec())
    {
        qDebug() << "inserted failed!"<< endl;
    }
    else
    {
        qDebug() << "inserted succeed!"<<endl;

        update_face_data();
    }
}

void MainWindow::UpdateFaceData(int id, QString name)   //更新姓名
{
    QString update_sql = "update facedata set name = :name where id = :id";
    QSqlQuery sql_query;
    sql_query.prepare(update_sql);
    sql_query.bindValue(":name", name);
    sql_query.bindValue(":id", id);
    if(!sql_query.exec())
    {
        //qDebug() << "update failed!" <<endl;
        QMessageBox::information(this,"提示","修改姓名失败，请重新修改！");
    }
    else
    {
        //qDebug() << "update succeed!";
        QMessageBox::information(this,"提示","修改姓名成功！");

        update_face_data();
    }
}

void MainWindow::DeleteFaceData(int id)   //删除数据
{
    QString select_sql = "select * from facedata where id = :id";
    QSqlQuery sql_query;
    sql_query.prepare(select_sql);
    sql_query.bindValue(":id", id);
    if(!sql_query.exec())
    {
        //qDebug() << "Query failed!" <<endl;
        QMessageBox::information(this,"提示","删除人脸数据失败，请重新删除！");
        return;
    }
    else
    {
        while(sql_query.next())
        {
            QString image_path = sql_query.value(3).toString();
            QFile filename(image_path);
            filename.remove();
        }
    }

    QString delete_sql = "delete from facedata where id = :id";
    sql_query.prepare(delete_sql);
    sql_query.bindValue(":id", id);
    if(!sql_query.exec())
    {
        //qDebug() << "delete failed!" <<endl;
        QMessageBox::information(this,"提示","删除人脸数据失败，请重新删除！");
    }
    else
    {
        //qDebug() << "delete succeed!";
        QMessageBox::information(this,"提示","删除人脸数据成功！");

        update_face_data();
    }
}

void MainWindow::QueryFaceData(QString name) //查询数据,人名查询
{
    QString select_sql = "select * from facedata where name = :name";
    QSqlQuery sql_query;
    sql_query.prepare(select_sql);
    sql_query.bindValue(":name", name);
    if(!sql_query.exec())
    {
        //qDebug() << "Query failed!" <<endl;
        QMessageBox::information(this,"提示","查询失败，请重新查询！");
    }
    else
    {
        int count = 0;
        while(sql_query.next())
        {
            int id = sql_query.value(0).toInt();
            QString name = sql_query.value(1).toString();
            QString code = sql_query.value(2).toString();
            QString image_path = sql_query.value(3).toString();
            QString feature = sql_query.value(4).toString();
            //qDebug()<<QString("id:%1   name:%2  code:%3  image_path:%4   feature:%5").arg(id).arg(name).arg(code).arg(image_path).arg(feature);

            add_table_face(id,name,code,image_path,feature);

            count += 1;
        }

        if(count == 0)
        {
            //qDebug() << "The face data is not in db!" <<endl;
            QMessageBox::information(this,"提示","未查询到该人脸数据！");
        }
        else
        {
            QMessageBox::information(this,"提示","查询成功！");
        }
    }
}

void MainWindow::QueryFaceData_2(int id) //查询数据,人脸id查询
{
    QString select_sql = "select * from facedata where id = :id";
    QSqlQuery sql_query;
    sql_query.prepare(select_sql);
    sql_query.bindValue(":id", id);
    if(!sql_query.exec())
    {
        //qDebug() << "Query failed!" <<endl;
        QMessageBox::information(this,"提示","查询失败，请重新查询！");
    }
    else
    {
        int count = 0;
        while(sql_query.next())
        {
            int id = sql_query.value(0).toInt();
            QString name = sql_query.value(1).toString();
            QString code = sql_query.value(2).toString();
            QString image_path = sql_query.value(3).toString();
            QString feature = sql_query.value(4).toString();
            //qDebug()<<QString("id:%1   name:%2  code:%3  image_path:%4   feature:%5").arg(id).arg(name).arg(code).arg(image_path).arg(feature);

            add_table_face(id,name,code,image_path,feature);

            count += 1;
        }

        if(count == 0)
        {
            //qDebug() << "The face data is not in db!" <<endl;
            QMessageBox::information(this,"提示","未查询到该人脸数据！");
        }
        else
        {
            QMessageBox::information(this,"提示","查询成功！");
        }
    }
}

int MainWindow::GetMaxNo() //获取最新一条No
{
    QString select_all_sql = "select max(No) from record";
    QSqlQuery sql_query;
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug() << "Query failed!" <<endl;
        return -1;
    }
    else
    {
        while(sql_query.next())
        {
            int no_new = sql_query.value(0).toInt();
            return no_new;
        }
    }
}

void MainWindow::InsertRecord(int id, QString name, QString code, QString datetime)   //插入进校记录,1分钟记录一次
{
    QString select_sql = "select * from record where id = :id and datetime = :datetime";
    QSqlQuery sql_query;
    sql_query.prepare(select_sql);
    sql_query.bindValue(":id", id);
    sql_query.bindValue(":datetime", datetime);
    if(!sql_query.exec())
    {
        //qDebug() << "Query failed!" <<endl;
        //QMessageBox::information(this,"提示","查询失败，请重新查询！");
    }
    else
    {
        if(sql_query.first())
        {
            return;
        }
    }

    QString insert_sql = "insert into record values (?, ?, ?, ?, ?)";
    sql_query.prepare(insert_sql);

    int No_new = GetMaxNo();
    if(No_new == -1)
    {
        qDebug() << "inserted failed!"<< endl;
        return;
    }

    sql_query.addBindValue(No_new + 1);
    sql_query.addBindValue(id);
    sql_query.addBindValue(name);
    sql_query.addBindValue(code);
    sql_query.addBindValue(datetime);

    if(!sql_query.exec())
    {
        qDebug() << "inserted failed!"<< endl;
    }
}

void MainWindow::QueryRecord(QString datetime) //查询当天记录
{
    QString select_sql = "select * from record where datetime like :datetime";
    QSqlQuery sql_query;
    sql_query.prepare(select_sql);
    sql_query.bindValue(":datetime", datetime + "%");
    if(!sql_query.exec())
    {
        //qDebug() << "Query failed!" <<endl;
        QMessageBox::information(this,"提示","查询失败，请重新查询！");
    }
    else
    {
        int count = 0;
        col_table_record = 0;
        while(sql_query.next())
        {
            int No = sql_query.value(0).toInt();
            int id = sql_query.value(1).toInt();
            QString name = sql_query.value(2).toString();
            QString code = sql_query.value(3).toString();
            QString datetime = sql_query.value(4).toString();

            add_table_record(No,id,name,code,datetime);

            count += 1;
        }

        if(count == 0)
        {
            //qDebug() << "The face data is not in db!" <<endl;
            QMessageBox::information(this,"提示","未查询到该天记录！");
        }
        else
        {
            QMessageBox::information(this,"提示","查询成功！");
        }
    }
}

void MainWindow::QueryRecord_2(int id) //查询个人记录，id
{
    QString select_sql = "select * from record where id = :id";
    QSqlQuery sql_query;
    sql_query.prepare(select_sql);
    sql_query.bindValue(":id", id);
    if(!sql_query.exec())
    {
        //qDebug() << "Query failed!" <<endl;
        QMessageBox::information(this,"提示","查询失败，请重新查询！");
    }
    else
    {
        int count = 0;
        col_table_record = 0;
        while(sql_query.next())
        {
            int No = sql_query.value(0).toInt();
            int id = sql_query.value(1).toInt();
            QString name = sql_query.value(2).toString();
            QString code = sql_query.value(3).toString();
            QString datetime = sql_query.value(4).toString();

            add_table_record(No,id,name,code,datetime);

            count += 1;
        }

        if(count == 0)
        {
            //qDebug() << "The face data is not in db!" <<endl;
            QMessageBox::information(this,"提示","未查询到该人记录！");
        }
        else
        {
            QMessageBox::information(this,"提示","查询成功！");
        }
    }
}

void MainWindow::QueryRecord_2_2(QString name) //查询个人记录，姓名
{
    QString select_sql = "select * from record where name = :name";
    QSqlQuery sql_query;
    sql_query.prepare(select_sql);
    sql_query.bindValue(":name", name);
    if(!sql_query.exec())
    {
        //qDebug() << "Query failed!" <<endl;
        QMessageBox::information(this,"提示","查询失败，请重新查询！");
    }
    else
    {
        int count = 0;
        col_table_record = 0;
        while(sql_query.next())
        {
            int No = sql_query.value(0).toInt();
            int id = sql_query.value(1).toInt();
            QString name = sql_query.value(2).toString();
            QString code = sql_query.value(3).toString();
            QString datetime = sql_query.value(4).toString();

            add_table_record(No,id,name,code,datetime);

            count += 1;
        }

        if(count == 0)
        {
            //qDebug() << "The face data is not in db!" <<endl;
            QMessageBox::information(this,"提示","未查询到该人记录！");
        }
        else
        {
            QMessageBox::information(this,"提示","查询成功！");
        }
    }
}

void MainWindow::QueryRecord_3() //查询绿码记录
{
    QString select_sql = "select * from record where code = :code";
    QSqlQuery sql_query;
    sql_query.prepare(select_sql);
    sql_query.bindValue(":code", "green");
    if(!sql_query.exec())
    {
        //qDebug() << "Query failed!" <<endl;
        QMessageBox::information(this,"提示","查询失败，请重新查询！");
    }
    else
    {
        int count = 0;
        col_table_record = 0;
        while(sql_query.next())
        {
            int No = sql_query.value(0).toInt();
            int id = sql_query.value(1).toInt();
            QString name = sql_query.value(2).toString();
            QString code = sql_query.value(3).toString();
            QString datetime = sql_query.value(4).toString();

            add_table_record(No,id,name,code,datetime);

            count += 1;
        }

        if(count == 0)
        {
            //qDebug() << "The face data is not in db!" <<endl;
            QMessageBox::information(this,"提示","未查询到记录！");
        }
        else
        {
            QMessageBox::information(this,"提示","查询成功！");
        }
    }
}

void MainWindow::QueryRecord_4() //查询红码记录
{
    QString select_sql = "select * from record where code = :code";
    QSqlQuery sql_query;
    sql_query.prepare(select_sql);
    sql_query.bindValue(":code", "red");
    if(!sql_query.exec())
    {
        //qDebug() << "Query failed!" <<endl;
        QMessageBox::information(this,"提示","查询失败，请重新查询！");
    }
    else
    {
        int count = 0;
        col_table_record = 0;
        while(sql_query.next())
        {
            int No = sql_query.value(0).toInt();
            int id = sql_query.value(1).toInt();
            QString name = sql_query.value(2).toString();
            QString code = sql_query.value(3).toString();
            QString datetime = sql_query.value(4).toString();

            add_table_record(No,id,name,code,datetime);

            count += 1;
        }

        if(count == 0)
        {
            //qDebug() << "The face data is not in db!" <<endl;
            QMessageBox::information(this,"提示","未查询到记录！");
        }
        else
        {
            QMessageBox::information(this,"提示","查询成功！");
        }
    }
}

