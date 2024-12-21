#include "mainwindow.hpp"

#include <QActionGroup>
#include <QDir>
#include <QInputDialog>
#include <QMessageBox>

#include "ui_mainwindow.h"

#include "ffftp.h"
#include "stdafx.h"
#include "core/ffftpthread.hpp"
#include "ui/common/inputdialog.hpp"
#include "ui/host/hostlistdialog.hpp"
#include "ui/option/optiondialog.hpp"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class MainWindow::Private {
 public:
  Private() : ffftpt(nullptr) {}
  ~Private() {}
  Ui::MainWindowClass ui;
  FFFTPThread* ffftpt;
};

namespace {

MainWindow* _mainwindow = nullptr;
bool _AskSaveCryptFunc() {
  bool _r = false;
  // Qt::BlockingQueuedConnectionは、他のスレッドからinvokeMethodする場合に必要
  // see https://stackoverflow.com/questions/18725727/how-to-get-a-return-value-from-qmetaobjectinvokemethod
  QMetaObject::invokeMethod(_mainwindow, "askSaveCryptFunc", Qt::AutoConnection, Q_RETURN_ARG(bool, _r));
  return _r;
}
bool _AskMasterPassword(std::wstring& passwd) {
  qDebug() << __FUNCTION__ << " called.";
  bool _r = false;
  QString passwd_;
  QMetaObject::invokeMethod(_mainwindow, "askMasterPassword", Qt::AutoConnection, Q_RETURN_ARG(bool, _r), Q_ARG(QString&, passwd_));
  qDebug() << __FUNCTION__ << _r << " " << passwd_;
  passwd = passwd_.toStdWString();
  return _r;
}
bool _AskRetryMasterPassword() {
  bool _r = false;
  QMetaObject::invokeMethod(_mainwindow, "askRetryMasterPassword", Qt::AutoConnection, Q_RETURN_ARG(bool, _r));
  return _r;
}

}  // namespace

