#pragma once

#include <QThread>

class FFFTPThread : public QThread {
  Q_OBJECT

 public:
  explicit FFFTPThread(QObject* parent = Q_NULLPTR);

 public slots:
  void connect(int index);

 private:
  class Private;
  Private* d_;
  Q_DISABLE_COPY(FFFTPThread)
};
