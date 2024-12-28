# Win32 APIとの決別に向けて

## Windows版のQt使用の可否について

Windows版においては、実装の手段としてはQtに置き換えず既存のWin32 APIを使用することもできるが、他のプラットフォームとの統一性を高めるためQtを使用することとする。ただし、LIBFFFTP_NOTUSE_QTスイッチを定義した場合は、Qtに置き換えず既存のWin32 APIを使用することとする。

## 方針

なるべく元のコードはいじらないという方針のもと、Win32 APIの呼び出し自体は削除せずに、スタブを作成し、スタブ呼び出しに置き換える。置き換え対象のWin32 APIの機能が複雑で実装が難しい場合はそのWin32 API呼び出している関数自体を書き換えることも視野に入れる。

関数自体を書き換えた方がよさそうな場合は、元のコードを書き換えるのではなく、defineで切り分けて、追加コードは別ファイルに記述する。もちろんそのコードはlibffftpのプロジェクトに配置する。

## インスタンスハンドル hInstFtp変数

WinMain関数の冒頭でインスタンスハンドルをhInstFtp変数に退避しており、以後様々な場所で参照されているが、その用途は以下の2種類だけ。

* リソース（画像、文字列、メニュー、ダイアログ、アクセラレータなど）を参照するため
* ウィンドウやダイアログ、プロパティシートを生成するため

使用されている関数/構造体と用途、対応策を以下に示す。

| 関数/構造体 | 用途 | 対応策 |
| --- | --- | --- |
| DialogBoxParamW関数 | ダイアログの表示。ダイアログのリソースIDを引数に指定している。 | スタブ化。引数で受け取るリソースIDをライブラリ使用者側に通知する。 |
| MessageBoxIndirectW関数 | メッセージボックスの表示。本文とキャプションの文字列リソースIDを構造体経由で引数に指定している。 | スタブ化。引数で受け取るリソースIDをライブラリ使用者側に通知する。 |
| PropertySheetW関数 | プロパティシート（タブを有するダイアログ）の表示。 | 空のスタブ化。プロパティシートの実装はライブラリ使用者側に委ねる。プロパティシートの実装に必要なデータへの入出力インターフェースを提供する。 |
| LoadStringW関数 | 指定したリソースIDに文字列を取得する。 | 空のスタブ化。ダイアログの表示など他の機能に内包しているため。 |
| GetClassInfoExW関数 | ファイルリストのリストボックスを作成する。 | 空のスタブ化。ウィンドウ関連は実装不要。 |
| ImageList_LoadImageW関数 | ファイルリストのリストボックスを作成時に使用する。 | 空のスタブ化。ウィンドウ関連は実装不要。 |
| CreateWindowExW関数 |  |  |
| LoadBitmapW関数 |  |  |
| CreateDialogW関数 |  |  |
| UnregisterClassW関数 |  |  |
| LoadAcceleratorsW関数 |  |  |
| LoadIconW関数 |  |  |
| NMTTDISPINFOW構造体 |  |  |
| LoadMenuW関数 |  |  |
|  |  |  |

## 使用しているWin32

* Microsoft::WRL::ComPtr<T>
* HFONT
* LOGFONTW
* SIZE
* SecInvalidateHandle
* WSAOVERLAPPED
* SOCKET
* sockaddr_storage
* CtxtHandle
* SecPkgContext_StreamSizes
* SECURITY_STATUS
* ULONG
* 