#include "optiontransfer4form.hpp"

#include "ui_optiontransfer4form.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionTransfer4Form::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionTransfer4Form::Private {
 public:
  Private();
  ~Private();
  Ui::OptionTransfer4Form ui;
};
OptionTransfer4Form::Private::Private() : ui() {}
OptionTransfer4Form::Private::~Private() {}

OptionTransfer4Form::Data::Data(){}

OptionTransfer4Form::OptionTransfer4Form(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
//  d_->ui.lineEdit_Port->setValidator(new QIntValidator(0, 0xFFFF, this));
}
OptionTransfer4Form::~OptionTransfer4Form() {}

int OptionTransfer4Form::helpID() const {
  return kHelpTopicOptionTransfer4;
}

void OptionTransfer4Form::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionTransfer4Form::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
}

void OptionTransfer4Form::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
}
