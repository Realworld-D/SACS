#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <QPaintEvent>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QImage>
#include <QVector>
#include <QDateTime>
#include <QDebug>
#include <mtcnn.h>
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <recognize.h>
#include <QFileDialog>
#include "QStandardItem"
#include <QFile>
#include <head.h>
#include <qmovie.h>
#include <QIcon>
#include <QFont>

//#pragma execution_character_set("utf-8")

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void InitSystem();  //系统初始化

    void CreatDb();  //创建数据库

    bool OpenDb();   //判断是否已经打开数据库

    void CloseDb();  //关闭数据库

    void CreateTable();  //创建数据表

    void QueryFaceData(); //遍历数据

    void InsertFaceData(int id, QString name, QString code, QString img, QString feature);  //插入人脸数据

    void UpdateFaceData(int id, QString name);   //更新姓名

    void DeleteFaceData(int id);   //删除数据

    void QueryFaceData(QString name); //查询数据,姓名查询

    void QueryFaceData_2(int id); //查询数据,人脸id查询

    int GetMaxNo(); //获取最新一条No

    void InsertRecord(int id, QString name, QString code, QString datetime);   //插入进校记录

    void QueryRecord(QString datetime); //查询当天记录

    void QueryRecord_2(int id); //查询个人记录，id

    void QueryRecord_2_2(QString name); //查询个人记录，姓名

    void QueryRecord_3(); //查询绿码记录

    void QueryRecord_4(); //查询红码记录

    QImage face_recognition(cv::Mat image_fliped); //人脸识别

    void Init_table_recognition();

    void add_table_recognition(int col,int id,QString name,QString code,QString result,double distance);

    void Init_table_face();

    void add_table_face(int id,QString name,QString code,QString image_path,QString feature);

    void Init_table_record();

    void add_table_record(int No,int id,QString name,QString code,QString datetime);

    void update_face_data();

public slots:
    void updateImage();
    void updatetime();

private:
    Ui::MainWindow *ui;

    MTCNN mtcnn;
    Face::Recognize mobilefacenet;
    int confidence_set = 1;                     //默认置信度为余弦相似度
    double threshold_0 = 1;                     //欧氏距离默认阈值为1
    double threshold_1 = 0.5;                   //余弦相似度默认阈值为0.5
    double threshold_0_0 = 50;                   //欧氏距离下的置信度默认值为50
    double threshold_1_1 = 50;                   //余弦相似度下的置信度默认值为50

    cv::VideoCapture capture;
    QTimer theTimer;
    cv::Mat srcImage;
    cv::Mat image_fliped;
    int index = 0;
    int face_recognition_frame_time = 2000;

    bool is_recognize = TRUE;

    QSqlDatabase db_all;                        //数据库
    map<int,QString> map_name;
    map<int,QString> map_code;
    map<int,QString> map_feature;

    QStandardItemModel *model;                  //人脸识别记录表
    int col_table_recognition = 0;
    QStandardItemModel *model_face;             //人脸数据库表
    int col_table_face = 0;
    QStandardItemModel *model_record;           //信息统计表
    int col_table_record = 0;

    cv::Mat Select_Image;   //选择图片文件

    QDateTime current_date_time;
    QString current_date;

    QTimer local_timer;

    QMovie *bg_movie;
    QPixmap facebg;

private slots:
    void initForm();
    void loadStyle(const QString &qssFile);

private slots:
    void on_action1_triggered();
    void on_action2_triggered();
    void on_action3_triggered();
    void on_action4_triggered();
    void on_action5_triggered();
    void on_action6_triggered();
    void on_action7_triggered();
    void on_pushButton_camera_clicked();
    void on_pushButton_photo_clicked();
    void on_comboBox_confidence_currentIndexChanged(int index);
    void on_pushButton_setconfidence_clicked();
    void on_pushButton_camera_2_clicked();
    void on_pushButton_getphoto_clicked();
    void on_pushButton_photo_2_clicked();
    void on_pushButton_register_clicked();
    void on_pushButton_query_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_update_clicked();
    void on_pushButton_queryall_clicked();
    void on_pushButton_today_clicked();
    void on_pushButton_people_clicked();
    void on_pushButton_green_clicked();
    void on_pushButton_red_clicked();
    void on_tableView_2_doubleClicked(const QModelIndex &index);
};

#endif // MAINWINDOW_H
