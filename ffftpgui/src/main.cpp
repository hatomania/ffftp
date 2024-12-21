#include <QtWidgets/QApplication>

#include "ffftp.h"
#include "ui/main/mainwindow.hpp"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  // qDebug() << QStyleFactory::keys();
  // QApplication::setStyle(QStyleFactory::create("Fusion"));
  int ret = 1;
  MainWindow w;
  if (ffftp_initialize(MainWindow::ffftp_proc)) {
    w.show();
    QMetaObject::invokeMethod(&w, &MainWindow::actionConnect);
    ret = a.exec();
  }
  ffftp_finalize();
  return ret;
}
