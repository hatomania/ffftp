#include "mainwindow.hpp"
#include "hostslistdialog.hpp"
#include "stdafx.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void MainWindow::connect()
{
    qDebug() << __FUNCTION__ << " called.";
    if (HostsListDialog(this).exec() == QDialog::Rejected) {
        qDebug() << "Rejected.";
    }
}
