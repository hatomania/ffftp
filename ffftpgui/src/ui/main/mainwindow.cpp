#include "mainwindow.hpp"

#include <QActionGroup>
#include <QInputDialog>
#include <QMessageBox>

#include "core/ffftpthread.hpp"
#include "ffftp.h"
#include "stdafx.h"
#include "ui/host/hostlistdialog.hpp"
#include "ui_mainwindow.h"
#include "ui/option/optiondialog.hpp"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class MainWindow::Private {
 public:
  Private() : ffftpt(nullptr) {}
  ~Private() {}
  Ui::MainWindowClass ui;
  FFFTPThread* ffftpt;
};

static MainWindow* _mainwindow = nullptr;
static bool _AskSaveCryptFunc() {
  bool _r = false;
  // Qt::BlockingQueuedConnectionは、他のスレッドからinvokeMethodする場合に必要
  // see
  // https://stackoverflow.com/questions/18725727/how-to-get-a-return-value-from-qmetaobjectinvokemethod
  QMetaObject::invokeMethod(_mainwindow, "askSaveCryptFunc",
                            Qt::BlockingQueuedConnection,
                            Q_RETURN_ARG(bool, _r));
  return _r;
}
static bool _AskMasterPassword(const wchar_t** passwd) {
  qDebug() << __FUNCTION__ << " called.";
  bool _r = false;
  QString passwd_;
  QMetaObject::invokeMethod(_mainwindow, "askMasterPassword",
                            Qt::AutoConnection, Q_RETURN_ARG(bool, _r),
                            Q_ARG(QString&, passwd_));
  qDebug() << __FUNCTION__ << _r << " " << passwd_;
  static std::wstring
      static_pwd;  // staticなので実体はこの関数に残り続ける。ffftp-origin側は結果的にこのポインタを参照することとなる
  static_pwd = passwd_.toStdWString();
  *passwd = static_pwd.c_str();
  return _r;
}
static bool _AskRetryMasterPassword() {
  bool _r = false;
  QMetaObject::invokeMethod(_mainwindow, "askRetryMasterPassword",
                            Qt::AutoConnection, Q_RETURN_ARG(bool, _r));
  return _r;
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
  ffftp_setcallback_askmasterpassword(_AskMasterPassword);
  ffftp_setcallback_askretrymasterpassword(_AskRetryMasterPassword);
}

MainWindow::~MainWindow() {
  d_->ffftpt->terminate();
  delete d_->ffftpt;
}

void MainWindow::timerEvent(QTimerEvent* event) {
  QString msg = QString::fromWCharArray(ffftp_gettaskmessage());
  if (!msg.isEmpty()) {
    d_->ui.widget->addTaskMessage(msg);
  }
  QString title = QString::fromWCharArray(ffftp_getwindowtitle());
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
    QMetaObject::invokeMethod(d_->ffftpt, "connect", Qt::QueuedConnection,
                              Q_ARG(const void*, dialog.hostcontext()));
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
void MainWindow::actionViewFList(bool checked) {}
void MainWindow::actionViewFDetail(bool checked) {}
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
  qDebug() << __FUNCTION__ << " called.";
  ffftp_option option;
  ffftp_option_initialize(&option);
  ffftp_getoption(&option);
  OptionDialog dialog{option, this};
  if (dialog.exec() == QDialog::Accepted) {
    qDebug() << "Accepted.";
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
  if (QMessageBox::question(this, kAskSaveCryptTitle, kAskSaveCryptBody) ==
      QMessageBox::Yes)
    return true;
  return false;
}

bool MainWindow::askMasterPassword(QString& passwd) {
  qDebug() << __FUNCTION__ << " called.";
  bool ok = false;
  passwd = QInputDialog::getText(this, QString(ffftp_get_application_name()),
                                 kPlzInputYourMasterPwd, QLineEdit::Password,
                                 "", &ok);
  return ok;
}

bool MainWindow::askRetryMasterPassword() {
  if (QMessageBox::question(this, QString(ffftp_get_application_name()),
                            kAskRetryInputYourMasterPwd) == QMessageBox::Yes)
    return true;
  return false;
}
