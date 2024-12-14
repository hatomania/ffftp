#include "optionoperationform.hpp"

#include "ui_optionoperationform.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionOperationForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionOperationForm::Private {
 public:
  Private();
  ~Private();
  Ui::OptionOperationForm ui;
};
OptionOperationForm::Private::Private() : ui() {}
OptionOperationForm::Private::~Private() {}

OptionOperationForm::Data::Data(){}

OptionOperationForm::OptionOperationForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
OptionOperationForm::~OptionOperationForm() {}

int OptionOperationForm::helpID() const {
  return kHelpTopicOptionOperation;
}

void OptionOperationForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionOperationForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
}

void OptionOperationForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
}
