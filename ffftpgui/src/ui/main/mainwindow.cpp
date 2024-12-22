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
#include "ui/host/hostquickdialog.hpp"
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
MainWindow* _mainwindow{nullptr};
}  // namespace

unsigned long long MainWindow::ffftp_proc(unsigned long long msg, ffftp_procparam param) {
  unsigned long long ret{0};
  bool ret_bool{false};
  switch (msg) {
  // ffftpからメッセージボックスの表示依頼の通知が来た
  case ffftp_procmsg::SHOW_MESSAGEBOX:
    ret = MainWindow::messageBox(reinterpret_cast<unsigned long long>(param.param1), reinterpret_cast<unsigned long long>(param.param2));
    break;

  // ffftpからダイアログの表示依頼の通知が来た
  case ffftp_procmsg::SHOW_DIALOGBOX:
    unsigned long long msgid = reinterpret_cast<unsigned long long>(param.param1);
    switch (msgid) {
    case ffftp_dialogid::HOSTLIST_DLG:
      // ホスト設定ダイアログを表示する
      QMetaObject::invokeMethod(_mainwindow, "showHostListDialog", Qt::AutoConnection, Q_RETURN_ARG(bool, ret_bool));
      ret = ret_bool;
      break;
    case ffftp_dialogid::HOSTCONNECT_DLG:
      // ホスト設定ダイアログ（簡易版）を表示する
      QMetaObject::invokeMethod(_mainwindow, "showHostConnectDialog", Qt::AutoConnection, Q_RETURN_ARG(bool, ret_bool));
      ret = ret_bool;
      break;
    case ffftp_dialogid::HOSTNAME_DLG: {
      // クイック接続ダイアログを表示する
      const ffftp_procparam_quickconnect* param2 = static_cast<decltype(param2)>(param.param2);
      ffftp_procparam_quickconnect* param3 = static_cast<decltype(param3)>(param.param3);
      QMetaObject::invokeMethod(_mainwindow, "showHostQuickConnectDialog", Qt::AutoConnection, Q_RETURN_ARG(bool, ret_bool), Q_ARG(const ffftp_procparam_quickconnect&, *param2), Q_ARG(ffftp_procparam_quickconnect&, *param3));
      ret = ret_bool;
      } break;
    case ffftp_dialogid::ABOUT_DLG: break;
    case ffftp_dialogid::TRANSFER_DLG: break;
    case ffftp_dialogid::RENAME_DLG: break;
    case ffftp_dialogid::DELETE_DLG: break;
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
      QMetaObject::invokeMethod(_mainwindow, "askRetryMasterPassword", Qt::AutoConnection, Q_RETURN_ARG(bool, ret_bool));
      ret = ret_bool;
      break;
    case ffftp_dialogid::MASTERPASSWD_DLG: {
      QString passwd_{};
      QMetaObject::invokeMethod(_mainwindow, "askMasterPassword", Qt::AutoConnection, Q_RETURN_ARG(bool, ret_bool), Q_ARG(QString&, passwd_));
      *reinterpret_cast<std::wstring*>(param.param2) = passwd_.toStdWString();
      ret = ret_bool;
    } break;
    case ffftp_dialogid::HSET_CRYPT_DLG: break;
    case ffftp_dialogid::HSET_ADV3_DLG: break;
    case ffftp_dialogid::SAVECRYPT_DLG:
      QMetaObject::invokeMethod(_mainwindow, "askSaveCryptFunc", Qt::AutoConnection, Q_RETURN_ARG(bool, ret_bool));
      ret = ret_bool;
      break;
    case ffftp_dialogid::UPDATESSLROOT_DLG: break;
    case ffftp_dialogid::UPDOWN_AS_WITH_EXT_DLG: break;
    case ffftp_dialogid::INI_FROM_REG_DLG: break;
    case ffftp_dialogid::OPT_TRMODE4_DLG: break;
    case ffftp_dialogid::OPT_DISP2_DLG: break;
    case ffftp_dialogid::CORRUPTSETTINGS_DLG: break;
    case ffftp_dialogid::CERTERR_DLG: break;
    case ffftp_dialogid::OPTION_DLG:
      QMetaObject::invokeMethod(_mainwindow, "showOptionDialog", Qt::AutoConnection, Q_RETURN_ARG(bool, ret_bool));
      ret = ret_bool;
      break;
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

  d_->ffftpt = new FFFTPThread();  // スレッド化するためにはコンストラクタにparentを渡してはいけない
  //d_->ffftpt = new FFFTPThread(this); // これはNG
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

// [接続]メニュー
void MainWindow::actionConnect() { ffftp_notify_event(ffftp_eventid::EID_MENU_CONNECT); }
void MainWindow::actionQuickConnect() { ffftp_notify_event(ffftp_eventid::EID_MENU_QUICK); }
void MainWindow::actionDisconnect() { ffftp_notify_event(ffftp_eventid::EID_MENU_DISCONNECT); }
void MainWindow::actionHostSettings() { ffftp_notify_event(ffftp_eventid::EID_MENU_SET_CONNECT); }
void MainWindow::actionExit() { ffftp_notify_event(ffftp_eventid::EID_MENU_EXIT); }
void MainWindow::actionImportFromWS_FTP() {}
void MainWindow::actionSaveSettingsToFile() {}
void MainWindow::actionLoadSettingsFromFile() {}
void MainWindow::actionModifyMasterPassword() {}
void MainWindow::actionExportFileZillaXML() {}
void MainWindow::actionExportWinSCPINI() {}
void MainWindow::actionResetAllSettings() {}
// [コマンド]メニュー
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
// [ブックマーク]メニュー
void MainWindow::actionBmarkAddHost() {}
void MainWindow::actionBmarkAddLocal() {}
void MainWindow::actionBmarkAddBoth() {}
void MainWindow::actionBmarkEdit() {}
// [表示]メニュー
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
// [ツール]メニュー
void MainWindow::actionCalcOnetimePasswd() {}
void MainWindow::actionWindowsFWSetting() {}
// [オプション]メニュー
void MainWindow::actionPreference() { ffftp_notify_event(ffftp_eventid::EID_MENU_OPTION); }
// [ヘルプ]メニュー
void MainWindow::actionContents() {}
void MainWindow::actionOpenWebsite() {}
void MainWindow::actionAbout() {}
void MainWindow::actionAboutQt() { QMessageBox::aboutQt(this, QString(ffftp_applicationname())); }
// ツールボタン
void MainWindow::actionModeAscii(bool checked) {}
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

// ダイアログの表示系
bool MainWindow::showHostListDialog() {
  bool ret{false};
  HostListDialog dialog{true, this};
  if (ret = dialog.exec() == QDialog::Accepted) {
    ffftp_preconnect(dialog.hostcontext());
  }
  return ret;
}

bool MainWindow::showHostConnectDialog() {
  bool ret{false};
  HostListDialog dialog{false, this};
  if (ret = dialog.exec() == QDialog::Accepted) {
    ffftp_preconnect(dialog.hostcontext());
  }
  return ret;
}

bool MainWindow::showHostQuickConnectDialog(const ffftp_procparam_quickconnect& inparam, ffftp_procparam_quickconnect& outparam) {
  HostQuickDialog dialog{{
      [&inparam](){
        QStringList ret{};
        for (int i = 0; i < inparam.history_cnt; ++i) {
          ret.push_back(QString(inparam.history[i]));
        }
        return ret;
      }(),
      QString(inparam.username), QString(inparam.password),
      inparam.use_firewall, inparam.use_passive }, this};
  const bool ret = dialog.exec() == QDialog::Accepted;
  if (ret) {
    static HostQuickDialog::Data data{};
    static std::wstring hostname{}, username{}, password{};
    data = dialog.data();
    hostname = data.hostname.toStdWString();
    username = data.username.toStdWString();
    password = data.password.toStdWString();
    outparam.hostname = hostname.c_str();
    outparam.username = username.c_str();
    outparam.password = password.c_str();
    outparam.use_firewall = data.use_firewall;
    outparam.use_passive = data.use_passive;
  }
  return ret;
}

bool MainWindow::showOptionDialog() {
  ffftp_option option;
  ffftp_option_initialize(&option);
  ffftp_getoption(&option);
  OptionDialog dialog{option, this};
  const bool ret{dialog.exec() == QDialog::Accepted};
  if (ret) {
    dialog.option(option);
    ffftp_setoption(&option);
  }
  ffftp_option_finalize(&option);
  return ret;
}

// メッセージボックスの表示系
bool MainWindow::askMasterPassword(QString& passwd) {
  bool ok{false};
  passwd = QInputDialog::getText(this, QString(ffftp_applicationname()), kPlzInputYourMasterPwd, QLineEdit::Password, kEmptyString, &ok);
  return ok;
}

bool MainWindow::askRetryMasterPassword() {
  return QMessageBox::question(this, QString(ffftp_applicationname()), kAskRetryInputYourMasterPwd) == QMessageBox::Yes;
}

bool MainWindow::askSaveCryptFunc() {
  return QMessageBox::question(this, kAskSaveCryptTitle, kAskSaveCryptBody) == QMessageBox::Yes;
}

// タイマーイベント
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

// ffftpからメッセージボックスの表示依頼の通知が来た時に行う処理
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
    { SID_REMOVE_READONLY,             { msgq, tr("ダウンロード"), tr("読み取り専用ファイルです。読み取り専用属性を解除しますか？"), kYesNo, QMessageBox::NoButton } },
    { SID_MASTER_PASSWORD_INCORRECT,   { msgw, kStringFFFTP, kAskRetryInputYourMasterPwd, kYesNo, QMessageBox::NoButton } },
    { SID_FAIL_TO_INIT_OLE,            { msgc, kStringFFFTP, tr("OLEの初期化に失敗しました。"), kOk, QMessageBox::NoButton } },
    { SID_ERR_SSL,                     { msgc, kStringFFFTP, tr("SSLの初期化に失敗しました。\nアプリケーションを終了します。"), kOk, QMessageBox::NoButton } },
    { SID_FOUND_NEW_VERSION_INI,       { msgq, kStringFFFTP, kMsgFoundNewVerSettings, kYesNoCancel, QMessageBox::No } },
    { SID_MANAGE_STATEFUL_FTP,         { msgi, kStringFFFTP, tr("WindowsファイアウォールのステートフルFTPフィルタの有効無効を設定します。\nこれはWindows Vista以降でのみ動作します。\n有効化または無効化することで通信状態が改善されることがあります。\n有効化するには「はい」、無効化するには「いいえ」を選択してください。"), kYesNoCancel, QMessageBox::NoButton } },
    { SID_FAIL_TO_MANAGE_STATEFUL_FTP, { msgc, kStringFFFTP, tr("ステートフルFTPフィルタを設定できませんでした。"), kOk, QMessageBox::NoButton } },
    { SID_NEED_RESTART,                { msgi, kStringFFFTP, tr("設定をファイルから復元するためには,FFFTPを再起動してください。"), kOk, QMessageBox::NoButton } },
    { SID_PASSWORD_ISNOT_IDENTICAL,    { msgc, kStringFFFTP, tr("新しいマスターパスワードが一致しません。"), kOk, QMessageBox::NoButton } },
    { SID_FAIL_TO_EXEC_REDEDIT,        { msgc, kStringFFFTP, tr("レジストリエディタが起動できませんでした。"), kOk, QMessageBox::NoButton } },
    { SID_MUST_BE_REG_OR_INI,          { msgc, kStringFFFTP, tr("設定ファイルは拡張子が.regか.iniでなければなりません。"), kOk, QMessageBox::NoButton } },
    { SID_CANT_SAVE_TO_INI,            { msgc, kStringFFFTP, tr("INIファイルに設定が保存できません。"), kOk, QMessageBox::NoButton } },
    { SID_FAIL_TO_EXPORT,              { msgc, kStringFFFTP, tr("設定のエクスポートに失敗しました。\n保存する場所や形式を変更してください。"), kOk, QMessageBox::NoButton } },
    { SID_NEED_EXSITING_WINSCP_INI,    { msgi, kStringFFFTP, tr("この機能で新規作成したINIファイルをWinSCPで読み込むと全ての設定が失われます。\nすでにWinSCPをお使いでありホストの設定のみ移行したい場合は既存のWinSCP.iniを選択してください。"), kOk, QMessageBox::NoButton } },
  };
  Msg& msg = table[msgid];
  return ret_table[msg.box->box(msg.title, msg.text, msg.buttons, msg.defaultButton)];
}
