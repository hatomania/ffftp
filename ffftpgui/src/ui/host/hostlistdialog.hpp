#ifndef FFFTPGUI_UI_HOST_HOSTLISTDIALOG_HPP_
#define FFFTPGUI_UI_HOST_HOSTLISTDIALOG_HPP_

#include <QDialog>
#include <QModelIndex>
#include <QString>

#include "ffftp.h"

class HostListDialog : public QDialog {
  Q_OBJECT

 public:
  explicit HostListDialog(QWidget* parent = Q_NULLPTR);
  virtual ~HostListDialog();
  const hostcontext_t hostcontext() const;

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
  void onClick_treeView_HostList(QModelIndex);

 private:
  bool showSettingDialog(hostdata& in_out_data);
  void updateEnabled();
  bool askGroupName(QString& group_name, const QString& title);

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY(HostListDialog)
};

#endif  // FFFTPGUI_UI_HOST_HOSTLISTDIALOG_HPP_
