#include "mainwindow.hpp"
#include "stdafx.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //qDebug() << QStyleFactory::keys();
    //QApplication::setStyle(QStyleFactory::create("Fusion"));
    int ret = 1;
    MainWindow w;
    if (ffftp_initialize()) {
        w.show();
        QMetaObject::invokeMethod(&w, &MainWindow::actionConnect);
        ret = a.exec();
    }
    ffftp_finalize();
    return ret;
}
