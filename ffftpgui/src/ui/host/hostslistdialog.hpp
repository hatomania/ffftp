﻿#ifndef FFFTPGUI_UI_HOST_HOSTSLISTDIALOG_HPP_
#define FFFTPGUI_UI_HOST_HOSTSLISTDIALOG_HPP_

#include <QDialog>

#include "ffftp_hostdata.h"

class HostsListDialog : public QDialog {
  Q_OBJECT

 public:
  explicit HostsListDialog(QWidget* parent = Q_NULLPTR);
  virtual ~HostsListDialog();
  int connectingHostIndex();

 public slots:
  void accept() override;
  void onClick_pushButton_NewHost();
  void onClick_pushButton_NewGroup();
  void onClick_pushButton_Mod();
  void onClick_pushButton_Copy();
  void onClick_pushButton_Del();
  void onClick_pushButton_Up();
  void onClick_pushButton_Down();
  void onClick_pushButton_Default();
  void onClick_pushButton_Help();
  void selectedHost(const QModelIndex& index);

 private:
  bool showSettingDialog(hostdata& in_out_data);

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY(HostsListDialog)
};

#endif  // FFFTPGUI_UI_HOST_HOSTSLISTDIALOG_HPP_
