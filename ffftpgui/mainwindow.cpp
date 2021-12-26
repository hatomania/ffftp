#include "mainwindow.hpp"
#include "hostslistdialog.hpp"
#include <QDebug>
#include "stdafx.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void MainWindow::connect()
{
	qDebug() << __FUNCTION__ << " called.";
	//qDebug() << HostsListDialog(this).exec() == QDialog::DialogCode::Rejected ? "Rejected" : "";
	if (HostsListDialog(this).exec() == QDialog::Rejected) {
		qDebug() << "Rejected.";
	}
}
