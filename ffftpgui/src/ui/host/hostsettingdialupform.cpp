#include "hostsettingdialupform.hpp"

#include "ui_hostsettingdialupform.h"

namespace {
inline const HostSettingDialupForm::Data& castData(const BaseForm::Data& data) {
  return static_cast<const HostSettingDialupForm::Data&>(data);
}
inline HostSettingDialupForm::Data& castData(BaseForm::Data& data) {
  return static_cast<HostSettingDialupForm::Data&>(data);
}
}  // namespace

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingDialupForm::Private {
 public:
  Private();
  ~Private();
  Ui::HostSettingDialupForm ui;
};
HostSettingDialupForm::Private::Private() {}
HostSettingDialupForm::Private::~Private() {}

HostSettingDialupForm::Data::Data() {}

HostSettingDialupForm::HostSettingDialupForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
HostSettingDialupForm ::~HostSettingDialupForm() {}

void HostSettingDialupForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void HostSettingDialupForm::updateUi(const BaseForm::Data& data) {}

void HostSettingDialupForm::updateData(BaseForm::Data& data) const {}
