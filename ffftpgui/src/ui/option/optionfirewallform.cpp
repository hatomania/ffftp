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

OptionFirewallForm::Data::Data()
    : type(0),
      host(),
      port(0),
      username(),
      password(),
      delimiter(0),
      security(0),
      resolve(false),
      lower(false),
      fwall_default(false),
      pasv_default(false),
      no_save_user(false) {}

OptionFirewallForm::Data::Data(
  int type,
  std::wstring host,
  int port,
  std::wstring username,
  std::wstring password,
  wchar_t delimiter,
  int security,
  bool resolve,
  bool lower,
  bool fwall_default,
  bool pasv_default,
  bool no_save_user)
    : type(type),
      host(host),
      port(port),
      username(username),
      password(password),
      delimiter(delimiter),
      security(security),
      resolve(resolve),
      lower(lower),
      fwall_default(fwall_default),
      pasv_default(pasv_default),
      no_save_user(no_save_user) {}

OptionFirewallForm::OptionFirewallForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
  d_->ui.lineEdit_FwallPort->setValidator(new QIntValidator(0, 0xFFFF, this));
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
  static const std::map<int, int> wmap{
      {1, 0}, {2, 1}, {8, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {9, 8},
  };
  UI_SETCURRENTINDEX(d_->ui.comboBox_FwallType, wmap.at(data_in.type));
  UI_SETTEXT(d_->ui.lineEdit_FwallHost, QString(data_in.host));
  UI_SETTEXT(d_->ui.lineEdit_FwallPort, QString::number(data_in.port));
  UI_SETTEXT(d_->ui.lineEdit_FwallUser, QString(data_in.username));
  UI_SETTEXT(d_->ui.lineEdit_FwallPass, QString(data_in.password));
  UI_SETTEXT(d_->ui.lineEdit_FwallDelimiter, QString(data_in.delimiter));
  UI_SETCURRENTINDEX(d_->ui.comboBox_FwallSecurity, data_in.security);
  UI_SETCHECKED(d_->ui.checkBox_FwallResolve, data_in.resolve);
  UI_SETCHECKED(d_->ui.checkBox_FwallLower, data_in.lower);
  UI_SETCHECKED(d_->ui.checkBox_FwallDefault, data_in.fwall_default);
  UI_SETCHECKED(d_->ui.checkBox_PasvDefault, data_in.pasv_default);
  UI_SETCHECKED(d_->ui.checkBox_FwallNoSaveUser, data_in.no_save_user);
  updateEnabled();
}

void OptionFirewallForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  static const std::vector<int> wmap{
      1, 2, 8, 3, 4, 5, 6, 7, 9,
  };
  data_out.type = wmap.at(d_->ui.comboBox_FwallType->currentIndex());
  UI_TEXT(data_out.host, d_->ui.lineEdit_FwallHost).toStdWString();
  UI_TEXT(data_out.port, d_->ui.lineEdit_FwallPort).toInt();
  UI_TEXT(data_out.username, d_->ui.lineEdit_FwallUser).toStdWString();
  UI_TEXT(data_out.password, d_->ui.lineEdit_FwallPass).toStdWString();
  const QString& delimiter = d_->ui.lineEdit_FwallDelimiter->text();
  data_out.delimiter = delimiter.isEmpty() ? L'@' : *delimiter.toStdWString().begin();
  UI_CURRENTINDEX(data_out.security, d_->ui.comboBox_FwallSecurity);
  UI_ISCHECKED(data_out.resolve, d_->ui.checkBox_FwallResolve);
  UI_ISCHECKED(data_out.lower, d_->ui.checkBox_FwallLower);
  UI_ISCHECKED(data_out.fwall_default, d_->ui.checkBox_FwallDefault);
  UI_ISCHECKED(data_out.pasv_default, d_->ui.checkBox_PasvDefault);
  UI_ISCHECKED(data_out.no_save_user, d_->ui.checkBox_FwallNoSaveUser);
}

void OptionFirewallForm::updateEnabled() {
  const std::vector<std::pair<QWidget*, QWidget*>> tw{
    {d_->ui.label_FwallUser, d_->ui.lineEdit_FwallUser}, // 0
    {d_->ui.label_FwallPass, d_->ui.lineEdit_FwallPass}, // 1
    {d_->ui.label_FwallDelimiter, d_->ui.lineEdit_FwallDelimiter}, // 2
    {d_->ui.label_FwallSecurity, d_->ui.comboBox_FwallSecurity}, // 3
    {nullptr, d_->ui.checkBox_FwallResolve}, // 4
    {nullptr, d_->ui.checkBox_FwallLower}, // 5
  };
  static const std::vector<std::vector<int>> ti{
    { 2, 4 },
    { 4, 5 },
    { 2, 4, 5 },
    { 0, 1, 3, 4, 5 },
    { 0, 1, 2, 3, 4 },
    { 1, 2, 3, 4, 5 },
    { 0, 1, 2, 3, 5 },
    { 2, 3, 5 },
    { 3, 4 },
  };
  for (const auto& w : tw) {
    if (w.first)  { UI_SETENABLED(w.first,  true); }
    if (w.second) { UI_SETENABLED(w.second, true); }
  }
  for (const auto& i : ti.at(d_->ui.comboBox_FwallType->currentIndex())) {
    if (tw.at(i).first)  { UI_SETENABLED(tw.at(i).first,  false); }
    if (tw.at(i).second) { UI_SETENABLED(tw.at(i).second, false); }
  }
}

void OptionFirewallForm::onCurrentIndexChange_comboBox_FwallType() { updateEnabled(); }
