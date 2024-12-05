#include "hostsettingfeatureform.hpp"

#include "ui_hostsettingfeatureform.h"

namespace {
inline const HostSettingFeatureForm::Data& castData(const BaseForm::Data& data) {
  return static_cast<const HostSettingFeatureForm::Data&>(data);
}
inline HostSettingFeatureForm::Data& castData(BaseForm::Data& data) {
  return static_cast<HostSettingFeatureForm::Data&>(data);
}
}  // namespace

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingFeatureForm::Private {
 public:
  Private();
  ~Private();
  Ui::HostSettingFeatureForm ui;
};
HostSettingFeatureForm::Private::Private() {}
HostSettingFeatureForm::Private::~Private() {}

HostSettingFeatureForm::Data::Data() {}

HostSettingFeatureForm::HostSettingFeatureForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
HostSettingFeatureForm ::~HostSettingFeatureForm() {}

void HostSettingFeatureForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void HostSettingFeatureForm::updateUi(const BaseForm::Data& data) {}

void HostSettingFeatureForm::updateData(BaseForm::Data& data) const {}
