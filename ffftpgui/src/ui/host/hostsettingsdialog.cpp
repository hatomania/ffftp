#include "hostsettingsdialog.hpp"

#include "ui_hostsettingsdialog.h"

#include "ffftp.h"
#include "ui/uicommon.h"
#include "generaldatatransceiver.hpp"
#include "advanceddatatransceiver.hpp"
#include "kanjicodedatatransceiver.hpp"
#include "dialupdatatransceiver.hpp"
#include "specialdatatransceiver.hpp"
#include "encryptiondatatransceiver.hpp"
#include "featuredatatransceiver.hpp"

namespace {
enum class Form {
  kGeneral,
  kAdvanced,
  kKanjiCode,
  kDialup,
  kSpecial,
  kEncryption,
  kFeature,
};
}

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingsDialog::Private {
 public:
  Private();
  ~Private();
  Ui::HostSettingsDialog ui;
  std::map<Form, std::unique_ptr<DataTransceiver>> transceiver;
};
HostSettingsDialog::Private::Private() : ui(), transceiver() {}
HostSettingsDialog::Private::~Private() {}

HostSettingsDialog::HostSettingsDialog(const ffftp_hostdata& hdata, QWidget* parent)
    : QDialog(parent), d_(new Private()) {
  d_->ui.setupUi(this);
  MAKE_TRANSCEIVER(Form::kGeneral,
                   HostSettingGeneralFormDataTransceiver,
                   *d_->ui.tab_0);
  MAKE_TRANSCEIVER(Form::kAdvanced,
                   HostSettingAdvancedFormDataTransceiver,
                   *d_->ui.tab_1);
  MAKE_TRANSCEIVER(Form::kKanjiCode,
                   HostSettingKanjiCodeFormDataTransceiver,
                   *d_->ui.tab_2);
  MAKE_TRANSCEIVER(Form::kDialup,
                   HostSettingDialupFormDataTransceiver,
                   *d_->ui.tab_3);
  MAKE_TRANSCEIVER(Form::kSpecial,
                   HostSettingSpecialFormDataTransceiver,
                   *d_->ui.tab_4);
  MAKE_TRANSCEIVER(Form::kEncryption,
                   HostSettingEncryptionFormDataTransceiver,
                   *d_->ui.tab_5);
  MAKE_TRANSCEIVER(Form::kFeature,
                   HostSettingFeatureFormDataTransceiver,
                   *d_->ui.tab_6);
  setHostData(hdata);
  d_->ui.tab_0->firstFocus();
}
HostSettingsDialog::~HostSettingsDialog() {}

void HostSettingsDialog::setHostData(const ffftp_hostdata& hdata) {
  for (auto& [k, form] : d_->transceiver) {
    form->send(&hdata);
  }
}

void HostSettingsDialog::hostData(ffftp_hostdata& hdata) const {
  for (auto& [k, form] : d_->transceiver) {
    form->receive(&hdata);
  }
}

void HostSettingsDialog::accept() {
  QDialog::accept();
}

void HostSettingsDialog::help() {
  BaseForm* form = static_cast<BaseForm*>(d_->ui.tabWidget->currentWidget());
  ffftp_showhelp(form->helpID());
}
