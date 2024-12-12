#include "optiondialog.hpp"

#include "ui_optiondialog.h"

#include "ffftp.h"
#include "ui/uicommon.h"
#include "userdatatransceiver.hpp"
#include "transfer1datatransceiver.hpp"
#include "transfer2datatransceiver.hpp"
#include "transfer3datatransceiver.hpp"
#include "transfer4datatransceiver.hpp"
#include "mirroringdatatransceiver.hpp"
#include "operationdatatransceiver.hpp"
#include "view1datatransceiver.hpp"
#include "view2datatransceiver.hpp"
#include "connectingdatatransceiver.hpp"
#include "firewalldatatransceiver.hpp"
#include "tooldatatransceiver.hpp"
#include "otherdatatransceiver.hpp"

namespace {
enum class Form {
  kUser,
  kTransfer1,
  kTransfer2,
  kTransfer3,
  kTransfer4,
  kMirroring,
  kOperation,
  kView1,
  kView2,
  kConnecting,
  kFirewall,
  kTool,
  kOther,
};
}

class OptionDialog::Private {
 public:
  Private();
  ~Private();
  Ui::OptionDialog ui;
  std::map<Form, std::unique_ptr<DataTransceiver>> transceiver;
};
OptionDialog::Private::Private() : ui(), transceiver() {}
OptionDialog::Private::~Private() {}

OptionDialog::OptionDialog(const ffftp_option& option_, QWidget* parent)
    : QDialog(parent), d_(new Private()) {
  d_->ui.setupUi(this);
  MAKE_TRANSCEIVER(Form::kUser,
                   OptionUserFormDataTransceiver,
                   *d_->ui.tab_00);
  MAKE_TRANSCEIVER(Form::kTransfer1,
                   OptionTransfer1FormDataTransceiver,
                   *d_->ui.tab_01);
  MAKE_TRANSCEIVER(Form::kTransfer2,
                   OptionTransfer2FormDataTransceiver,
                   *d_->ui.tab_02);
  MAKE_TRANSCEIVER(Form::kTransfer3,
                   OptionTransfer3FormDataTransceiver,
                   *d_->ui.tab_03);
  MAKE_TRANSCEIVER(Form::kTransfer4,
                   OptionTransfer4FormDataTransceiver,
                   *d_->ui.tab_04);
  MAKE_TRANSCEIVER(Form::kMirroring,
                   OptionMirroringFormDataTransceiver,
                   *d_->ui.tab_05);
  MAKE_TRANSCEIVER(Form::kOperation,
                   OptionOperationFormDataTransceiver,
                   *d_->ui.tab_06);
  MAKE_TRANSCEIVER(Form::kView1,
                   OptionView1FormDataTransceiver,
                   *d_->ui.tab_07);
  MAKE_TRANSCEIVER(Form::kView2,
                   OptionView2FormDataTransceiver,
                   *d_->ui.tab_08);
  MAKE_TRANSCEIVER(Form::kConnecting,
                   OptionConnectingFormDataTransceiver,
                   *d_->ui.tab_09);
  MAKE_TRANSCEIVER(Form::kFirewall,
                   OptionFirewallFormDataTransceiver,
                   *d_->ui.tab_10);
  MAKE_TRANSCEIVER(Form::kTool,
                   OptionToolFormDataTransceiver,
                   *d_->ui.tab_11);
  MAKE_TRANSCEIVER(Form::kOther,
                   OptionOtherFormDataTransceiver,
                   *d_->ui.tab_12);
  setOption(option_);
}
OptionDialog::~OptionDialog() {}

void OptionDialog::option(ffftp_option& option) const {
  for (auto& [k, form] : d_->transceiver) {
    form->receive(&option);
  }
}

void OptionDialog::setOption(const ffftp_option& option) {
  for (auto& [k, form] : d_->transceiver) {
    form->send(&option);
  }
}

void OptionDialog::accept() { QDialog::accept(); }

void OptionDialog::help() {
  BaseForm* form = static_cast<BaseForm*>(d_->ui.tabWidget->currentWidget());
  ffftp_showhelp(form->helpID());
}
