#include "mainwindow.hpp"
#include "hostslistdialog.hpp"
#include "ui_mainwindow.h"
#include "stdafx.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class MainWindow::Private {
public:
    Private() {}
    ~Private() {}
    Ui::MainWindowClass ui;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), d_(new MainWindow::Private())
{
    d_->ui.setupUi(this);
    startTimer(500);
    emit timerEvent(nullptr);
}

void MainWindow::timerEvent(QTimerEvent* event) {
    qDebug() << __FUNCTION__ << " called.";
    QString msg = QString::fromWCharArray(ffftp_gettaskmessage());
    if (!msg.isEmpty()) {
        d_->ui.widget->addTaskMessage(msg);
    }
}

void MainWindow::connect()
{
    qDebug() << __FUNCTION__ << " called.";
    if (HostsListDialog(this).exec() == QDialog::Rejected) {
        qDebug() << "Rejected.";
    }
}
