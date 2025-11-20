/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action1;
    QAction *action2;
    QAction *action3;
    QAction *action4;
    QAction *action5;
    QAction *action6;
    QAction *action7;
    QWidget *WidgetPainter;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *page_2;
    QLabel *label_show_2;
    QPushButton *pushButton_photo_2;
    QPushButton *pushButton_camera_2;
    QPushButton *pushButton_getphoto;
    QLabel *label_camera_status_2;
    QLabel *label_12;
    QPushButton *pushButton_register;
    QLabel *label_24;
    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_id_3;
    QLabel *label_25;
    QLabel *label_show_4;
    QWidget *page_3;
    QTableView *tableView_2;
    QLabel *label_alter_name;
    QLabel *label_check_name;
    QLabel *label_check_id;
    QLineEdit *lineEdit_newname;
    QLabel *label_show_3;
    QPushButton *pushButton_query;
    QPushButton *pushButton_delete;
    QPushButton *pushButton_update;
    QPushButton *pushButton_queryall;
    QLineEdit *lineEdit_name_2;
    QLineEdit *lineEdit_id;
    QLabel *label_14;
    QWidget *page_4;
    QLabel *label_16;
    QTableView *tableView_3;
    QPushButton *pushButton_today;
    QPushButton *pushButton_people;
    QPushButton *pushButton_green;
    QPushButton *pushButton_red;
    QLineEdit *lineEdit_id_2;
    QLabel *label_alter_name_3;
    QLabel *label_check_id_3;
    QLabel *label_check_name_3;
    QLineEdit *lineEdit_name_3;
    QLineEdit *lineEdit_date;
    QWidget *page;
    QLabel *label_show;
    QPushButton *pushButton_camera;
    QPushButton *pushButton_photo;
    QLabel *label_4;
    QComboBox *comboBox_confidence;
    QLineEdit *lineEdit_threshold;
    QPushButton *pushButton_setconfidence;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_camera_status;
    QLabel *label_datetime;
    QLabel *label_detectnum;
    QLabel *label_recognizenum;
    QLabel *label_recognizetime;
    QTableView *tableView;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1400, 730);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        action1 = new QAction(MainWindow);
        action1->setObjectName(QString::fromUtf8("action1"));
        action2 = new QAction(MainWindow);
        action2->setObjectName(QString::fromUtf8("action2"));
        action3 = new QAction(MainWindow);
        action3->setObjectName(QString::fromUtf8("action3"));
        action4 = new QAction(MainWindow);
        action4->setObjectName(QString::fromUtf8("action4"));
        action5 = new QAction(MainWindow);
        action5->setObjectName(QString::fromUtf8("action5"));
        action6 = new QAction(MainWindow);
        action6->setObjectName(QString::fromUtf8("action6"));
        action7 = new QAction(MainWindow);
        action7->setObjectName(QString::fromUtf8("action7"));
        WidgetPainter = new QWidget(MainWindow);
        WidgetPainter->setObjectName(QString::fromUtf8("WidgetPainter"));
        gridLayout = new QGridLayout(WidgetPainter);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        stackedWidget = new QStackedWidget(WidgetPainter);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setFrameShape(QFrame::Box);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        label_show_2 = new QLabel(page_2);
        label_show_2->setObjectName(QString::fromUtf8("label_show_2"));
        label_show_2->setGeometry(QRect(30, 60, 640, 480));
        label_show_2->setFrameShape(QFrame::Box);
        label_show_2->setAlignment(Qt::AlignCenter);
        pushButton_photo_2 = new QPushButton(page_2);
        pushButton_photo_2->setObjectName(QString::fromUtf8("pushButton_photo_2"));
        pushButton_photo_2->setGeometry(QRect(490, 570, 171, 61));
        QFont font;
        font.setPointSize(16);
        pushButton_photo_2->setFont(font);
        pushButton_camera_2 = new QPushButton(page_2);
        pushButton_camera_2->setObjectName(QString::fromUtf8("pushButton_camera_2"));
        pushButton_camera_2->setGeometry(QRect(40, 570, 171, 61));
        pushButton_camera_2->setFont(font);
        pushButton_getphoto = new QPushButton(page_2);
        pushButton_getphoto->setObjectName(QString::fromUtf8("pushButton_getphoto"));
        pushButton_getphoto->setEnabled(false);
        pushButton_getphoto->setGeometry(QRect(270, 570, 171, 61));
        pushButton_getphoto->setFont(font);
        label_camera_status_2 = new QLabel(page_2);
        label_camera_status_2->setObjectName(QString::fromUtf8("label_camera_status_2"));
        label_camera_status_2->setGeometry(QRect(180, 20, 61, 40));
        label_camera_status_2->setFont(font);
        label_12 = new QLabel(page_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(30, 20, 155, 40));
        label_12->setFont(font);
        pushButton_register = new QPushButton(page_2);
        pushButton_register->setObjectName(QString::fromUtf8("pushButton_register"));
        pushButton_register->setGeometry(QRect(960, 570, 171, 61));
        pushButton_register->setFont(font);
        label_24 = new QLabel(page_2);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(870, 60, 131, 40));
        label_24->setFont(font);
        lineEdit_name = new QLineEdit(page_2);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(990, 170, 200, 61));
        lineEdit_name->setFont(font);
        lineEdit_id_3 = new QLineEdit(page_2);
        lineEdit_id_3->setObjectName(QString::fromUtf8("lineEdit_id_3"));
        lineEdit_id_3->setGeometry(QRect(990, 50, 200, 61));
        lineEdit_id_3->setFont(font);
        label_25 = new QLabel(page_2);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(870, 180, 131, 40));
        label_25->setFont(font);
        label_show_4 = new QLabel(page_2);
        label_show_4->setObjectName(QString::fromUtf8("label_show_4"));
        label_show_4->setGeometry(QRect(930, 310, 240, 180));
        label_show_4->setFrameShape(QFrame::Box);
        label_show_4->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        tableView_2 = new QTableView(page_3);
        tableView_2->setObjectName(QString::fromUtf8("tableView_2"));
        tableView_2->setGeometry(QRect(30, 59, 640, 551));
        QFont font1;
        font1.setPointSize(14);
        tableView_2->setFont(font1);
        label_alter_name = new QLabel(page_3);
        label_alter_name->setObjectName(QString::fromUtf8("label_alter_name"));
        label_alter_name->setGeometry(QRect(710, 330, 181, 51));
        QFont font2;
        font2.setPointSize(18);
        label_alter_name->setFont(font2);
        label_check_name = new QLabel(page_3);
        label_check_name->setObjectName(QString::fromUtf8("label_check_name"));
        label_check_name->setGeometry(QRect(710, 90, 131, 31));
        label_check_name->setFont(font2);
        label_check_id = new QLabel(page_3);
        label_check_id->setObjectName(QString::fromUtf8("label_check_id"));
        label_check_id->setGeometry(QRect(710, 220, 151, 31));
        label_check_id->setFont(font2);
        lineEdit_newname = new QLineEdit(page_3);
        lineEdit_newname->setObjectName(QString::fromUtf8("lineEdit_newname"));
        lineEdit_newname->setGeometry(QRect(880, 330, 200, 51));
        lineEdit_newname->setFont(font);
        label_show_3 = new QLabel(page_3);
        label_show_3->setObjectName(QString::fromUtf8("label_show_3"));
        label_show_3->setGeometry(QRect(700, 430, 240, 180));
        label_show_3->setFrameShape(QFrame::Box);
        label_show_3->setAlignment(Qt::AlignCenter);
        pushButton_query = new QPushButton(page_3);
        pushButton_query->setObjectName(QString::fromUtf8("pushButton_query"));
        pushButton_query->setGeometry(QRect(1150, 70, 171, 61));
        pushButton_query->setFont(font);
        pushButton_delete = new QPushButton(page_3);
        pushButton_delete->setObjectName(QString::fromUtf8("pushButton_delete"));
        pushButton_delete->setGeometry(QRect(1150, 200, 171, 61));
        pushButton_delete->setFont(font);
        pushButton_update = new QPushButton(page_3);
        pushButton_update->setObjectName(QString::fromUtf8("pushButton_update"));
        pushButton_update->setGeometry(QRect(1150, 330, 171, 61));
        pushButton_update->setFont(font);
        pushButton_queryall = new QPushButton(page_3);
        pushButton_queryall->setObjectName(QString::fromUtf8("pushButton_queryall"));
        pushButton_queryall->setGeometry(QRect(1150, 460, 171, 61));
        pushButton_queryall->setFont(font);
        lineEdit_name_2 = new QLineEdit(page_3);
        lineEdit_name_2->setObjectName(QString::fromUtf8("lineEdit_name_2"));
        lineEdit_name_2->setGeometry(QRect(880, 80, 200, 51));
        lineEdit_name_2->setFont(font);
        lineEdit_id = new QLineEdit(page_3);
        lineEdit_id->setObjectName(QString::fromUtf8("lineEdit_id"));
        lineEdit_id->setGeometry(QRect(880, 210, 200, 51));
        lineEdit_id->setFont(font);
        label_14 = new QLabel(page_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(290, 20, 171, 40));
        QFont font3;
        font3.setPointSize(20);
        label_14->setFont(font3);
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        label_16 = new QLabel(page_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(300, 20, 111, 40));
        label_16->setFont(font3);
        tableView_3 = new QTableView(page_4);
        tableView_3->setObjectName(QString::fromUtf8("tableView_3"));
        tableView_3->setGeometry(QRect(30, 59, 640, 551));
        tableView_3->setFont(font1);
        pushButton_today = new QPushButton(page_4);
        pushButton_today->setObjectName(QString::fromUtf8("pushButton_today"));
        pushButton_today->setGeometry(QRect(1130, 100, 211, 61));
        pushButton_today->setFont(font);
        pushButton_people = new QPushButton(page_4);
        pushButton_people->setObjectName(QString::fromUtf8("pushButton_people"));
        pushButton_people->setGeometry(QRect(1130, 230, 211, 61));
        pushButton_people->setFont(font);
        pushButton_green = new QPushButton(page_4);
        pushButton_green->setObjectName(QString::fromUtf8("pushButton_green"));
        pushButton_green->setGeometry(QRect(1130, 360, 211, 61));
        pushButton_green->setFont(font);
        pushButton_red = new QPushButton(page_4);
        pushButton_red->setObjectName(QString::fromUtf8("pushButton_red"));
        pushButton_red->setGeometry(QRect(1130, 490, 211, 61));
        pushButton_red->setFont(font);
        lineEdit_id_2 = new QLineEdit(page_4);
        lineEdit_id_2->setObjectName(QString::fromUtf8("lineEdit_id_2"));
        lineEdit_id_2->setGeometry(QRect(880, 370, 200, 51));
        lineEdit_id_2->setFont(font);
        label_alter_name_3 = new QLabel(page_4);
        label_alter_name_3->setObjectName(QString::fromUtf8("label_alter_name_3"));
        label_alter_name_3->setGeometry(QRect(710, 370, 181, 51));
        label_alter_name_3->setFont(font2);
        label_check_id_3 = new QLabel(page_4);
        label_check_id_3->setObjectName(QString::fromUtf8("label_check_id_3"));
        label_check_id_3->setGeometry(QRect(710, 250, 151, 31));
        label_check_id_3->setFont(font2);
        label_check_name_3 = new QLabel(page_4);
        label_check_name_3->setObjectName(QString::fromUtf8("label_check_name_3"));
        label_check_name_3->setGeometry(QRect(710, 110, 131, 31));
        label_check_name_3->setFont(font2);
        lineEdit_name_3 = new QLineEdit(page_4);
        lineEdit_name_3->setObjectName(QString::fromUtf8("lineEdit_name_3"));
        lineEdit_name_3->setGeometry(QRect(880, 240, 200, 51));
        lineEdit_name_3->setFont(font);
        lineEdit_date = new QLineEdit(page_4);
        lineEdit_date->setObjectName(QString::fromUtf8("lineEdit_date"));
        lineEdit_date->setGeometry(QRect(880, 100, 200, 51));
        lineEdit_date->setFont(font);
        stackedWidget->addWidget(page_4);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        label_show = new QLabel(page);
        label_show->setObjectName(QString::fromUtf8("label_show"));
        label_show->setGeometry(QRect(30, 60, 640, 480));
        label_show->setFrameShape(QFrame::Box);
        label_show->setLineWidth(1);
        label_show->setAlignment(Qt::AlignCenter);
        pushButton_camera = new QPushButton(page);
        pushButton_camera->setObjectName(QString::fromUtf8("pushButton_camera"));
        pushButton_camera->setGeometry(QRect(70, 570, 171, 61));
        pushButton_camera->setFont(font);
        pushButton_photo = new QPushButton(page);
        pushButton_photo->setObjectName(QString::fromUtf8("pushButton_photo"));
        pushButton_photo->setGeometry(QRect(390, 570, 171, 61));
        pushButton_photo->setFont(font);
        label_4 = new QLabel(page);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(380, 20, 71, 40));
        label_4->setFont(font);
        comboBox_confidence = new QComboBox(page);
        comboBox_confidence->setObjectName(QString::fromUtf8("comboBox_confidence"));
        comboBox_confidence->setEnabled(true);
        comboBox_confidence->setGeometry(QRect(730, 460, 241, 61));
        comboBox_confidence->setFont(font);
        comboBox_confidence->setStyleSheet(QString::fromUtf8(""));
        comboBox_confidence->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
        lineEdit_threshold = new QLineEdit(page);
        lineEdit_threshold->setObjectName(QString::fromUtf8("lineEdit_threshold"));
        lineEdit_threshold->setGeometry(QRect(800, 570, 171, 61));
        lineEdit_threshold->setFont(font);
        pushButton_setconfidence = new QPushButton(page);
        pushButton_setconfidence->setObjectName(QString::fromUtf8("pushButton_setconfidence"));
        pushButton_setconfidence->setGeometry(QRect(1030, 570, 251, 61));
        pushButton_setconfidence->setFont(font);
        label_5 = new QLabel(page);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(710, 20, 151, 40));
        label_5->setFont(font);
        label_6 = new QLabel(page);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(920, 20, 151, 40));
        label_6->setFont(font);
        label_7 = new QLabel(page);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(1140, 20, 151, 40));
        label_7->setFont(font);
        label_8 = new QLabel(page);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 20, 155, 40));
        label_8->setFont(font);
        label_8->setStyleSheet(QString::fromUtf8(""));
        label_camera_status = new QLabel(page);
        label_camera_status->setObjectName(QString::fromUtf8("label_camera_status"));
        label_camera_status->setGeometry(QRect(180, 20, 61, 40));
        label_camera_status->setFont(font);
        label_datetime = new QLabel(page);
        label_datetime->setObjectName(QString::fromUtf8("label_datetime"));
        label_datetime->setGeometry(QRect(450, 20, 231, 40));
        label_datetime->setFont(font);
        label_detectnum = new QLabel(page);
        label_detectnum->setObjectName(QString::fromUtf8("label_detectnum"));
        label_detectnum->setGeometry(QRect(860, 20, 31, 40));
        label_detectnum->setFont(font);
        label_recognizenum = new QLabel(page);
        label_recognizenum->setObjectName(QString::fromUtf8("label_recognizenum"));
        label_recognizenum->setGeometry(QRect(1070, 20, 31, 40));
        label_recognizenum->setFont(font);
        label_recognizetime = new QLabel(page);
        label_recognizetime->setObjectName(QString::fromUtf8("label_recognizetime"));
        label_recognizetime->setGeometry(QRect(1290, 20, 61, 40));
        label_recognizetime->setFont(font);
        tableView = new QTableView(page);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(710, 60, 640, 480));
        stackedWidget->addWidget(page);
        comboBox_confidence->raise();
        label_show->raise();
        pushButton_camera->raise();
        pushButton_photo->raise();
        label_4->raise();
        lineEdit_threshold->raise();
        pushButton_setconfidence->raise();
        label_5->raise();
        label_6->raise();
        label_7->raise();
        label_8->raise();
        label_camera_status->raise();
        label_datetime->raise();
        label_detectnum->raise();
        label_recognizenum->raise();
        label_recognizetime->raise();
        tableView->raise();

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(WidgetPainter);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1400, 49));
        menuBar->setFont(font3);
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu->setFont(font3);
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_2->setFont(font3);
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(action1);
        menu->addSeparator();
        menu->addAction(action2);
        menu->addSeparator();
        menu->addAction(action3);
        menu->addSeparator();
        menu->addAction(action4);
        menu_2->addAction(action5);
        menu_2->addSeparator();
        menu_2->addAction(action6);
        menu_2->addSeparator();
        menu_2->addAction(action7);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);
        comboBox_confidence->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        action1->setText(QApplication::translate("MainWindow", "\344\272\272\350\204\270\350\257\206\345\210\253", 0, QApplication::UnicodeUTF8));
        action2->setText(QApplication::translate("MainWindow", "\344\272\272\350\204\270\345\275\225\345\205\245", 0, QApplication::UnicodeUTF8));
        action3->setText(QApplication::translate("MainWindow", "\344\272\272\350\204\270\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
        action4->setText(QApplication::translate("MainWindow", "\344\277\241\346\201\257\347\273\237\350\256\241", 0, QApplication::UnicodeUTF8));
        action5->setText(QApplication::translate("MainWindow", "\350\223\235\350\211\262\344\270\273\351\242\230", 0, QApplication::UnicodeUTF8));
        action6->setText(QApplication::translate("MainWindow", "\351\273\221\350\211\262\344\270\273\351\242\230", 0, QApplication::UnicodeUTF8));
        action7->setText(QApplication::translate("MainWindow", "\347\201\260\350\211\262\344\270\273\351\242\230", 0, QApplication::UnicodeUTF8));
        label_show_2->setText(QString());
        pushButton_photo_2->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\345\233\276\347\211\207", 0, QApplication::UnicodeUTF8));
        pushButton_camera_2->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257\346\221\204\345\203\217\345\244\264", 0, QApplication::UnicodeUTF8));
        pushButton_getphoto->setText(QApplication::translate("MainWindow", "\346\213\215\347\205\247", 0, QApplication::UnicodeUTF8));
        label_camera_status_2->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "\346\221\204\345\203\217\345\244\264\347\212\266\346\200\201\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton_register->setText(QApplication::translate("MainWindow", "\345\275\225\345\205\245", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("MainWindow", "\350\276\223\345\205\245id\357\274\232", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("MainWindow", "\350\276\223\345\205\245\345\247\223\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_show_4->setText(QString());
        label_alter_name->setText(QApplication::translate("MainWindow", "\350\276\223\345\205\245\346\226\260\347\232\204\345\247\223\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_check_name->setText(QApplication::translate("MainWindow", "\350\276\223\345\205\245\345\247\223\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_check_id->setText(QApplication::translate("MainWindow", "\350\276\223\345\205\245\344\272\272\350\204\270id\357\274\232", 0, QApplication::UnicodeUTF8));
        label_show_3->setText(QString());
        pushButton_query->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242\344\272\272\350\204\270", 0, QApplication::UnicodeUTF8));
        pushButton_delete->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\344\272\272\350\204\270", 0, QApplication::UnicodeUTF8));
        pushButton_update->setText(QApplication::translate("MainWindow", "\344\277\256\346\224\271\345\247\223\345\220\215", 0, QApplication::UnicodeUTF8));
        pushButton_queryall->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242\346\211\200\346\234\211\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "\344\272\272\350\204\270\346\225\260\346\215\256\350\241\250", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MainWindow", "\344\277\241\346\201\257\350\241\250", 0, QApplication::UnicodeUTF8));
        pushButton_today->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242\345\275\223\345\244\251\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        pushButton_people->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242\344\270\252\344\272\272\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        pushButton_green->setText(QApplication::translate("MainWindow", "\347\273\277\347\240\201\350\256\260\345\275\225\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        pushButton_red->setText(QApplication::translate("MainWindow", "\347\272\242\347\240\201\350\256\260\345\275\225\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        label_alter_name_3->setText(QApplication::translate("MainWindow", "\350\276\223\345\205\245\344\272\272\350\204\270id\357\274\232", 0, QApplication::UnicodeUTF8));
        label_check_id_3->setText(QApplication::translate("MainWindow", "\350\276\223\345\205\245\345\247\223\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_check_name_3->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\346\227\245\346\234\237\357\274\232", 0, QApplication::UnicodeUTF8));
        label_show->setText(QString());
        pushButton_camera->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257\346\221\204\345\203\217\345\244\264", 0, QApplication::UnicodeUTF8));
        pushButton_photo->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\345\233\276\347\211\207", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "\346\227\266\351\227\264\357\274\232", 0, QApplication::UnicodeUTF8));
        comboBox_confidence->clear();
        comboBox_confidence->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\344\275\231\345\274\246\347\233\270\344\274\274\345\272\246(%)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "\346\254\247\346\260\217\350\267\235\347\246\273(%)", 0, QApplication::UnicodeUTF8)
        );
        lineEdit_threshold->setText(QApplication::translate("MainWindow", "50", 0, QApplication::UnicodeUTF8));
        pushButton_setconfidence->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\347\275\256\344\277\241\345\272\246(%)", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "\346\243\200\346\265\213\344\272\272\350\204\270\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "\350\257\206\345\210\253\344\272\272\350\204\270\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "\350\257\206\345\210\253\346\227\266\351\227\264ms\357\274\232", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "\346\221\204\345\203\217\345\244\264\347\212\266\346\200\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_camera_status->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
        label_datetime->setText(QApplication::translate("MainWindow", "2022.06.22 17:30", 0, QApplication::UnicodeUTF8));
        label_detectnum->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_recognizenum->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_recognizetime->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "  \344\272\272\350\204\270\346\223\215\344\275\234   ", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("MainWindow", "  \344\270\273\351\242\230\350\256\276\347\275\256   ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
