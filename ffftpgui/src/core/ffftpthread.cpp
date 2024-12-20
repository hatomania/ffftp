#include "ffftpthread.hpp"

#include <QDebug>
#include <QThread>

#include "ffftp.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class FFFTPThread::Private {
 public:
  Private() {}
  ~Private() {}
};

FFFTPThread::FFFTPThread(QObject* parent)
    : QThread(parent), d_(new FFFTPThread::Private()) {}

void FFFTPThread::connect(const void* hc) {
  qDebug() << __FUNCTION__ << " called. " << hc;
  ffftp_connect(const_cast<ffftp_hostcontext_t>(hc));
  qDebug() << __FUNCTION__ << " end.";
}
