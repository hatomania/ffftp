#pragma once

#include <QMainWindow>

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = Q_NULLPTR);
  virtual ~MainWindow();

 public slots:
  // actions
  void actionConnect();
  void actionQuickConnect();
  void actionDisconnect();
  void actionHostSettings();
  void actionExit();
  void actionImportFromWS_FTP();
  void actionSaveSettingsToFile();
  void actionLoadSettingsFromFile();
  void actionModifyMasterPassword();
  void actionExportFileZillaXML();
  void actionExportWinSCPINI();
  void actionResetSettings();
  void actionDownload();
  void actionUpload();
  void actionDownloadRename();
  void actionUploadRename();
  void actionDownloadRespecify();
  void actionDownloadAsFile();
  void actionUploadMirroring();
  void actionCalcFilesSize();
  void actionDownloadMirroring();
  void actionCmdRm();
  void actionCmdRename();
  void actionCmdReattribute();
  void actionCmdMkdir();
  void actionCommand();
  void actionDirSync(bool checked);
  void actionBmarkAddHost();
  void actionBmarkAddLocal();
  void actionBmarkAddBoth();
  void actionBmarkEdit();
  void actionFilter();
  void actionFind();
  void actionFindNext();
  void actionSelect();
  void actionSelectAll();
  void actionViewFList(bool checked);
  void actionViewFDetail(bool checked);
  void actionSort();
  void actionViewDot(bool checked);
  void actionListWithViewer();
  void actionTaskWithViewer();
  void actionReflesh();
  void actionCalcOnetimePasswd();
  void actionWindowsFWSetting();
  void actionPreference();
  void actionContents();
  void actionOpenWebsite();
  void actionAbout();
  void actionAboutQt();
  void actionModeAscii(bool checked);
  void actionModeBinary(bool checked);
  void actionModeAuto(bool checked);
  void actionLocalSJIS(bool checked);
  void actionLocalEUC(bool checked);
  void actionLocalJIS(bool checked);
  void actionLocalUTF8(bool checked);
  void actionLocalUTF8BOM(bool checked);
  void actionHostSJIS(bool checked);
  void actionHostEUC(bool checked);
  void actionHostJIS(bool checked);
  void actionHostUTF8(bool checked);
  void actionHostUTF8BOM(bool checked);
  void actionHostNocode(bool checked);
  void actionHalfKana2Full(bool checked);
  void actionStopReceiving();
  // others
  bool askSaveCryptFunc();
  bool askMasterPassword(QString& passwd);
  bool askRetryMasterPassword();

 protected:
  void timerEvent(QTimerEvent* event) override;

 private:
  class Private;
  Private* d_;
  Q_DISABLE_COPY(MainWindow)
};
