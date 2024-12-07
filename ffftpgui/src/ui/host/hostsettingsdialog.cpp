#include "hostsettingsdialog.hpp"

#include "ffftp_hostdata.h"
#include "ui_hostsettingsdialog.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingsDialog::Private {
 public:
  Private() {}
  ~Private() {}
  Ui::HostSettingsDialog ui;
};

HostSettingsDialog::HostSettingsDialog(const hostdata& hdata, QWidget* parent)
    : QDialog(parent), d_(new Private()) {
  d_->ui.setupUi(this);
  setHostData(hdata);
}

void HostSettingsDialog::setHostData(const hostdata& hdata) {
  // [基本]タブへデータを入力
  HostSettingGeneralForm::Data data_tab_0{
      hdata.general.host_name,      hdata.general.host_adrs,
      hdata.general.username,       hdata.general.password,
      hdata.general.anonymous,      hdata.general.initdir_local,
      hdata.general.initdir_remote, hdata.general.initdir_remote_now,
      hdata.general.enabled_curdir, hdata.general.last_dir,
  };
  d_->ui.tab_0->setData(data_tab_0);
  // [拡張]タブへデータを入力
  HostSettingAdvancedForm::Data data_tab_1{
      hdata.advanced.firewall, hdata.advanced.pasv,    hdata.advanced.syncmove,
      hdata.advanced.port,     hdata.advanced.account, hdata.advanced.timezone,
      hdata.advanced.security, hdata.advanced.initcmd,
  };
  d_->ui.tab_1->setData(data_tab_1);
  // [文字コード]タブへデータを入力
  static const std::map<int, HostSettingKanjiCodeForm::KanjiCode> convtable{
      {KC_NOP, HostSettingKanjiCodeForm::KanjiCode::kNOP},
      {KC_SJIS, HostSettingKanjiCodeForm::KanjiCode::kSJIS},
      {KC_JIS, HostSettingKanjiCodeForm::KanjiCode::kJIS},
      {KC_EUC, HostSettingKanjiCodeForm::KanjiCode::kEUC},
      {KC_UTF8N, HostSettingKanjiCodeForm::KanjiCode::kUTF8N},
      {KC_UTF8BOM, HostSettingKanjiCodeForm::KanjiCode::kUTF8BOM},
  };
  static const std::map<int, HostSettingKanjiCodeForm::KanjiCode>
      convtable_name{
          {KC_AUTO, HostSettingKanjiCodeForm::KanjiCode::kAUTO},
          {KC_SJIS, HostSettingKanjiCodeForm::KanjiCode::kSJIS},
          {KC_JIS, HostSettingKanjiCodeForm::KanjiCode::kJIS},
          {KC_EUC, HostSettingKanjiCodeForm::KanjiCode::kEUC},
          {KC_SMH, HostSettingKanjiCodeForm::KanjiCode::kSMH},
          {KC_SMC, HostSettingKanjiCodeForm::KanjiCode::kSMC},
          {KC_UTF8N, HostSettingKanjiCodeForm::KanjiCode::kUTF8N},
          {KC_UTF8HFSX, HostSettingKanjiCodeForm::KanjiCode::kUTF8HFSX},
      };
  HostSettingKanjiCodeForm::Data data_tab_2{
      convtable.at(hdata.kanjicode.kanjicode),
      hdata.kanjicode.kanacnv,
      convtable_name.at(hdata.kanjicode.kanjicode_name),
      hdata.kanjicode.kanacnv_name,
  };
  d_->ui.tab_2->setData(data_tab_2);
  // [ダイアルアップ]タブへデータを入力
  HostSettingDialupForm::Data data_tab_3;
  data_tab_3.dialup = hdata.dialup.dialup;
  data_tab_3.dial_entries.clear();
  for (int i = 0; i < hdata.dialup.dial_entries_cnt; ++i) {
    data_tab_3.dial_entries.push_back(hdata.dialup.dial_entries[i]);
  }
  data_tab_3.dial_entry = hdata.dialup.dial_entry;
  data_tab_3.dialup_always = hdata.dialup.dialup_always;
  data_tab_3.dialup_notify = hdata.dialup.dialup_notify;
  d_->ui.tab_3->setData(data_tab_3);
}