unsigned long long MainWindow::ffftp_proc(unsigned long long msg, ffftp_procparam param) {
  unsigned long long ret{0};
  switch (msg) {
  case ffftp_procmsg::SHOW_MESSAGEBOX:
    ret = MainWindow::messageBox(reinterpret_cast<unsigned long long>(param.param1), reinterpret_cast<unsigned long long>(param.param2));
    break;
  case ffftp_procmsg::SHOW_DIALOGBOX:
    unsigned long long msgid = reinterpret_cast<unsigned long long>(param.param1);
    switch (msgid) {
    case ffftp_dialogid::ABOUT_DLG: break;
    case ffftp_dialogid::TRANSFER_DLG: break;
    case ffftp_dialogid::RENAME_DLG: break;
    case ffftp_dialogid::DELETE_DLG: break;
    case ffftp_dialogid::HOSTLIST_DLG: {
      bool _r{false};
      QMetaObject::invokeMethod(_mainwindow, "actionConnectInvoked", Qt::AutoConnection, Q_RETURN_ARG(bool, _r), Q_ARG(bool, true));
      ret = _r;
    } break;
    case ffftp_dialogid::HOSTSET_DLG: break;
    //case ffftp_dialogid::HSET_MAIN_DLG: break;
    case ffftp_dialogid::USER_DLG: break;
    //case ffftp_dialogid::OPT_USER_DLG: break;
    case ffftp_dialogid::TOOL_DLG: break;
    //case ffftp_dialogid::OPT_TOOL_DLG: break;
    case ffftp_dialogid::PERMIT_DLG: break;
    //case ffftp_dialogid::CHMOD_DLG: break;
    case ffftp_dialogid::SORT_DLG: break;
    case ffftp_dialogid::TRMODE_DLG: break;
    case ffftp_dialogid::MKDIR_DLG: break;
    case ffftp_dialogid::OPT_MISC_DLG: break;
    case ffftp_dialogid::HOSTNAME_DLG: break;
    case ffftp_dialogid::PASSWD_DLG: break;
    case ffftp_dialogid::USERNAME_DLG: break;
    case ffftp_dialogid::CHDIR_DLG: break;
    case ffftp_dialogid::EXIT_DLG: break;
    case ffftp_dialogid::EXIST_DLG: break;
    //case ffftp_dialogid::DOWN_EXIST_DLG: break;
    case ffftp_dialogid::OPT_TRMODE_DLG: break;
    //case ffftp_dialogid::OPT_TRMODE2_DLG: break;
    case ffftp_dialogid::OPT_NOTIFY_DLG: break;
    case ffftp_dialogid::BMARK_DLG: break;
    case ffftp_dialogid::OPT_FIRE_DLG: break;
    case ffftp_dialogid::HSET_ADV_DLG: break;
    case ffftp_dialogid::DISKFULL_DLG: break;
    case ffftp_dialogid::FIND_DLG: break;
    case ffftp_dialogid::DOWNERR_DLG: break;
    case ffftp_dialogid::UPERR_DLG: break;
    case ffftp_dialogid::HSET_CODE_DLG: break;
    case ffftp_dialogid::OPT_TRMODE_DLG1: break;
    //case ffftp_dialogid::OPT_TRMODE1_DLG: break;
    case ffftp_dialogid::EXIST_DLG1: break;
    case ffftp_dialogid::UP_EXIST_DLG: break;
    case ffftp_dialogid::REGINIT_DLG: break;
    case ffftp_dialogid::HOSTCONNECT_DLG: {
      bool _r{false};
      QMetaObject::invokeMethod(_mainwindow, "actionConnectInvoked", Qt::AutoConnection, Q_RETURN_ARG(bool, _r), Q_ARG(bool, false));
      ret = _r;
    } break;
    case ffftp_dialogid::UPDOWN_AS_DLG: break;
    case ffftp_dialogid::RE_PASSWD_DLG: break;
    case ffftp_dialogid::SAVEPASS_DLG: break;
    case ffftp_dialogid::SEL_LOCAL_DLG: break;
    case ffftp_dialogid::SEL_REMOTE_DLG: break;
    case ffftp_dialogid::MIRROR_UP_DLG: break;
    case ffftp_dialogid::ACCOUNT_DLG: break;
    case ffftp_dialogid::OPT_MIRROR_DLG: break;
    case ffftp_dialogid::SOMECMD_DLG: break;
    case ffftp_dialogid::DOWNNAME_DLG: break;
    case ffftp_dialogid::OPT_CONNECT_DLG: break;
    case ffftp_dialogid::RASNOTIFY_DLG: break;
    case ffftp_dialogid::FILESIZE_DLG: break;
    case ffftp_dialogid::FILESIZE_NOTIFY_DLG: break;
    case ffftp_dialogid::HSET_ADV2_DLG: break;
    case ffftp_dialogid::CWDERR_DLG: break;
    case ffftp_dialogid::OPT_TRMODE3_DLG: break;
    case ffftp_dialogid::DEF_ATTR_DLG: break;
    case ffftp_dialogid::FNAME_IN_DLG: break;
    case ffftp_dialogid::OTP_NOTIFY_DLG: break;
    case ffftp_dialogid::OTP_CALC_DLG: break;
    case ffftp_dialogid::MIRROR_NOTIFY_DLG: break;
    case ffftp_dialogid::MIRRORDOWN_NOTIFY_DLG: break;
    case ffftp_dialogid::MIRROR_DOWN_DLG: break;
    case ffftp_dialogid::CHDIR_BR_DLG: break;
    case ffftp_dialogid::FILTER_DLG: break;
    case ffftp_dialogid::GROUP_DLG: break;
    case ffftp_dialogid::HOSTDEL_DLG: break;
    case ffftp_dialogid::GROUPDEL_DLG: break;
    case ffftp_dialogid::NORESUME_DLG: break;
    case ffftp_dialogid::FORCERENAME_DLG: break;
    case ffftp_dialogid::HSET_DIALUP_DLG: break;
    case ffftp_dialogid::RASRECONNECT_DLG: break;
    case ffftp_dialogid::OPT_DISP1_DLG: break;
    case ffftp_dialogid::BMARK_EDIT_DLG: break;
    case ffftp_dialogid::OPT_TOOL_DLG1: break;
    case ffftp_dialogid::MOVE_NOTIFY_DLG: break;
    case ffftp_dialogid::FORCEPASSCHANGE_DLG: break;
    case ffftp_dialogid::NEWMASTERPASSWD_DLG:
      ret = static_cast<unsigned long long>(_AskRetryMasterPassword());
      break;
    case ffftp_dialogid::MASTERPASSWD_DLG: {
      std::wstring* passwd = reinterpret_cast<std::wstring*>(param.param2);
      ret = static_cast<unsigned long long>(_AskMasterPassword(*passwd));
    } break;
    case ffftp_dialogid::HSET_CRYPT_DLG: break;
    case ffftp_dialogid::HSET_ADV3_DLG: break;
    case ffftp_dialogid::SAVECRYPT_DLG:
      ret = static_cast<int>(_AskSaveCryptFunc());
      break;
    case ffftp_dialogid::UPDATESSLROOT_DLG: break;
    case ffftp_dialogid::UPDOWN_AS_WITH_EXT_DLG: break;
    case ffftp_dialogid::INI_FROM_REG_DLG: break;
    case ffftp_dialogid::OPT_TRMODE4_DLG: break;
    case ffftp_dialogid::OPT_DISP2_DLG: break;
    case ffftp_dialogid::CORRUPTSETTINGS_DLG: break;
    case ffftp_dialogid::CERTERR_DLG: break;
    }
  }
  return ret;
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), d_(new MainWindow::Private()) {
  d_->ui.setupUi(this);
  // QActionGroupをDesignerから編集する方法が分からなかったので手動で実装
  QActionGroup* ag1 = new QActionGroup(this);
  ag1->addAction(d_->ui.actionViewFList);
  ag1->addAction(d_->ui.actionViewFDetail);
  ag1->setExclusive(true);
  QActionGroup* ag2 = new QActionGroup(this);
  ag2->addAction(d_->ui.actionModeAscii);
  ag2->addAction(d_->ui.actionModeBinary);
  ag2->addAction(d_->ui.actionModeAuto);
  ag2->setExclusive(true);
  QActionGroup* ag3 = new QActionGroup(this);
  ag3->addAction(d_->ui.actionLocalSJIS);
  ag3->addAction(d_->ui.actionLocalEUC);
  ag3->addAction(d_->ui.actionLocalJIS);
  ag3->addAction(d_->ui.actionLocalUTF8);
  ag3->addAction(d_->ui.actionLocalUTF8BOM);
  ag3->setExclusive(true);
  QActionGroup* ag4 = new QActionGroup(this);
  ag4->addAction(d_->ui.actionHostSJIS);
  ag4->addAction(d_->ui.actionHostEUC);
  ag4->addAction(d_->ui.actionHostJIS);
  ag4->addAction(d_->ui.actionHostUTF8);
  ag4->addAction(d_->ui.actionHostUTF8BOM);
  ag4->addAction(d_->ui.actionHostNocode);
  ag4->setExclusive(true);

  startTimer(500);
  emit timerEvent(nullptr);

  d_->ffftpt =
      new FFFTPThread();  // スレッド化するためにはコンストラクタにparentを渡してはいけない
  // d_->ffftpt = new FFFTPThread(this); // これはNG
  d_->ffftpt->moveToThread(d_->ffftpt);
  d_->ffftpt->start();

  _mainwindow = this;

  // ローカルファイルリストの初期化
  for (const auto& d : QDir::drives()) {
    d_->ui.widget->setLocalPath(d.path());
  }
  d_->ui.widget->setLocalPath(QDir::currentPath());

  // 詳細ボタンを押下させる
  d_->ui.actionViewFDetail->setChecked(true);
}

