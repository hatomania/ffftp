#pragma once

#include <QtCore/QThread>

class FFFTPThread : public QThread
{
    Q_OBJECT

public:
    explicit FFFTPThread(QWidget *parent = Q_NULLPTR);

private slots:
    void connect(int index);

private:
    class Private;
    Private* d_;
    Q_DISABLE_COPY(FFFTPThread)
};
