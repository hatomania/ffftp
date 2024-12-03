#include "hostsettingencryptform.hpp"

#include "stdafx.h"
#include "ui_hostsettingencryptform.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingEncryptForm::Private {
 public:
  Private() {}
  ~Private() {}
  Ui::HostSettingEncryptForm ui;
};

HostSettingEncryptForm::Data::Data()
    : allow_without_encrypt(true),
      is_ftps_explicit(true),
      is_ftps_implicit(true)

{}

HostSettingEncryptForm::HostSettingEncryptForm(QWidget* parent)
    : QWidget(parent), d_(new HostSettingEncryptForm::Private()) {
  d_->ui.setupUi(this);
  setDataAsDefault();
}

void HostSettingEncryptForm::setData(const Data& data) const {
  d_->ui.checkBox_WithoutEncrypt->setChecked(data.allow_without_encrypt);
  d_->ui.checkBox_FTPSExplicit->setChecked(data.is_ftps_explicit);
  d_->ui.checkBox_FTPSImplicit->setChecked(data.is_ftps_implicit);
}

const HostSettingEncryptForm::Data& HostSettingEncryptForm::getData() const {
  static Data data;
  data.allow_without_encrypt = d_->ui.checkBox_WithoutEncrypt->isChecked();
  data.is_ftps_explicit = d_->ui.checkBox_FTPSExplicit->isChecked();
  data.is_ftps_implicit = d_->ui.checkBox_FTPSImplicit->isChecked();
  return data;
}

void HostSettingEncryptForm::setDataAsDefault() const { this->setData(Data()); }
