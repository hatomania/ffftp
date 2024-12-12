#include "optionconnectingform.hpp"

#include "ui_optionconnectingform.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionConnectingForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionConnectingForm::Private {
 public:
  Private();
  ~Private();
  Ui::OptionConnectingForm ui;
};
OptionConnectingForm::Private::Private() : ui() {}
OptionConnectingForm::Private::~Private() {}

OptionConnectingForm::Data::Data(){}

OptionConnectingForm::OptionConnectingForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
//  d_->ui.lineEdit_Port->setValidator(new QIntValidator(0, 0xFFFF, this));
}
OptionConnectingForm::~OptionConnectingForm() {}

int OptionConnectingForm::helpID() const {
  return kHelpTopicOptionConnecting;
}

void OptionConnectingForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionConnectingForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
}

void OptionConnectingForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
}
