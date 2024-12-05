#include "hostsettingkanjicodeform.hpp"

#include "ui_hostsettingkanjicodeform.h"

namespace {
inline const HostSettingKanjiCodeForm::Data& castData(const BaseForm::Data& data) {
  return static_cast<const HostSettingKanjiCodeForm::Data&>(data);
}
inline HostSettingKanjiCodeForm::Data& castData(BaseForm::Data& data) {
  return static_cast<HostSettingKanjiCodeForm::Data&>(data);
}
}  // namespace

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingKanjiCodeForm::Private {
 public:
  Private();
  ~Private();
  Ui::HostSettingKanjiCodeForm ui;
};
HostSettingKanjiCodeForm::Private::Private() {}
HostSettingKanjiCodeForm::Private::~Private() {}

HostSettingKanjiCodeForm::Data::Data() {}

HostSettingKanjiCodeForm::HostSettingKanjiCodeForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
HostSettingKanjiCodeForm ::~HostSettingKanjiCodeForm() {}

void HostSettingKanjiCodeForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void HostSettingKanjiCodeForm::updateUi(const BaseForm::Data& data) {}

void HostSettingKanjiCodeForm::updateData(BaseForm::Data& data) const {}
