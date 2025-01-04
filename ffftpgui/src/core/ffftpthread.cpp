#include "ffftpthread.hpp"

#include <QDebug>
#include <QThread>

#include "ffftp.h"
#include "ui/main/mainwindow.hpp"

FFFTPThread::FFFTPThread() : QThread(Q_NULLPTR) {
  moveToThread(this);
  start();
}

void FFFTPThread::initFFFTP() {
  qDebug() << __FUNCTION__ << "pid=" << QThread::currentThreadId();
  bool ret{ffftp_initialize(MainWindow::ffftp_proc)};
  emit inited(ret);
}

void FFFTPThread::connect(const void* hc) {
  qDebug() << __FUNCTION__ << " called. " << hc;
  ffftp_connect(const_cast<ffftp_hostcontext_t>(hc));
  qDebug() << __FUNCTION__ << " end.";
}
