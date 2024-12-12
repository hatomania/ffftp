#include "optiontransfer1form.hpp"

#include "ui_optiontransfer1form.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionTransfer1Form::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionTransfer1Form::Private {
 public:
  Private();
  ~Private();
  Ui::OptionTransfer1Form ui;
};
OptionTransfer1Form::Private::Private() : ui() {}
OptionTransfer1Form::Private::~Private() {}

OptionTransfer1Form::Data::Data(){}

OptionTransfer1Form::OptionTransfer1Form(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
//  d_->ui.lineEdit_Port->setValidator(new QIntValidator(0, 0xFFFF, this));
}
OptionTransfer1Form::~OptionTransfer1Form() {}

int OptionTransfer1Form::helpID() const {
  return kHelpTopicOptionTransfer1;
}

void OptionTransfer1Form::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionTransfer1Form::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
}

void OptionTransfer1Form::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
}
