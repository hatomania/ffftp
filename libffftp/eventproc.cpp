#include "eventproc.hpp"

#include <QTimerEvent>

#include "common.h"

namespace libffftp {
extern LRESULT CallFtpWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
}

EventProc::EventProc()
    : QThread{Q_NULLPTR},
      timer_{} {
  QObject::connect(this, SIGNAL(started()), this, SLOT(threadStarted()), Qt::DirectConnection);
  QObject::connect(this, SIGNAL(finished()), this, SLOT(threadFinished()), Qt::DirectConnection);
  start();
  setPriority(QThread::LowestPriority);
}

EventProc::~EventProc() {
}

void EventProc::threadStarted() {
  timer_.reset();
  timer_ = std::make_unique<QTimer>();
  QObject::connect(timer_.get(), SIGNAL(timeout()), this, SLOT(timerWorks()));
  timer_->moveToThread(this);
  timer_->start(1000);
}

void EventProc::threadFinished() {
  timer_->stop();
  timer_.reset();
}

void EventProc::timerWorks() {
  qDebug() << __FUNCTION__;
  libffftp::CallFtpWndProc(0, WM_TIMER, 1, 0);
}