MainWindow::~MainWindow() {
  d_->ffftpt->terminate();
  delete d_->ffftpt;
}

void MainWindow::timerEvent(QTimerEvent* event) {
  QString msg = QString(ffftp_taskmessage());
  if (!msg.isEmpty()) {
    d_->ui.widget->addTaskMessage(msg);
  }
  QString title = QString(ffftp_windowtitle());
  if (this->windowTitle() != title) {
    this->setWindowTitle(title);
  }
}

void MainWindow::actionConnect() {
  ffftp_notify_event(ffftp_eventid::EID_MENU_CONNECT);
}
bool MainWindow::actionConnectInvoked(bool editable) {
  bool ret{false};
  HostListDialog dialog{editable, this};
  if (ret = dialog.exec() == QDialog::Accepted) {
    ffftp_preconnect(dialog.hostcontext());
  }
  return ret;
}
void MainWindow::actionQuickConnect() {}
void MainWindow::actionDisconnect() {}
void MainWindow::actionHostSettings() {}
void MainWindow::actionExit() {
  qDebug() << __FUNCTION__ << " called.";
  QMainWindow::close();
}
void MainWindow::actionImportFromWS_FTP() {}
void MainWindow::actionSaveSettingsToFile() {}
void MainWindow::actionLoadSettingsFromFile() {}
void MainWindow::actionModifyMasterPassword() {}
void MainWindow::actionExportFileZillaXML() {}
void MainWindow::actionExportWinSCPINI() {}
void MainWindow::actionResetSettings() {}
void MainWindow::actionDownload() {}
void MainWindow::actionUpload() {}
void MainWindow::actionDownloadRename() {}
void MainWindow::actionUploadRename() {}
void MainWindow::actionDownloadRespecify() {}
void MainWindow::actionDownloadAsFile() {}
void MainWindow::actionUploadMirroring() {}
void MainWindow::actionCalcFilesSize() {}
void MainWindow::actionDownloadMirroring() {}
void MainWindow::actionCmdRm() {}
void MainWindow::actionCmdRename() {}
void MainWindow::actionCmdReattribute() {}
void MainWindow::actionCmdMkdir() {}
void MainWindow::actionCommand() {}
void MainWindow::actionDirSync(bool checked) {}
void MainWindow::actionBmarkAddHost() {}
void MainWindow::actionBmarkAddLocal() {}
void MainWindow::actionBmarkAddBoth() {}
void MainWindow::actionBmarkEdit() {}
void MainWindow::actionFilter() {}
void MainWindow::actionFind() {}
void MainWindow::actionFindNext() {}
void MainWindow::actionSelect() {}
void MainWindow::actionSelectAll() {}
void MainWindow::actionViewFList(bool checked) {
  d_->ui.widget->showDetail(!checked);
}
void MainWindow::actionViewFDetail(bool checked) {
  d_->ui.widget->showDetail(checked);
}
void MainWindow::actionSort() {}
void MainWindow::actionViewDot(bool checked) {
  d_->ui.widget->setDotFileShown(checked);
}
void MainWindow::actionListWithViewer() {}
void MainWindow::actionTaskWithViewer() {}
void MainWindow::actionReflesh() {}
void MainWindow::actionCalcOnetimePasswd() {}
void MainWindow::actionWindowsFWSetting() {}
void MainWindow::actionPreference() {
  ffftp_option option;
  ffftp_option_initialize(&option);
  ffftp_getoption(&option);
  OptionDialog dialog{option, this};
  if (dialog.exec() == QDialog::Accepted) {
    dialog.option(option);
    ffftp_setoption(&option);
  }
  ffftp_option_finalize(&option);
}
void MainWindow::actionContents() {}
void MainWindow::actionOpenWebsite() {}
void MainWindow::actionAbout() {}
void MainWindow::actionAboutQt() {
  qDebug() << __FUNCTION__ << " called.";
  QMessageBox::aboutQt(this, "FFFTP");
}
void MainWindow::actionModeAscii(bool checked) {
  qDebug() << __FUNCTION__ << " called. toggled=" << checked;
}
void MainWindow::actionModeBinary(bool checked) {}
void MainWindow::actionModeAuto(bool checked) {}
void MainWindow::actionLocalSJIS(bool checked) {}
void MainWindow::actionLocalEUC(bool checked) {}
void MainWindow::actionLocalJIS(bool checked) {}
void MainWindow::actionLocalUTF8(bool checked) {}
void MainWindow::actionLocalUTF8BOM(bool checked) {}
void MainWindow::actionHostSJIS(bool checked) {}
void MainWindow::actionHostEUC(bool checked) {}
void MainWindow::actionHostJIS(bool checked) {}
void MainWindow::actionHostUTF8(bool checked) {}
void MainWindow::actionHostUTF8BOM(bool checked) {}
void MainWindow::actionHostNocode(bool checked) {}
void MainWindow::actionHalfKana2Full(bool checked) {}
void MainWindow::actionStopReceiving() {}

