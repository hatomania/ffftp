#pragma once

#include <QMainWindow>

#include "ffftp_common.h"

class MainWindow : public QMainWindow {
  Q_OBJECT;

 public:
  explicit MainWindow(QWidget* parent = Q_NULLPTR);
  virtual ~MainWindow();

  static unsigned long long ffftp_proc(unsigned long long msg, ffftp_procparam* param);

 private Q_SLOTS:
  // [接続]メニュー
  void actionConnect();                   // [接続]
  void actionQuickConnect();              // [クイック接続]
  void actionDisconnect();                // [切断]
  void actionHostSettings();              // [ホストの設定]
  void actionExit();                      // [終了]
  void actionImportFromWS_FTP();          // [設定]->[WS_FTPから設定をインポート]
  void actionSaveSettingsToFile();        // [設定]->[設定をファイルに保存]
  void actionLoadSettingsFromFile();      // [設定]->[設定をファイルから復元]
  void actionModifyMasterPassword();      // [設定]->[マスターパスワードの変更]
  void actionExportFileZillaXML();        // [設定]->[FileZilla XMLに設定をエクスポート]
  void actionExportWinSCPINI();           // [設定]->[WinSCP INIに設定をエクスポート]
  void actionResetAllSettings();          // [設定]->[全設定の消去]

  // [コマンド]メニュー
  void actionDownload();                  // [ダウンロード]
  void actionUpload();                    // [アップロード]
  void actionDownloadRename();            // [名前を変えてダウンロード]
  void actionUploadRename();              // [名前を変えてアップロード]
  void actionDownloadRespecify();         // [名前を指定してダウンロード]
  void actionDownloadAsFile();            // [ファイルとしてダウンロード]
  void actionUploadMirroring();           // [ミラーリングアップロード]
  void actionCalcFilesSize();             // [ファイル容量計算]
  void actionDownloadMirroring();         // [ミラーリングダウンロード]
  void actionCmdRm();                     // [削除]
  void actionCmdRename();                 // [名前変更]
  void actionCmdReattribute();            // [属性変更]
  void actionCmdMkdir();                  // [フォルダ作成]
  void actionCommand();                   // [任意のコマンド]
  void actionDirSync(bool checked);       // [フォルダ同時移動]

  // [ブックマーク]メニュー
  void actionBmarkAddHost();              // [追加－ホスト側]
  void actionBmarkAddLocal();             // [追加－ローカル側]
  void actionBmarkAddBoth();              // [追加－両方]
  void actionBmarkEdit();                 // [編集]

  // [表示]メニュー
  void actionFilter();                    // [フィルタ]
  void actionFind();                      // [検索]
  void actionFindNext();                  // [次を検索]
  void actionSelect();                    // [選択]
  void actionSelectAll();                 // [全選択/解除]
  void actionViewFList(bool checked);     // [形式]->[一覧]
  void actionViewFDetail(bool checked);   // [形式]->[詳細]
  void actionSort();                      // [ソート]
  void actionViewDot(bool checked);       // [.で始まるファイルを表示]
  void actionListWithViewer();            // [ファイル一覧をビューアで表示]
  void actionTaskWithViewer();            // [処理内容をビューアで表示]
  void actionReflesh();                   // [最新の情報に更新]

  // [ツール]メニュー
  void actionCalcOnetimePasswd();         // [ワンタイムパスワード計算]
  void actionWindowsFWSetting();          // [WindowsファイアウォールのステートフルFTPフィルタの設定]

  // [オプション]メニュー
  void actionPreference();                // [環境設定]

  // [ヘルプ]メニュー
  void actionContents();                  // [目次]
  void actionOpenWebsite();               // [ウェブサイトを開く]
  void actionAbout();                     // [FFFTPについて]
  void actionAboutQt();                   // [Qtについて]

  // ツールボタン
  void actionModeAscii(bool checked);     // [アスキー転送モード]
  void actionModeBinary(bool checked);    // [バイナリ転送モード]
  void actionModeAuto(bool checked);      // [ファイル名で転送モード切替え]
  void actionLocalSJIS(bool checked);     // [ローカルの漢字コードはShift_JIS]
  void actionLocalEUC(bool checked);      // [ローカルの漢字コードはEUC]
  void actionLocalJIS(bool checked);      // [ローカルの漢字コードはJIS]
  void actionLocalUTF8(bool checked);     // [ローカルの漢字コードはUTF-8]
  void actionLocalUTF8BOM(bool checked);  // [ローカルの漢字コードはUTF-8 BOM]
  void actionHostSJIS(bool checked);      // [ホストの漢字コードはShift_JIS]
  void actionHostEUC(bool checked);       // [ホストの漢字コードはEUC]
  void actionHostJIS(bool checked);       // [ホストの漢字コードはJIS]
  void actionHostUTF8(bool checked);      // [ホストの漢字コードはUTF-8]
  void actionHostUTF8BOM(bool checked);   // [ホストの漢字コードはUTF-8 BOM]
  void actionHostNocode(bool checked);    // [漢字コードの変換なし]
  void actionHalfKana2Full(bool checked); // [半角カナを全角に変換]
  void actionStopReceiving();             // [受信中止]

  // コモンダイアログの表示系
  bool openFileName(QString& out_filepath, const QString& path, const QString& filter, const QString& caption = QString());
  bool saveFileName(QString& out_filepath, const QString& path, const QString& filter, const QString& caption = QString());

  // ダイアログの表示系
  bool showHostListDialog();
  bool showHostConnectDialog();
  bool showHostQuickConnectDialog(const ffftp_procparam_quickconnect& inparam, ffftp_procparam_quickconnect& outparam);
  bool showOptionDialog();

  // メッセージボックスの表示系
  bool askMasterPassword(QString& passwd);
  bool askRetryMasterPassword();
  bool askSaveCryptFunc();

 private:
  void timerEvent(QTimerEvent* event) override;
  void closeEvent(QCloseEvent* event) override;
  static int messageBox(unsigned long long msgid, unsigned long long capid);

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(MainWindow);
};
