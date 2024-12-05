#include "hostsettingspecialform.hpp"

#include "ui_hostsettingspecialform.h"

namespace {
inline const HostSettingSpecialForm::Data& castData(const BaseForm::Data& data) {
  return static_cast<const HostSettingSpecialForm::Data&>(data);
}
inline HostSettingSpecialForm::Data& castData(BaseForm::Data& data) {
  return static_cast<HostSettingSpecialForm::Data&>(data);
}
}  // namespace

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingSpecialForm::Private {
 public:
  Private();
  ~Private();
  Ui::HostSettingSpecialForm ui;
};
HostSettingSpecialForm::Private::Private() {}
HostSettingSpecialForm::Private::~Private() {}

HostSettingSpecialForm::Data::Data() {}

HostSettingSpecialForm::HostSettingSpecialForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
HostSettingSpecialForm ::~HostSettingSpecialForm() {}

void HostSettingSpecialForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void HostSettingSpecialForm::updateUi(const BaseForm::Data& data) {}

void HostSettingSpecialForm::updateData(BaseForm::Data& data) const {}
