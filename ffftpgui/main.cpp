#include "mainwindow.hpp"
#include "stdafx.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ffftp_initialize();
    MainWindow w;
    w.setWindowTitle(QString::fromWCharArray(ffftp_get_window_title()));
    w.show();
    QMetaObject::invokeMethod(&w, "connect");
    int ret = a.exec();
    ffftp_finalize();
    return ret;
}
