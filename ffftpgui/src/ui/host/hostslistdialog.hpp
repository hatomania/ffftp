#pragma once

#include <QDialog>

class HostsListDialog : public QDialog {
  Q_OBJECT

 public:
  explicit HostsListDialog(QWidget* parent = Q_NULLPTR);
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
  class Private;
  Private* d_;
  Q_DISABLE_COPY(HostsListDialog)
};
