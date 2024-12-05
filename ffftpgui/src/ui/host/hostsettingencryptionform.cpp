#include "hostsettingencryptionform.hpp"

#include "ui_hostsettingencryptionform.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingEncryptionForm::Private {
 public:
  Private() {}
  ~Private() {}
  Ui::HostSettingEncryptionForm ui;
};

HostSettingEncryptionForm::Data::Data()
    : allow_without_encrypt(true),
      is_ftps_explicit(true),
      is_ftps_implicit(true)

{}

HostSettingEncryptionForm::HostSettingEncryptionForm(QWidget* parent)
    : QWidget(parent), d_(new HostSettingEncryptionForm::Private()) {
  d_->ui.setupUi(this);
  setDataAsDefault();
}

void HostSettingEncryptionForm::setData(const Data& data) const {
  d_->ui.checkBox_WithoutEncrypt->setChecked(data.allow_without_encrypt);
  d_->ui.checkBox_FTPSExplicit->setChecked(data.is_ftps_explicit);
  d_->ui.checkBox_FTPSImplicit->setChecked(data.is_ftps_implicit);
}

const HostSettingEncryptionForm::Data& HostSettingEncryptionForm::getData() const {
  static Data data;
  data.allow_without_encrypt = d_->ui.checkBox_WithoutEncrypt->isChecked();
  data.is_ftps_explicit = d_->ui.checkBox_FTPSExplicit->isChecked();
  data.is_ftps_implicit = d_->ui.checkBox_FTPSImplicit->isChecked();
  return data;
}

void HostSettingEncryptionForm::setDataAsDefault() const { this->setData(Data()); }
