#include "eventproc.hpp"

#include <QTimerEvent>

#include "common.h"

extern LRESULT CallFtpWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

EventProc::EventProc()
    : QObject{Q_NULLPTR},
      thread_{},
      timer1id_{0},
      timer2id_{0} {
  moveToThread(&thread_);
  thread_.start();
  thread_.setPriority(QThread::LowestPriority);
}

EventProc::~EventProc() {
  thread_.exit();
  thread_.wait();
}

void EventProc::setupTimer() {
  timer1id_ = startTimer(1000);
  timer2id_ = startTimer(100);
}

void EventProc::timerEvent(QTimerEvent* e) {
  const auto timerid{e->timerId()};
  if (timerid == timer1id_) {
    CallFtpWndProc(0, WM_TIMER, 1, 0);
  } else if (timerid == timer2id_) {
    CallFtpWndProc(0, WM_TIMER, 2, 0);
  }
}