#define DECL_FORMDATA(T, V) \
  static T::Data data_##V;  \
  data_##V = static_cast<const T::Data&>(d_->ui.V->data());

void HostSettingsDialog::hostData(hostdata& hdata) const {
  // [基本]タブからデータを取得
  DECL_FORMDATA(HostSettingGeneralForm, tab_0);
  hdata.general = {
      .host_name = data_tab_0.host_name.c_str(),
      .host_adrs = data_tab_0.host_adrs.c_str(),
      .username = data_tab_0.username.c_str(),
      .password = data_tab_0.password.c_str(),
      .anonymous = data_tab_0.anonymous,
      .initdir_local = data_tab_0.initdir_local.c_str(),
      .initdir_remote = data_tab_0.initdir_remote.c_str(),
      .initdir_remote_now = data_tab_0.initdir_remote_now.c_str(),
      .last_dir = data_tab_0.last_dir,
  };
  // [拡張]タブからデータを取得
  DECL_FORMDATA(HostSettingAdvancedForm, tab_1);
  hdata.advanced = {
      .firewall = data_tab_1.firewall,
      .pasv = data_tab_1.pasv,
      .syncmove = data_tab_1.syncmove,
      .port = data_tab_1.port,
      .account = data_tab_1.account.c_str(),
      .timezone = data_tab_1.timezone,
      .security = data_tab_1.security,
      .initcmd = data_tab_1.initcmd.c_str(),
  };
  // [文字コード]タブからデータを取得
  static const std::map<HostSettingKanjiCodeForm::KanjiCode, int> convtable{
      {HostSettingKanjiCodeForm::KanjiCode::kNOP, KC_NOP},
      {HostSettingKanjiCodeForm::KanjiCode::kSJIS, KC_SJIS},
      {HostSettingKanjiCodeForm::KanjiCode::kJIS, KC_JIS},
      {HostSettingKanjiCodeForm::KanjiCode::kEUC, KC_EUC},
      {HostSettingKanjiCodeForm::KanjiCode::kUTF8N, KC_UTF8N},
      {HostSettingKanjiCodeForm::KanjiCode::kUTF8BOM, KC_UTF8BOM},
  };
  static const std::map<HostSettingKanjiCodeForm::KanjiCode, int>
      convtable_name{
          {HostSettingKanjiCodeForm::KanjiCode::kAUTO, KC_AUTO},
          {HostSettingKanjiCodeForm::KanjiCode::kSJIS, KC_SJIS},
          {HostSettingKanjiCodeForm::KanjiCode::kJIS, KC_JIS},
          {HostSettingKanjiCodeForm::KanjiCode::kEUC, KC_EUC},
          {HostSettingKanjiCodeForm::KanjiCode::kSMH, KC_SMH},
          {HostSettingKanjiCodeForm::KanjiCode::kSMC, KC_SMC},
          {HostSettingKanjiCodeForm::KanjiCode::kUTF8N, KC_UTF8N},
          {HostSettingKanjiCodeForm::KanjiCode::kUTF8HFSX, KC_UTF8HFSX},
      };
  DECL_FORMDATA(HostSettingKanjiCodeForm, tab_2);
  hdata.kanjicode = {
      .kanjicode = convtable.at(data_tab_2.kanjicode),
      .kanacnv = data_tab_2.kanacnv,
      .kanjicode_name = convtable_name.at(data_tab_2.kanjicode_name),
      .kanacnv_name = data_tab_2.kanacnv_name,
  };
  // [ダイアルアップ]タブからデータを取得
  DECL_FORMDATA(HostSettingDialupForm, tab_3);
  hdata.dialup = {
      .dialup = data_tab_3.dialup,
      .dial_entry = data_tab_3.dial_entry.c_str(),
      .dialup_always = data_tab_3.dialup_always,
      .dialup_notify = data_tab_3.dialup_notify,
  };
}

void HostSettingsDialog::accept() {
  qDebug() << __FUNCTION__ << "called!";
  QDialog::accept();
}

void HostSettingsDialog::help() { qDebug() << __FUNCTION__ << "called!"; }
