#include "hostsettinggeneralform.hpp"

#include <QFileDialog>

#include "ui_hostsettinggeneralform.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
constexpr const char* const kDefAnonymousUsename = "anonymous";
using ThisData = HostSettingGeneralForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingGeneralForm::Private {
 public:
  Private();
  ~Private();
  Ui::HostSettingGeneralForm ui;
};
HostSettingGeneralForm::Private::Private() {}
HostSettingGeneralForm::Private::~Private() {}

HostSettingGeneralForm::Data::Data()
    : host_name(),
      host_adrs(),
      username(),
      password(),
      anonymous_password(),
      anonymous(false),
      initdir_local(),
      initdir_remote(),
      initdir_remote_now(),
      enabled_curdir(false),
      last_dir(false) {}

HostSettingGeneralForm::Data::Data(
    const std::wstring& host_name,
    const std::wstring& host_adrs,
    const std::wstring& username,
    const std::wstring& password,
    const std::wstring& anonymous_password,
    bool anonymous,
    const std::wstring& initdir_local,
    const std::wstring& initdir_remote,
    const std::wstring& initdir_remote_now,
    bool enabled_curdir,
    bool last_dir)
    : host_name(host_name),
      host_adrs(host_adrs),
      username(username),
      password(password),
      anonymous_password(anonymous_password),
      anonymous(anonymous),
      initdir_local(initdir_local),
      initdir_remote(initdir_remote),
      initdir_remote_now(initdir_remote_now),
      enabled_curdir(enabled_curdir),
      last_dir(last_dir) {}

HostSettingGeneralForm::HostSettingGeneralForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);

  // slots隠ぺいの残骸
  // QObject::connect(d_->ui.pushButton_NowDir, SIGNAL(clicked()), d_,
  // SLOT(onClick_pushButton_NowDir()));
}
HostSettingGeneralForm::~HostSettingGeneralForm() {}

void HostSettingGeneralForm::firstFocus() const {
  d_->ui.lineEdit_HostName->setFocus();
  d_->ui.lineEdit_HostName->selectAll();
}

int HostSettingGeneralForm::helpID() const {
  return kHelpTopicHostSettingGeneral;
}

void HostSettingGeneralForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void HostSettingGeneralForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  UI_SETTEXT(d_->ui.lineEdit_HostName, QString(data_in.host_name));
  UI_SETTEXT(d_->ui.lineEdit_HostAdrs, QString(data_in.host_adrs));
  UI_SETTEXT(d_->ui.lineEdit_Username, QString(data_in.username));
  UI_SETTEXT(d_->ui.lineEdit_Password, QString(data_in.password));
  UI_SETCHECKED(d_->ui.checkBox_Anonymous, data_in.anonymous);
  UI_SETTEXT(d_->ui.lineEdit_InitDirLocal, QString(data_in.initdir_local));
  UI_SETTEXT(d_->ui.lineEdit_InitDirRemote, QString(data_in.initdir_remote));
  UI_SETENABLED(d_->ui.pushButton_CurDir, data_in.enabled_curdir);
  UI_SETCHECKED(d_->ui.checkBox_LastDir, data_in.last_dir);
}

void HostSettingGeneralForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  UI_TEXT(data_out.host_name, d_->ui.lineEdit_HostName).toStdWString();
  UI_TEXT(data_out.host_adrs, d_->ui.lineEdit_HostAdrs).toStdWString();
  UI_TEXT(data_out.username, d_->ui.lineEdit_Username).toStdWString();
  UI_TEXT(data_out.password, d_->ui.lineEdit_Password).toStdWString();
  UI_ISCHECKED(data_out.anonymous, d_->ui.checkBox_Anonymous);
  UI_TEXT(data_out.initdir_local, d_->ui.lineEdit_InitDirLocal).toStdWString();
  UI_TEXT(data_out.initdir_remote, d_->ui.lineEdit_InitDirRemote).toStdWString();
  UI_ISCHECKED(data_out.last_dir, d_->ui.checkBox_LastDir);
}

void HostSettingGeneralForm::onClick_toolButton_SelectLocalDir() {
  QString dirpath = QFileDialog::getExistingDirectory(
      this, "", d_->ui.lineEdit_InitDirLocal->text());
  if (!dirpath.isEmpty()) {
    d_->ui.lineEdit_InitDirLocal->setText(dirpath);
  }
}

void HostSettingGeneralForm::onClick_pushButton_CurDir() {
  d_->ui.lineEdit_InitDirRemote->setText(QString(thisData().initdir_remote));
}

void HostSettingGeneralForm::onClick_checkBox_Anonymous(bool checked) {
  static QPair<QString, QString> user_passwd;
  if (checked) {
    UI_TEXT(user_passwd.first, d_->ui.lineEdit_Username);
    UI_TEXT(user_passwd.second, d_->ui.lineEdit_Password);
    UI_SETTEXT(d_->ui.lineEdit_Username, kDefAnonymousUsename);
    UI_SETTEXT(d_->ui.lineEdit_Password, QString(thisData().anonymous_password));
  } else {
    UI_SETTEXT(d_->ui.lineEdit_Username, user_passwd.first);
    UI_SETTEXT(d_->ui.lineEdit_Password, user_passwd.second);
  }
}

const HostSettingGeneralForm::Data& HostSettingGeneralForm::thisData() const {
  return castData(rawData());
}
