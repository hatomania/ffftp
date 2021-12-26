#pragma once

#include <QtWidgets/QDialog>
#include "ui_hostslistdialog.h"

class HostsListDialog : public QDialog
{
    Q_OBJECT

public:
	HostsListDialog(QWidget *parent = Q_NULLPTR);

private:
    Ui::HostsListDialogClass ui;
};
