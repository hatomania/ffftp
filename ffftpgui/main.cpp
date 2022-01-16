#include "mainwindow.hpp"
#include "stdafx.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //qDebug() << QStyleFactory::keys();
    //QApplication::setStyle(QStyleFactory::create("Fusion"));
    ffftp_initialize();
    MainWindow w;
    w.show();
    QMetaObject::invokeMethod(&w, &MainWindow::actionConnect);
    int ret = a.exec();
    ffftp_finalize();
    return ret;
}
