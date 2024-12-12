#include "optionuserform.hpp"

#include "ui_optionuserform.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionUserForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionUserForm::Private {
 public:
  Private();
  ~Private();
  Ui::OptionUserForm ui;
};
OptionUserForm::Private::Private() : ui() {}
OptionUserForm::Private::~Private() {}

OptionUserForm::Data::Data(){}

OptionUserForm::OptionUserForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
//  d_->ui.lineEdit_Port->setValidator(new QIntValidator(0, 0xFFFF, this));
}
OptionUserForm::~OptionUserForm() {}

int OptionUserForm::helpID() const {
  return kHelpTopicOptionUser;
}

void OptionUserForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionUserForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
}

void OptionUserForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
}
