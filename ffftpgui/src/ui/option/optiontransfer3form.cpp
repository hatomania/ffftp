#include "optiontransfer3form.hpp"

#include "ui_optiontransfer3form.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionTransfer3Form::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionTransfer3Form::Private {
 public:
  Private();
  ~Private();
  Ui::OptionTransfer3Form ui;
};
OptionTransfer3Form::Private::Private() : ui() {}
OptionTransfer3Form::Private::~Private() {}

OptionTransfer3Form::Data::Data(){}

OptionTransfer3Form::OptionTransfer3Form(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
//  d_->ui.lineEdit_Port->setValidator(new QIntValidator(0, 0xFFFF, this));
}
OptionTransfer3Form::~OptionTransfer3Form() {}

int OptionTransfer3Form::helpID() const {
  return kHelpTopicOptionTransfer3;
}

void OptionTransfer3Form::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionTransfer3Form::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
}

void OptionTransfer3Form::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
}
