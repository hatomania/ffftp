#include <QtWidgets/QApplication>

#include "ffftp.h"
#include "ui/main/mainwindow.hpp"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  // qDebug() << QStyleFactory::keys();
  // QApplication::setStyle(QStyleFactory::create("Fusion"));
  MainWindow w{};
  w.show();
  return a.exec();
}
