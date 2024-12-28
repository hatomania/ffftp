#include <QDebug>
#include <QObject>
#include <QThread>

class Transfer : public QObject {
  Q_OBJECT
 public:
  Transfer() = delete;
  inline explicit Transfer(int id) : QObject(Q_NULLPTR), id_(id) {
    moveToThread(&thread_);
    thread_.setPriority(QThread::LowestPriority);
    thread_.start();
  }
  inline virtual ~Transfer() {
    thread_.exit();
    thread_.wait();
  }

 private Q_SLOTS:
  inline int transfer() {
    qDebug() << __FUNCTION__ << " called. id=" << id_ << " thread_id=" << QThread::currentThreadId();
    return 0;
  }

 private:
  int id_;
  QThread thread_;
};
