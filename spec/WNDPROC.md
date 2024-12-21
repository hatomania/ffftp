# メインウィンドウのウィンドウプロシージャ

メインウィンドウのウィンドウプロシージャ。

定義: static LRESULT CALLBACK FtpWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);  
定義場所: main.cpp: 606～1477行

## WM_CREATE

ウィンドウが生成された時に呼ばれる処理。正確にはメッセージループに入る前のCreateWindow関数内部から呼ばれる。

以下の通りタイマーを生成する。

| タイマーID | 周期(ms) |
| --- | --- |
| 1 | 1000 |
| 2 | 100 |

## WM_TIMER

タイマーの周期が達した時に呼ばれる処理。

| タイマーID | 処理内容 |
| --- | --- |
| 1 | ローカルファイルリストの更新、自動切断対策 |
| 2 | タスクバーのプログレスの更新 |

## WM_COMMAND

メニューの項目、またはツールバーのボタンをクリックした時に呼ばれる処理。

### MENU_CONNECT

メニュー[接続]->[接続]をクリックした、またはツールバーの[接続]ボタンをクリックした時に呼ばれる処理。

### MENU_CONNECT_NUM

コマンドライン引数に`-s`または`--set`を指定した状態で起動した時に時に呼ばれる処理。アプリケーション起動直後にコマンドライン引数で指定したホストへ自動で接続を試みる。ミラーリングアップロードまたはミラーリングダウンロードの指定があった場合は、接続が成功したのち、それらを試みる。

### MENU_SET_CONNECT

メニュー[接続]->[ホストの設定]をクリックした時に呼ばれる処理。

### MENU_QUICK

### MENU_DISCONNECT

### MENU_HIST_1～MENU_HIST_20

### MENU_UPDIR

### MENU_DCLICK

### MENU_OPEN

### MENU_OPEN1

### MENU_OPEN2

### MENU_OPEN3

### MENU_REMOTE_UPDIR

### MENU_LOCAL_UPDIR

### MENU_REMOTE_CHDIR

### MENU_LOCAL_CHDIR

### MENU_DOWNLOAD

### MENU_DOWNLOAD_AS

### MENU_DOWNLOAD_AS_FILE

### MENU_DOWNLOAD_ALL

### MENU_DOWNLOAD_NAME

### MENU_UPLOAD

### MENU_UPLOAD_AS

### MENU_UPLOAD_ALL

### MENU_MIRROR_UPLOAD

### MENU_MIRROR_DOWNLOAD

### MENU_FILESIZE

### MENU_DELETE

### MENU_RENAME

### MENU_MKDIR

### MENU_CHMOD

### MENU_SOMECMD

### MENU_OPTION

### MENU_FILTER

### MENU_SORT

### MENU_EXIT

### MENU_AUTO_EXIT

### MENU_ABOUT

### MENU_TEXT

### MENU_BINARY

### MENU_AUTO

### MENU_XFRMODE

### MENU_KNJ_SJIS, MENU_KNJ_EUC, MENU_KNJ_JIS, MENU_KNJ_UTF8N, MENU_KNJ_UTF8BOM, MENU_KNJ_NONE

### MENU_L_KNJ_SJIS, MENU_L_KNJ_EUC, MENU_L_KNJ_JIS, MENU_L_KNJ_UTF8N, MENU_L_KNJ_UTF8BOM

### MENU_KANACNV

### MENU_REFRESH

### MENU_LIST

### MENU_REPORT

### REFRESH_LOCAL

### REFRESH_REMOTE

### COMBO_LOCAL, COMBO_REMOTE

### MENU_HELP

### MENU_HELP_TROUBLE

### MENU_BMARK_ADD

### MENU_BMARK_ADD_LOCAL

### MENU_BMARK_ADD_BOTH

### MENU_BMARK_EDIT

### MENU_SELECT_ALL

### MENU_SELECT

### MENU_FIND

### MENU_FINDNEXT

### MENU_DOTFILE

### MENU_SYNC

### MENU_IMPORT_WS

### MENU_REGSAVE

### MENU_REGLOAD

### MENU_REGINIT

### MENU_CHANGEPASSWD

### MENU_DIRINFO

### MENU_TASKINFO

### MENU_ABORT

### MENU_OTPCALC

### MENU_FW_FTP_FILTER

### MENU_URL_COPY

### MENU_APPKEY

### MENU_SWITCH_OSS

### MENU_REMOTE_MOVE_UPDIR

### MENU_EXPORT_FILEZILLA_XML

### MENU_EXPORT_WINSCP_INI

### default

## WM_NOTIFY

### TTN_GETDISPINFOW

### LVN_COLUMNCLICK

### LVN_ITEMCHANGED

## WM_SIZE

## WM_MOVING

## WM_SETFOCUS

## WM_LBUTTONDOWN, WM_LBUTTONUP, WM_MOUSEMOVE

## WM_CHANGE_COND

## WM_REFRESH_LOCAL_FLG

## WM_REFRESH_REMOTE_FLG

## WM_RECONNECTSOCKET

## WM_MAINTHREADRUNNER

## WM_PAINT

## WM_DESTROY

## WM_QUERYENDSESSION

## WM_CLOSE

### 以上
