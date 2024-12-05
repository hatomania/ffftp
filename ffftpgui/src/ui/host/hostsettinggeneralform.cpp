#include "hostsettinggeneralform.hpp"

#include <QFileDialog>

#include "ui/uicommon.h"
#include "ui_hostsettinggeneralform.h"

namespace {
constexpr const char* const kDefAnonymousUsename = "anonymous";
constexpr const char* const kDefAnonymousPassword = "who@example.com";
inline const HostSettingGeneralForm::Data& castData(
    const BaseForm::Data& data) {
  return static_cast<const HostSettingGeneralForm::Data&>(data);
}
inline HostSettingGeneralForm::Data& castData(BaseForm::Data& data) {
  return static_cast<HostSettingGeneralForm::Data&>(data);
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

// ＜＜slotも隠ぺいしようとしたが失敗＞＞
// コード的には問題ないが、VS用Qtプラグインのmocプレビルドシステムが期待通り動かない
// コード内の"Q_OBJECT"を認識し、このcppもmocしてくれるまではいいが、mocしたcppが生成されない
// 通常mocしたファイル名は"moc_(拡張子を除くファイル名).cpp"となるため、hppをmocしたファイル名と被って上書きされてる可能性があると思い、
// （例えば、hoge.hppを"moc.exe
// hoge.hpp"すると"moc_hoge.cpp"が出力され、"moc.exe
// hoge.cpp"しても"moc_hoge.cpp"が出力される）
// （ちなみにmoc.exeはソースコードを標準出力するだけなので、それをファイルとして保存するVS用Qtプラグインの問題）
// プロジェクトの設定[Qt Meta-Object Compiler]=>[moc]=>[Output File
// Name]を"moc_%(Identity).cpp"してみた
// 期待通りhppをmocしたファイルは"moc_(拡張子を除くファイル名).hpp.cpp"となり、cppをmocしたファイル名と被らなくなると思ったが
// なぜか、期待したcppをmocしたファイル"moc_(拡張子を除くファイル名).cpp.cpp"は生成されず、
// 代わりに（？）"(拡張子を除くファイル名).moc"が生成される
// この.mocファイルをcppとしてコンパイラに通してくれればいいがそんなことはしてくれず結果的にcppから出力したmocのコードはコンパイルできない
// （ちなみにこの"(拡張子を除くファイル名).moc"を手動で"moc_(拡張子を除くファイル名).cpp.cpp"に変更してもコンパイルしてくれなかった）
// 独自のプレビルドで実現できないことはないが、さすがにそこまでするのはな～
// class HostSettingGeneralForm::Private : public QWidget {
//	Q_OBJECT
// public:
//	Private(QWidget* parent = Q_NULLPTR) : QWidget(parent) {}
//	~Private() {}
//	Ui::HostSettingGeneralForm ui;
// public slots:
//	void onClick_pushButton_SelectLocalDir() {
//		qDebug() << __FUNCTION__ << "called!";
//	}
//	void onClick_pushButton_NowDir() {
//		qDebug() << __FUNCTION__ << "called!";
//	}
//};

HostSettingGeneralForm::Data::Data()
    : host_name(),
      host_adrs(),
      username(),
      password(),
      anonymous(false),
      initdir_local(),
      initdir_remote(),
      initdir_remote_now(),
      enabled_curdir(false),
      last_dir(false) {}

HostSettingGeneralForm::Data::Data(
    const std::wstring& host_name, const std::wstring& host_adrs,
    const std::wstring& username, const std::wstring& password, bool anonymous,
    const std::wstring& initdir_local, const std::wstring& initdir_remote,
    const std::wstring& initdir_remote_now, bool enabled_curdir, bool last_dir)
    : host_name(host_name),
      host_adrs(host_adrs),
      username(username),
      password(password),
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

void HostSettingGeneralForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void HostSettingGeneralForm::updateUi(const BaseForm::Data& data) {
  const HostSettingGeneralForm::Data& data_ = castData(data);
  UI_SETTEXT(d_->ui.lineEdit_HostName, QString(data_.host_name));
  UI_SETTEXT(d_->ui.lineEdit_HostAdrs, QString(data_.host_adrs));
  UI_SETTEXT(d_->ui.lineEdit_Username, QString(data_.username));
  UI_SETTEXT(d_->ui.lineEdit_Password, QString(data_.password));
  UI_SETCHECKED(d_->ui.checkBox_Anonymous, data_.anonymous);
  UI_SETTEXT(d_->ui.lineEdit_InitDirLocal, QString(data_.initdir_local));
  UI_SETTEXT(d_->ui.lineEdit_InitDirRemote, QString(data_.initdir_remote));
  UI_SETENABLED(d_->ui.pushButton_CurDir, data_.enabled_curdir);
  UI_SETCHECKED(d_->ui.checkBox_LastDir, data_.last_dir);
}

void HostSettingGeneralForm::updateData(BaseForm::Data& data) const {
  HostSettingGeneralForm::Data& data_ = castData(data);
  UI_TEXT(data_.host_name, d_->ui.lineEdit_HostName).toStdWString();
  UI_TEXT(data_.host_adrs, d_->ui.lineEdit_HostAdrs).toStdWString();
  UI_TEXT(data_.username, d_->ui.lineEdit_Username).toStdWString();
  UI_TEXT(data_.password, d_->ui.lineEdit_Password).toStdWString();
  UI_ISCHECKED(data_.anonymous, d_->ui.checkBox_Anonymous);
  UI_TEXT(data_.initdir_local, d_->ui.lineEdit_InitDirLocal).toStdWString();
  UI_TEXT(data_.initdir_remote, d_->ui.lineEdit_InitDirRemote).toStdWString();
  UI_ISCHECKED(data_.last_dir, d_->ui.checkBox_LastDir);
}

void HostSettingGeneralForm::onClick_toolButton_SelectLocalDir() {
  qDebug() << __FUNCTION__ << "called!";
  QString dirpath = QFileDialog::getExistingDirectory(
      this, "", d_->ui.lineEdit_InitDirLocal->text());
  if (!dirpath.isEmpty()) {
    d_->ui.lineEdit_InitDirLocal->setText(dirpath);
  }
}

void HostSettingGeneralForm::onClick_pushButton_CurDir() {
  qDebug() << __FUNCTION__ << "called!";
  d_->ui.lineEdit_InitDirRemote->setText(QString(mydata().initdir_remote));
}

void HostSettingGeneralForm::onClick_checkBox_Anonymous(bool checked) {
  qDebug() << __FUNCTION__ << "called!";
  static QPair<QString, QString> user_passwd;
  if (checked) {
    UI_TEXT(user_passwd.first, d_->ui.lineEdit_Username);
    UI_TEXT(user_passwd.second, d_->ui.lineEdit_Password);
    UI_SETTEXT(d_->ui.lineEdit_Username, kDefAnonymousUsename);
    UI_SETTEXT(d_->ui.lineEdit_Password, kDefAnonymousPassword);
  } else {
    UI_SETTEXT(d_->ui.lineEdit_Username, user_passwd.first);
    UI_SETTEXT(d_->ui.lineEdit_Password, user_passwd.second);
  }
}

const HostSettingGeneralForm::Data& HostSettingGeneralForm::mydata() const {
  return castData(rawData());
}
