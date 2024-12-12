#include "optionmirroringform.hpp"

#include "ui_optionmirroringform.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionMirroringForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionMirroringForm::Private {
 public:
  Private();
  ~Private();
  Ui::OptionMirroringForm ui;
};
OptionMirroringForm::Private::Private() : ui() {}
OptionMirroringForm::Private::~Private() {}

OptionMirroringForm::Data::Data(){}

OptionMirroringForm::OptionMirroringForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
//  d_->ui.lineEdit_Port->setValidator(new QIntValidator(0, 0xFFFF, this));
}
OptionMirroringForm::~OptionMirroringForm() {}

int OptionMirroringForm::helpID() const {
  return kHelpTopicOptionMirroring;
}

void OptionMirroringForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionMirroringForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
}

void OptionMirroringForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
}
