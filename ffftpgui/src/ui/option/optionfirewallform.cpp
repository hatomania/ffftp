#include "optionfirewallform.hpp"

#include "ui_optionfirewallform.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionFirewallForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionFirewallForm::Private {
 public:
  Private();
  ~Private();
  Ui::OptionFirewallForm ui;
};
OptionFirewallForm::Private::Private() : ui() {}
OptionFirewallForm::Private::~Private() {}

OptionFirewallForm::Data::Data(){}

OptionFirewallForm::OptionFirewallForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
//  d_->ui.lineEdit_Port->setValidator(new QIntValidator(0, 0xFFFF, this));
}
OptionFirewallForm::~OptionFirewallForm() {}

int OptionFirewallForm::helpID() const {
  return kHelpTopicOptionFirewall;
}

void OptionFirewallForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionFirewallForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
}

void OptionFirewallForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
}
