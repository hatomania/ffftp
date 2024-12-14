#include "fileandattributesettingdialog.hpp"

#include <QIntValidator>

#include "ui_fileandattributesettingdialog.h"

#include "ui/uicommon.h"
#include "fileattributesettingdialog.hpp"

class FileAndAttributeSettingDialog::Private {
 public:
  Private();
  ~Private();
  Ui::FileAndAttributeSettingDialog ui;
};
FileAndAttributeSettingDialog::Private::Private() : ui() {}
FileAndAttributeSettingDialog::Private::~Private() {}

FileAndAttributeSettingDialog::FileAndAttributeSettingDialog(QWidget* parent)
    : QDialog(parent), d_(new Private()) {
  d_->ui.setupUi(this);
  d_->ui.lineEdit_Attr->setValidator(new QIntValidator(0, 777, this));
  d_->ui.lineEdit_Fname->setFocus();
  d_->ui.lineEdit_Fname->selectAll();
}
FileAndAttributeSettingDialog::~FileAndAttributeSettingDialog() {}

void FileAndAttributeSettingDialog::fileAndAttribute(QString& fname, int& attr) const {
  UI_TEXT(fname, d_->ui.lineEdit_Fname);
  UI_TEXT(attr, d_->ui.lineEdit_Attr).toInt();
}

void FileAndAttributeSettingDialog::onClick_toolButton_EditAttr() {
  FileAttributeSettingDialog dialog{d_->ui.lineEdit_Attr->text().toInt(), this};
  if (dialog.exec() == QDialog::Accepted) {
    int _attr = dialog.attribute();
    UI_SETTEXT(d_->ui.lineEdit_Attr, QString("%1").arg(dialog.attribute(), 3, 10, QChar('0')));
    d_->ui.lineEdit_Attr->setFocus();
    d_->ui.lineEdit_Attr->selectAll();
  }
}
