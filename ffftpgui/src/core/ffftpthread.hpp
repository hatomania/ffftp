#ifndef FFFTPGUI_CORE_FFFTPTHREAD_HPP_
#define FFFTPGUI_CORE_FFFTPTHREAD_HPP_

#include <QThread>

class FFFTPThread : public QThread {
  Q_OBJECT

 public:
  explicit FFFTPThread();

 Q_SIGNALS:
  void inited(bool);

 public Q_SLOTS:
  void initFFFTP();
  void connect(const void* hc);

 private:
  Q_DISABLE_COPY(FFFTPThread)
};

#endif  // FFFTPGUI_CORE_FFFTPTHREAD_HPP_
