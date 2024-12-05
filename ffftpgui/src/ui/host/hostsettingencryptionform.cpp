#include "hostsettingencryptionform.hpp"

#include "ui_hostsettingencryptionform.h"

namespace {
inline const HostSettingEncryptionForm::Data& castData(const BaseForm::Data& data) {
  return static_cast<const HostSettingEncryptionForm::Data&>(data);
}
inline HostSettingEncryptionForm::Data& castData(BaseForm::Data& data) {
  return static_cast<HostSettingEncryptionForm::Data&>(data);
}
}  // namespace

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingEncryptionForm::Private {
 public:
  Private();
  ~Private();
  Ui::HostSettingEncryptionForm ui;
};
HostSettingEncryptionForm::Private::Private() {}
HostSettingEncryptionForm::Private::~Private() {}

HostSettingEncryptionForm::Data::Data() {}

HostSettingEncryptionForm::HostSettingEncryptionForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
HostSettingEncryptionForm ::~HostSettingEncryptionForm() {}

void HostSettingEncryptionForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void HostSettingEncryptionForm::updateUi(const BaseForm::Data& data) {}

void HostSettingEncryptionForm::updateData(BaseForm::Data& data) const {}
