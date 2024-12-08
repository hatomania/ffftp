#include "hostsettingfeatureform.hpp"

#include "ui_hostsettingfeatureform.h"

namespace {
using ThisData = HostSettingFeatureForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
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

void HostSettingFeatureForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
}

void HostSettingFeatureForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
}
