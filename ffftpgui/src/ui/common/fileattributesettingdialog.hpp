#ifndef FFFTPGUI_UI_COMMON_FILEATTRIBUTESETTINGDIALOG_HPP_
#define FFFTPGUI_UI_COMMON_FILEATTRIBUTESETTINGDIALOG_HPP_

#include <QDialog>

class FileAttributeSettingDialog : public QDialog {
  Q_OBJECT;

 public:
  explicit FileAttributeSettingDialog(QWidget* parent = Q_NULLPTR);
  explicit FileAttributeSettingDialog(int attr, QWidget* parent = Q_NULLPTR);
  virtual ~FileAttributeSettingDialog();
  // 属性値は0-777の"10進数"で返ります
  int attribute() const;

 private:
  void updateAttribute();

 private Q_SLOTS:
  void help();
  void onClick_checkBox_OwnerRead();
  void onClick_checkBox_OtherWrite();
  void onClick_checkBox_OwnerExec();
  void onClick_checkBox_GroupRead();
  void onClick_checkBox_GroupWrite();
  void onClick_checkBox_GroupExec();
  void onClick_checkBox_OtherRead();
  void onClick_checkBox_OwnerWrite();
  void onClick_checkBox_OtherExec();

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(FileAttributeSettingDialog);
};

#endif  // FFFTPGUI_UI_COMMON_FILEATTRIBUTESETTINGDIALOG_HPP_
