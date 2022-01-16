#pragma once

#include <QtWidgets/QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR);
    virtual ~MainWindow();

protected:
    void timerEvent(QTimerEvent* event) override;

private slots:
    void connect();
    bool askSaveCryptFunc();

private:
    class Private;
    Private* d_;
    Q_DISABLE_COPY(MainWindow)
};
