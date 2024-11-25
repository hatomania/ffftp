#include "ffftpthread.hpp"
#include "stdafx.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class FFFTPThread::Private {
public:
    Private() {}
    ~Private() {}
};

FFFTPThread::FFFTPThread(QWidget* parent)
    : QThread(parent), d_(new FFFTPThread::Private())
{
}

void FFFTPThread::connect(int index) {
    qDebug() << __FUNCTION__ << " called.";
    ffftp_connect(index);
    qDebug() << __FUNCTION__ << " end.";
}
