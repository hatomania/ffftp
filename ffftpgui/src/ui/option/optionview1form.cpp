#include "optionview1form.hpp"

#include "ui_optionview1form.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionView1Form::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionView1Form::Private {
 public:
  Private();
  ~Private();
  Ui::OptionView1Form ui;
};
OptionView1Form::Private::Private() : ui() {}
OptionView1Form::Private::~Private() {}

OptionView1Form::Data::Data(){}

OptionView1Form::OptionView1Form(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
//  d_->ui.lineEdit_Port->setValidator(new QIntValidator(0, 0xFFFF, this));
}
OptionView1Form::~OptionView1Form() {}

int OptionView1Form::helpID() const {
  return kHelpTopicOptionView1;
}

void OptionView1Form::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionView1Form::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
}

void OptionView1Form::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
}
