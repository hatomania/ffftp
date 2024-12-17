#ifndef FFFTPGUI_UI_COMMON_FILEANDATTRIBUTESETTINGDIALOG_HPP_
#define FFFTPGUI_UI_COMMON_FILEANDATTRIBUTESETTINGDIALOG_HPP_

#include <QDialog>

class FileAndAttributeSettingDialog : public QDialog {
  Q_OBJECT;

 public:
  explicit FileAndAttributeSettingDialog(QWidget* parent = Q_NULLPTR);
  virtual ~FileAndAttributeSettingDialog();
  void fileAndAttribute(QString& fname, int& attr) const;

 private Q_SLOTS:
  void onClick_toolButton_EditAttr();

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(FileAndAttributeSettingDialog);
};

#endif  // FFFTPGUI_UI_COMMON_FILEANDATTRIBUTESETTINGDIALOG_HPP_
