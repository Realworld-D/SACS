#-------------------------------------------------
#
# Project created by QtCreator 2022-06-05T00:12:24
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = SACS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    recognize.cpp \
    mtcnn.cpp

HEADERS  += mainwindow.h \
    recognize.h \
    mtcnn.h \
    head.h

FORMS    += mainwindow.ui

LIBS += -L$$PWD/x86_opencv/lib -lncnn -lopencv_core -lopencv_highgui -lopencv_ml -lopencv_imgcodecs -lopencv_imgproc -lopencv_videostab -lopencv_photo -lopencv_shape -lopencv_stitching -lopencv_videoio -lopencv_video -lopencv_superres -lopencv_objdetect -lopencv_flann -lopencv_features2d -lopencv_calib3d -latomic

INCLUDEPATH += $$PWD/x86_opencv/include
DEPENDPATH += $$PWD/x86_opencv/lib

INCLUDEPATH += $$PWD/ncnn-20200106/src

DISTFILES +=

RESOURCES += \
    qrc/font.qrc \
    qrc/main.qrc \
    qrc/qm.qrc \
    qrc/qss.qrc