bool MainWindow::askSaveCryptFunc() {
  if (QMessageBox::question(this, kAskSaveCryptTitle, kAskSaveCryptBody) == QMessageBox::Yes)
    return true;
  return false;
}

bool MainWindow::askMasterPassword(QString& passwd) {
  qDebug() << __FUNCTION__ << " called.";
  bool ok = false;
  passwd = InputDialog::getText(this, QString(ffftp_applicationname()), kPlzInputYourMasterPwd, QLineEdit::Password, kEmptyString, &ok, 64/*TODO: helpID */);
  return ok;
}

bool MainWindow::askRetryMasterPassword() {
  if (QMessageBox::question(this, QString(ffftp_applicationname()), kAskRetryInputYourMasterPwd) == QMessageBox::Yes)
    return true;
  return false;
}

#define MsgBoxX(X)\
  struct MsgBox_##X : public MsgBox {\
    inline QMessageBox::StandardButton box(const QString& title, const QString& text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton) const override {\
      return QMessageBox::X(_mainwindow, title, text, buttons, defaultButton);\
    }\
  }

int MainWindow::messageBox(unsigned long long msgid, unsigned long long capid) {
  struct MsgBox { virtual inline QMessageBox::StandardButton box(const QString& title, const QString& text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton) const = 0; };
  MsgBoxX(critical);
  MsgBoxX(information);
  MsgBoxX(question);
  MsgBoxX(warning);
  static const MsgBox* msgc = new MsgBox_critical{};
  static const MsgBox* msgi = new MsgBox_information{};
  static const MsgBox* msgq = new MsgBox_question{};
  static const MsgBox* msgw = new MsgBox_warning{};
  struct Msg {
    const MsgBox* box;
    QString title;
    QString text;
    QMessageBox::StandardButtons buttons;
    QMessageBox::StandardButton defaultButton;
  };
  static QMap<QMessageBox::StandardButton, int> ret_table{
    { QMessageBox::Ok,     1 }, // means IDOK
    { QMessageBox::Cancel, 2 }, // means IDCANCEL
    { QMessageBox::Yes,    6 }, // means IDYES
    { QMessageBox::No,     7 }, // means IDNO
  };
  static constexpr QMessageBox::StandardButtons kOk          = QMessageBox::Ok;
  static constexpr QMessageBox::StandardButtons kYesNo       = QMessageBox::Yes | QMessageBox::No;
  static constexpr QMessageBox::StandardButtons kYesNoCancel = QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel;
  static QMap<unsigned long long, Msg> table{
    { SID_REMOVE_READONLY,             { msgq, tr("ダウンロード"), MainWindow::tr("読み取り専用ファイルです。読み取り専用属性を解除しますか？"), kYesNo, QMessageBox::NoButton } },
    { SID_MASTER_PASSWORD_INCORRECT,   { msgw, kStringFFFTP, kAskRetryInputYourMasterPwd, kYesNo, QMessageBox::NoButton } },
    { SID_FAIL_TO_INIT_OLE,            { msgc, kStringFFFTP, MainWindow::tr("OLEの初期化に失敗しました。"), kOk, QMessageBox::NoButton } },
    { SID_ERR_SSL,                     { msgc, kStringFFFTP, MainWindow::tr("SSLの初期化に失敗しました。\nアプリケーションを終了します。"), kOk, QMessageBox::NoButton } },
    { SID_FOUND_NEW_VERSION_INI,       { msgq, kStringFFFTP, kMsgFoundNewVerSettings, kYesNoCancel, QMessageBox::No } },
    { SID_MANAGE_STATEFUL_FTP,         { msgi, kStringFFFTP, MainWindow::tr("WindowsファイアウォールのステートフルFTPフィルタの有効無効を設定します。\nこれはWindows Vista以降でのみ動作します。\n有効化または無効化することで通信状態が改善されることがあります。\n有効化するには「はい」、無効化するには「いいえ」を選択してください。"), kYesNoCancel, QMessageBox::NoButton } },
    { SID_FAIL_TO_MANAGE_STATEFUL_FTP, { msgc, kStringFFFTP, MainWindow::tr("ステートフルFTPフィルタを設定できませんでした。"), kOk, QMessageBox::NoButton } },
    { SID_NEED_RESTART,                { msgi, kStringFFFTP, MainWindow::tr("設定をファイルから復元するためには,FFFTPを再起動してください。"), kOk, QMessageBox::NoButton } },
    { SID_PASSWORD_ISNOT_IDENTICAL,    { msgc, kStringFFFTP, MainWindow::tr("新しいマスターパスワードが一致しません。"), kOk, QMessageBox::NoButton } },
    { SID_FAIL_TO_EXEC_REDEDIT,        { msgc, kStringFFFTP, MainWindow::tr("レジストリエディタが起動できませんでした。"), kOk, QMessageBox::NoButton } },
    { SID_MUST_BE_REG_OR_INI,          { msgc, kStringFFFTP, MainWindow::tr("設定ファイルは拡張子が.regか.iniでなければなりません。"), kOk, QMessageBox::NoButton } },
    { SID_CANT_SAVE_TO_INI,            { msgc, kStringFFFTP, MainWindow::tr("INIファイルに設定が保存できません。"), kOk, QMessageBox::NoButton } },
    { SID_FAIL_TO_EXPORT,              { msgc, kStringFFFTP, MainWindow::tr("設定のエクスポートに失敗しました。\n保存する場所や形式を変更してください。"), kOk, QMessageBox::NoButton } },
    { SID_NEED_EXSITING_WINSCP_INI,    { msgi, kStringFFFTP, MainWindow::tr("この機能で新規作成したINIファイルをWinSCPで読み込むと全ての設定が失われます。\nすでにWinSCPをお使いでありホストの設定のみ移行したい場合は既存のWinSCP.iniを選択してください。"), kOk, QMessageBox::NoButton } },
  };
  Msg& msg = table[msgid];
  return ret_table[msg.box->box(msg.title, msg.text, msg.buttons, msg.defaultButton)];
}
