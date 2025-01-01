#ifndef LIBFFFTP_EVENTPROC_HPP_
#define LIBFFFTP_EVENTPROC_HPP_

#include <QThread>

class EventProc : public QObject {
  Q_OBJECT

 public:
  explicit EventProc();
  virtual ~EventProc();

  void setupTimer();

 protected:
  void timerEvent(QTimerEvent* e);

 private:
  QThread thread_;
  int timer1id_;
  int timer2id_;

 private:
  Q_DISABLE_COPY_MOVE(EventProc)
};

#endif  // LIBFFFTP_EVENTPROC_HPP_
