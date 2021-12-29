#pragma once

#include <QtWidgets/QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

protected:

private slots:
    void timerEvent(QTimerEvent* event) override;
    void connect();

private:
    class Private;
    Private* d_;
    Q_DISABLE_COPY(MainWindow)
};
