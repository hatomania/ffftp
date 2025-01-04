#ifndef LIBFFFTP_EVENTPROC_HPP_
#define LIBFFFTP_EVENTPROC_HPP_

#include <QThread>
#include <QTimer>

class EventProc : public QThread {
  Q_OBJECT

 public:
  explicit EventProc();
  virtual ~EventProc();

 private:
  std::unique_ptr<QTimer> timer_;

Q_SIGNALS:
  void finising();

private Q_SLOTS:
  void threadStarted();
  void threadFinished();
  void timerWorks();

 private:
  Q_DISABLE_COPY_MOVE(EventProc)
};

#endif  // LIBFFFTP_EVENTPROC_HPP_
