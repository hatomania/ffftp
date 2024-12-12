#include "optiontoolform.hpp"

#include "ui_optiontoolform.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionToolForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionToolForm::Private {
 public:
  Private();
  ~Private();
  Ui::OptionToolForm ui;
};
OptionToolForm::Private::Private() : ui() {}
OptionToolForm::Private::~Private() {}

OptionToolForm::Data::Data(){}

OptionToolForm::OptionToolForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
//  d_->ui.lineEdit_Port->setValidator(new QIntValidator(0, 0xFFFF, this));
}
OptionToolForm::~OptionToolForm() {}

int OptionToolForm::helpID() const {
  return kHelpTopicOptionTool;
}

void OptionToolForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionToolForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
}

void OptionToolForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
}
