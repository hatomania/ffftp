#include "optiontransfer2form.hpp"

#include "ui_optiontransfer2form.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionTransfer2Form::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionTransfer2Form::Private {
 public:
  Private();
  ~Private();
  Ui::OptionTransfer2Form ui;
};
OptionTransfer2Form::Private::Private() : ui() {}
OptionTransfer2Form::Private::~Private() {}

OptionTransfer2Form::Data::Data(){}

OptionTransfer2Form::OptionTransfer2Form(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
//  d_->ui.lineEdit_Port->setValidator(new QIntValidator(0, 0xFFFF, this));
}
OptionTransfer2Form::~OptionTransfer2Form() {}

int OptionTransfer2Form::helpID() const {
  return kHelpTopicOptionTransfer2;
}

void OptionTransfer2Form::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionTransfer2Form::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
}

void OptionTransfer2Form::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
}
