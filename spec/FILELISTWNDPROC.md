# ファイルリストのウィンドウプロシージャ

ファイルリストのウィンドウプロシージャ。ローカル側もリモート側も同じプロシージャを使用している。  
ドラッグアンドドロップ機能（ローカル側からリモート側へ、またはその逆へファイル／フォルダをドラッグアンドドロップすると当該ファイル／フォルダを転送する機能）も実装されていると思う。

定義: static LRESULT CALLBACK FileListCommonWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);  
定義場所: filelist.cpp: 330～571行

## WM_CREATE

## WM_SYSKEYDOWN

Alt＋何かのキーを押下した時に呼ばれる処理。`Alt+D`押下でヒストリのテキストボックスにフォースを与えている。

## WM_KEYDOWN

何かのキーを押下した時に呼ばれる処理。`Tab`押下でヒストリのテキストボックスにフォースを与えている。

## WM_SETFOCUS

フォーカスを失っている状態からフォーカスを得た時に呼ばれる処理。

* ツールバーのボタンのEnable/Disableを切り替え
* ステータスバーの表示情報の切り替え

## WM_KILLFOCUS

フォーカスを得ている状態からフォーカスを失った時に呼ばれる処理。

* ツールバーのボタンのEnable/Disableを切り替え
* ステータスバーの表示情報の切り替え

## WM_DROPFILES

ドラッグアンドドロップに関する処理。

## WM_LBUTTONDOWN

ドラッグアンドドロップに関する処理。

## WM_LBUTTONUP

ドラッグアンドドロップに関する処理。

## WM_DRAGDROP

ドラッグアンドドロップに関する処理。

## WM_GETDATA (WM_APP + 101)

### CF_HDROP

ドラッグアンドドロップに関する処理。

## WM_DRAGOVER

ドラッグアンドドロップに関する処理。接続中に限り、ファイルリストのファイルをクリックしたままドラッグすると呼び出される。

## WM_RBUTTONDOWN

## WM_LBUTTONDBLCLK

左クリックをダブルクリックした時に呼ばれる処理。

## WM_MOUSEMOVE

## WM_MOUSEWHEEL

## WM_NOTIFY

### HDN_ITEMCHANGEDW

### 以上
