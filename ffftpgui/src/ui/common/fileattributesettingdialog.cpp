#include "fileattributesettingdialog.hpp"

#include <QIntValidator>

#include "ui_fileattributesettingdialog.h"

#include "ffftp.h"
#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
inline int attributeWeighting(const QCheckBox& cb, int weight) {
  return cb.isChecked() ? weight : 0;
}
}  // namespace

class FileAttributeSettingDialog::Private {
 public:
  Private();
  ~Private();
  Ui::FileAttributeSettingDialog ui;
};
FileAttributeSettingDialog::Private::Private() : ui() {}
FileAttributeSettingDialog::Private::~Private() {}

FileAttributeSettingDialog::FileAttributeSettingDialog(QWidget* parent)
    : QDialog(parent), d_(new Private()) {
  d_->ui.setupUi(this);
  d_->ui.lineEdit_CurrentAttr->setValidator(new QIntValidator(0, 777, this));
  d_->ui.lineEdit_CurrentAttr->setFocus();
  d_->ui.lineEdit_CurrentAttr->selectAll();
}
FileAttributeSettingDialog::FileAttributeSettingDialog(int attr, QWidget* parent)
    : FileAttributeSettingDialog(parent) {
  int _attr = attr > 777 ? 777 : attr;
  int attr16 = std::stoi(QString::number(_attr).toStdWString(), nullptr, 16);
  UI_SETCHECKED(d_->ui.checkBox_OtherExec,  attr16 & 0x0001);
  UI_SETCHECKED(d_->ui.checkBox_OtherWrite, attr16 & 0x0002);
  UI_SETCHECKED(d_->ui.checkBox_OtherRead,  attr16 & 0x0004);
  UI_SETCHECKED(d_->ui.checkBox_GroupExec,  attr16 & 0x0010);
  UI_SETCHECKED(d_->ui.checkBox_GroupWrite, attr16 & 0x0020);
  UI_SETCHECKED(d_->ui.checkBox_GroupRead,  attr16 & 0x0040);
  UI_SETCHECKED(d_->ui.checkBox_OwnerExec,  attr16 & 0x0100);
  UI_SETCHECKED(d_->ui.checkBox_OwnerWrite, attr16 & 0x0200);
  UI_SETCHECKED(d_->ui.checkBox_OwnerRead,  attr16 & 0x0400);
  updateAttribute();
}
FileAttributeSettingDialog::~FileAttributeSettingDialog() {}

int FileAttributeSettingDialog::attribute() const {
  return d_->ui.lineEdit_CurrentAttr->text().toInt();
}

void FileAttributeSettingDialog::updateAttribute() {
  int attribute = 
    attributeWeighting(*d_->ui.checkBox_OtherExec,  0x0001) +
    attributeWeighting(*d_->ui.checkBox_OtherWrite, 0x0002) +
    attributeWeighting(*d_->ui.checkBox_OtherRead,  0x0004) +
    attributeWeighting(*d_->ui.checkBox_GroupExec,  0x0010) +
    attributeWeighting(*d_->ui.checkBox_GroupWrite, 0x0020) +
    attributeWeighting(*d_->ui.checkBox_GroupRead,  0x0040) +
    attributeWeighting(*d_->ui.checkBox_OwnerExec,  0x0100) +
    attributeWeighting(*d_->ui.checkBox_OwnerWrite, 0x0200) +
    attributeWeighting(*d_->ui.checkBox_OwnerRead,  0x0400);
  UI_SETTEXT(d_->ui.lineEdit_CurrentAttr, QString("%1").arg(attribute, 3, 16, QChar('0')));
}

void FileAttributeSettingDialog::help() {
  ffftp_showhelp(kHelpTopicAttrSetting);
}

void FileAttributeSettingDialog::onClick_checkBox_OwnerRead()  { updateAttribute(); }
void FileAttributeSettingDialog::onClick_checkBox_OtherWrite() { updateAttribute(); }
void FileAttributeSettingDialog::onClick_checkBox_OwnerExec()  { updateAttribute(); }
void FileAttributeSettingDialog::onClick_checkBox_GroupRead()  { updateAttribute(); }
void FileAttributeSettingDialog::onClick_checkBox_GroupWrite() { updateAttribute(); }
void FileAttributeSettingDialog::onClick_checkBox_GroupExec()  { updateAttribute(); }
void FileAttributeSettingDialog::onClick_checkBox_OtherRead()  { updateAttribute(); }
void FileAttributeSettingDialog::onClick_checkBox_OwnerWrite() { updateAttribute(); }
void FileAttributeSettingDialog::onClick_checkBox_OtherExec()  { updateAttribute(); }
