#pragma once

#include <QtWidgets/QDialog>

class HostsListDialog : public QDialog
{
    Q_OBJECT

public:
	explicit HostsListDialog(QWidget *parent = Q_NULLPTR);

public slots:
	void selectedHost(const QModelIndex& index);

private:
	class Private;
	Private* d_;
	Q_DISABLE_COPY(HostsListDialog)
};
