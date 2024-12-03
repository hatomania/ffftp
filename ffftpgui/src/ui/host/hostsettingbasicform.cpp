#include "hostsettingbasicform.hpp"

#include "stdafx.h"
#include "ui_hostsettingbasicform.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingBasicForm::Private {
 public:
  Private() {}
  ~Private() = default;
  Ui::HostSettingBasicForm ui;
  QString initdir_remote;
};

namespace {
constexpr const char* const kDefAnonymousUsename = "anonymous";
constexpr const char* const kDefAnonymousPassword = "who@example.com";
}  // namespace

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
// class HostSettingBasicForm::Private : public QWidget {
//	Q_OBJECT
// public:
//	Private(QWidget* parent = Q_NULLPTR) : QWidget(parent) {}
//	~Private() {}
//	Ui::HostSettingBasicForm ui;
// public slots:
//	void onClick_pushButton_SelectLocalDir() {
//		qDebug() << __FUNCTION__ << "called!";
//	}
//	void onClick_pushButton_NowDir() {
//		qDebug() << __FUNCTION__ << "called!";
//	}
//};

HostSettingBasicForm::Data::Data()
    : settingname(kEmptyString),
      hostaddr(kEmptyString),
      username(kEmptyString),
      password(kEmptyString),
      is_anonymous(false),
      initdir_local(kEmptyString),
      initdir_remote(kEmptyString),
      is_lastdir_as_initdir(false) {}

HostSettingBasicForm::HostSettingBasicForm(QWidget* parent)
    : QWidget(parent), d_(new HostSettingBasicForm::Private()) {
  d_->ui.setupUi(this);
  this->setDataAsDefault();

  // slots隠ぺいの残骸
  // QObject::connect(d_->ui.pushButton_NowDir, SIGNAL(clicked()), d_,
  // SLOT(onClick_pushButton_NowDir()));
}

void HostSettingBasicForm::setData(const Data& data) const {
  d_->initdir_remote = data.initdir_remote;
  d_->ui.lineEdit_SettingName->setText(data.settingname);
  d_->ui.lineEdit_HostAddr->setText(data.hostaddr);
  d_->ui.lineEdit_Username->setText(data.username);
  d_->ui.lineEdit_Password->setText(data.password);
  d_->ui.checkBox_Anonymous->setChecked(data.is_anonymous);
  d_->ui.lineEdit_LocalDir->setText(data.initdir_local);
  d_->ui.lineEdit_RemoteDir->setText(data.initdir_remote);
  d_->ui.checkBox_LastDir->setChecked(data.is_lastdir_as_initdir);
  d_->ui.pushButton_NowDir->setEnabled(!d_->initdir_remote.isEmpty());
}

const HostSettingBasicForm::Data& HostSettingBasicForm::getData() const {
  static Data data;
  data.settingname = d_->ui.lineEdit_SettingName->text();
  data.hostaddr = d_->ui.lineEdit_HostAddr->text();
  data.username = d_->ui.lineEdit_Username->text();
  data.password = d_->ui.lineEdit_Password->text();
  data.is_anonymous = d_->ui.checkBox_Anonymous->isChecked();
  data.initdir_local = d_->ui.lineEdit_LocalDir->text();
  data.initdir_remote = d_->ui.lineEdit_RemoteDir->text();
  data.is_lastdir_as_initdir = d_->ui.checkBox_LastDir->isChecked();
  return data;
}

void HostSettingBasicForm::setDataAsDefault() const { this->setData(Data()); }

void HostSettingBasicForm::onClick_toolButton_SelectLocalDir() {
  qDebug() << __FUNCTION__ << "called!";
  QString dirpath = QFileDialog::getExistingDirectory(
      this, "", d_->ui.lineEdit_LocalDir->text());
  if (!dirpath.isEmpty()) {
    d_->ui.lineEdit_LocalDir->setText(dirpath);
  }
}

void HostSettingBasicForm::onClick_pushButton_NowDir() {
  qDebug() << __FUNCTION__ << "called!";
  d_->ui.lineEdit_RemoteDir->setText(d_->initdir_remote);
}

void HostSettingBasicForm::onClick_checkBox_Anonymous(bool checked) {
  qDebug() << __FUNCTION__ << "called!";
  static QPair<QString, QString> user_passwd;
  if (checked) {
    user_passwd.first = d_->ui.lineEdit_Username->text();
    user_passwd.second = d_->ui.lineEdit_Password->text();
    d_->ui.lineEdit_Username->setText(kDefAnonymousUsename);
    d_->ui.lineEdit_Password->setText(kDefAnonymousPassword);
  } else {
    d_->ui.lineEdit_Username->setText(user_passwd.first);
    d_->ui.lineEdit_Password->setText(user_passwd.second);
  }
}
