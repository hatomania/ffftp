#include "optionotherform.hpp"

#include "ui_optionotherform.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionOtherForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionOtherForm::Private {
 public:
  Private();
  ~Private();
  Ui::OptionOtherForm ui;
};
OptionOtherForm::Private::Private() : ui() {}
OptionOtherForm::Private::~Private() {}

OptionOtherForm::Data::Data(){}

OptionOtherForm::OptionOtherForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
//  d_->ui.lineEdit_Port->setValidator(new QIntValidator(0, 0xFFFF, this));
}
OptionOtherForm::~OptionOtherForm() {}

int OptionOtherForm::helpID() const {
  return kHelpTopicOptionOther;
}

void OptionOtherForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionOtherForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
}

void OptionOtherForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
}
