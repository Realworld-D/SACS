#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    MainWindow w;
    w.setWindowTitle("SACS");
    w.setWindowIcon(QIcon("image/icon.png"));
    w.show();

    return a.exec();
}
