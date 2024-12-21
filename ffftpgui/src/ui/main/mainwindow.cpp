﻿#include "mainwindow.hpp"

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
  QMetaObject::invokeMethod(_mainwindow, "askSaveCryptFunc", Qt::BlockingQueuedConnection, Q_RETURN_ARG(bool, _r));
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
  case ffftp_procmsg::SHOW_DIALOGBOX:
    unsigned long long msgid = reinterpret_cast<unsigned long long>(param.param1);
    switch (msgid) {
    case ffftp_dialogid::SAVECRYPT_DLG:
      ret = static_cast<int>(_AskSaveCryptFunc());
      break;
    case ffftp_dialogid::MASTERPASSWD_DLG: {
      std::wstring* passwd = reinterpret_cast<std::wstring*>(param.param2);
      ret = static_cast<unsigned long long>(_AskMasterPassword(*passwd));
    }
      break;
    case ffftp_dialogid::NEWMASTERPASSWD_DLG:
      ret = static_cast<int>(_AskRetryMasterPassword());
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
  ffftp_setcallback_asksavecrypt(_AskSaveCryptFunc);
//  ffftp_setcallback_askmasterpassword(_AskMasterPassword);
  ffftp_setcallback_askretrymasterpassword(_AskRetryMasterPassword);

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
  qDebug() << __FUNCTION__ << " called.";
  HostListDialog dialog{this};
  if (dialog.exec() == QDialog::Accepted) {
    qDebug() << "Accepted.";
    // 接続処理は別スレッドへ
    QMetaObject::invokeMethod(d_->ffftpt, "connect", Qt::QueuedConnection, Q_ARG(const void*, dialog.hostcontext()));
  }
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
