#pragma once

#include <QtWidgets/QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR);
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
    void actionDirSync(bool toggle);
    void actionBmarkAddHost();
    void actionBmarkAddLocal();
    void actionBmarkAddBoth();
    void actionBmarkEdit();
    void actionFilter();
    void actionFind();
    void actionFindNext();
    void actionSelect();
    void actionSelectAll();
    void actionViewFList(bool toggle);
    void actionViewFDetail(bool toggle);
    void actionSort();
    void actionViewDot(bool toggle);
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
    void actionModeAscii(bool toggle);
    void actionModeBinary(bool toggle);
    void actionModeAuto(bool toggle);
    void actionLocalSJIS(bool toggle);
    void actionLocalEUC(bool toggle);
    void actionLocalJIS(bool toggle);
    void actionLocalUTF8(bool toggle);
    void actionLocalUTF8BOM(bool toggle);
    void actionHostSJIS(bool toggle);
    void actionHostEUC(bool toggle);
    void actionHostJIS(bool toggle);
    void actionHostUTF8(bool toggle);
    void actionHostUTF8BOM(bool toggle);
    void actionHostNocode(bool toggle);
    void actionHalfKana2Full(bool toggle);
    void actionStopReceiving();
    // others
    bool askSaveCryptFunc();

protected:
    void timerEvent(QTimerEvent* event) override;

private:
    class Private;
    Private* d_;
    Q_DISABLE_COPY(MainWindow)
};
