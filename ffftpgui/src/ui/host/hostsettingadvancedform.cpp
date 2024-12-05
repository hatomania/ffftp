#include "hostsettingadvancedform.hpp"

#include "ui_hostsettingadvancedform.h"

namespace {
inline const HostSettingAdvancedForm::Data& castData(
    const BaseForm::Data& data) {
  return static_cast<const HostSettingAdvancedForm::Data&>(data);
}
inline HostSettingAdvancedForm::Data& castData(BaseForm::Data& data) {
  return static_cast<HostSettingAdvancedForm::Data&>(data);
}
}  // namespace

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingAdvancedForm::Private {
 public:
  Private();
  ~Private();
  Ui::HostSettingAdvancedForm ui;
};
HostSettingAdvancedForm::Private::Private() {}
HostSettingAdvancedForm::Private::~Private() {}

HostSettingAdvancedForm::Data::Data()
    : firewall(false),
      pasv(false),
      syncmove(false),
      port(0),
      account(),
      timezone(0),
      security(0),
      initcmd() {}

HostSettingAdvancedForm::Data::Data(bool firewall, bool pasv, bool syncmove,
                                    int port, QString account, int timezone,
                                    int security, QString initcmd)
    : firewall(firewall),
      pasv(pasv),
      syncmove(syncmove),
      port(port),
      account(account),
      timezone(timezone),
      security(security),
      initcmd(initcmd) {}

HostSettingAdvancedForm::HostSettingAdvancedForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
HostSettingAdvancedForm ::~HostSettingAdvancedForm() {}

void HostSettingAdvancedForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void HostSettingAdvancedForm::updateUi(const BaseForm::Data& data) {}

void HostSettingAdvancedForm::updateData(BaseForm::Data& data) const {}

void HostSettingAdvancedForm::onClick_pushButton_StdPort() {

}
