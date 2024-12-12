# 「オプション」ダイアログ 仕様・設計

オプションを編集するダイアログ。メニュー「オプション」→「環境設定」を押下することで表示される。

変数の型について

| | 文字列系 | チェックボックス | コンボボックス |
| --- | --- | --- | --- |
| ffftp | std::wstring | int (YES=ON, NO=OFF) | int (先頭選択時=0) |
| libffftp | wchar_t* | bool (true=ON, false=OFF) | int (先頭選択時=0) |
| ffftpgui | std::wstring | bool (true=ON, false=OFF) | int (先頭選択時=0) |

(YES, NOは#defineで定義されている)

「ヘルプ」ボタン押下時、HTMLヘルプを表示する。

## 目次

* [「ユーザー」タブ](#ユーザータブ)
* [「転送1」タブ](#転送1タブ)
* [「転送2」タブ](#転送2タブ)
* [「転送3」タブ](#転送3タブ)
* [「転送4」タブ](#転送4タブ)

## 「ユーザー」タブ

関連するシンボル名とそのソースファイル名: struct User (option.cpp:82)

![「ユーザー」タブ](./option-01-user.png)

### 各部品の値を保持している変数名およびそれに関連する変数名(01)

| UI部品 | 変数名(ffftp) | 変数名(libffftp) | 変数名(ffftpgui) | 備考 |
| --- | --- | --- | --- | --- |
| メールアドレス | UserMailAdrs | option::option_user::user_mail_adrs | OptionUserForm::Data::user_mail_adrs | 上限文字数=80 |

## 「転送1」タブ

関連するシンボル名とそのソースファイル名: struct Transfer1 (option.cpp:103)

![「転送1」タブ](./option-02-transfer1.png)

### 各部品の値を保持している変数名およびそれに関連する変数名(02)

| UI部品 | 変数名(ffftp) | 変数名(libffftp) | 変数名(ffftpgui) | 備考 |
| --- | --- | --- | --- | --- |
| 常にアスキーモード | TmpTransMode=TRMODE_ASCII | option::option_transfer1::trans_mode=ASCII | OptionTransfer1Form::Data::trans_mode=kASCII |  |
| 常にバイナリモード | TmpTransMode=TRMODE_BIN | option::option_transfer1::trans_mode=BINARY | OptionTransfer1Form::Data::trans_mode=kBinary |  |
| ファイル名で切り替え | TmpTransMode=TRMODE_AUTO | option::option_transfer1::trans_mode=AUTO | OptionTransfer1Form::Data::trans_mode=kAuto |  |
| アスキーモードのファイル名 | AsciiExt | option::option_transfer1::ascii_ext, ascii_ext_cnt | OptionTransfer1Form::Data::ascii_ext | 文字列のvector系 |
| アスキーモードでアップロード時、EOF(Ctrl-Z)を取り除く | RmEOF | option::option_transfer1::rm_eof | OptionTransfer1Form::Data::rm_eof |  |
| アップロード/ダウンロードするファイルのタイムスタンプを維持 | SaveTimeStamp | option::option_transfer1::save_timestamp | OptionTransfer1Form::Data::save_timestamp |  |
| ファイル名のセミコロン以降は取り除いてダウンロード | VaxSemicolon | option::option_transfer1::vax_semicolon | OptionTransfer1Form::Data::vax_semicolon |  |
| ファイル名を変えて転送した場合にディレクトリを作成 | MakeAllDir | option::option_transfer1::make_all_dir | OptionTransfer1Form::Data::make_all_dir |  |
| ファイル一覧の取得に失敗した場合に転送を中止 | AbortOnListError | option::option_transfer1::abort_on_list_error | OptionTransfer1Form::Data::abort_on_list_error |  |
|  |  |  |  |  |

### 「常にアスキーモード」「常にバイナリモード」ラジオボックス

チェック時、アスキーモードのファイル名グループのリストボックス、「追加」および「削除」ボタンを無効にし、非チェック時は有効にする。

### 「追加」ボタン(1)

押下時、ファイル名の入力を求めるダイアログ（下記参照）を表示する。

![「追加」ボタン押下時に表示するダイアログ](./option-02-transfer1-01.png)

当該ダイアログ上の「OK」ボタンを押下時、当該ダイアログを閉じ、リストボックスの最後尾に入力されたファイル名を追加する。

### 「削除」ボタン

選択しているリストボックスの項目を当該リストボックスから削除する。

## 「転送2」タブ

関連するシンボル名とそのソースファイル名: struct Transfer2 (option.cpp:161)

![「転送2」タブ](./option-03-transfer2.png)

### 各部品の値を保持している変数名およびそれに関連する変数名(03)

| UI部品 | 変数名(ffftp) | 変数名(libffftp) | 変数名(ffftpgui) | 備考 |
| --- | --- | --- | --- | --- |
| ファイル名を全て小文字にして転送 | FnameCnv=TRMODE2_LOWER | option::option_transfer2::fname_cnv=LOWER | OptionTransfer2Form::Data::fname_cnv=kLower |  |
| ファイル名を全て大文字にして転送 | FnameCnv=TRMODE2_UPPER | option::option_transfer2::fname_cnv=UPPER | OptionTransfer2Form::Data::fname_cnv=kUpper |  |
| そのままのファイル名で転送 | FnameCnv=TRMODE2_NOCNV | option::option_transfer2::fname_cnv=NOCNV | OptionTransfer2Form::Data::fname_cnv=kNoConv |  |
| ネットワークタイムアウト時間 | TimeOut | option::option_transfer2::timeout | OptionTransfer2Form::Data::timeout | 上限文字数=5 |
| デフォルトのローカルフォルダ | DefaultLocalPath | option::option_transfer2::default_local_path | OptionTransfer2Form::Data::default_local_path | 上限文字数=1024 |

### 「...」ボタン

押下時、フォルダ選択ダイアログを表示し「デフォルトのローカルフォルダ」テキストボックスに選択したフォルダへの絶対パスを表示する。  

## 「転送3」タブ

関連するシンボル名とそのソースファイル名: struct Transfer3 (option.cpp:198)

![「転送3」タブ](./option-04-transfer3.png)

### 各部品の値を保持している変数名およびそれに関連する変数名(04)

| UI部品 | 変数名(ffftp) | 変数名(libffftp) | 変数名(ffftpgui) | 備考 |
| --- | --- | --- | --- | --- |
| アップロードするファイルの属性 | DefAttrList | option::option_transfer3::attrlist_fname, attrlist_attr, attrlist_cnt | OptionTransfer3Form::Data::attr_list |  |
| アップロード時に作成するフォルダの属性を指定する | FolderAttr | option::option_transfer3::is_folder_attr | OptionTransfer3Form::Data::is_folder_attr |  |
| 属性 | FolderAttrNum | option::option_transfer3::folder_attr | OptionTransfer3Form::Data::folder_attr | 上限文字数=5 |

### 「追加」ボタン(2)

押下時、ファイル名とその属性値を求めるダイアログ（下記参照）を表示する。

![「デフォルト属性の設定」ダイアログ](./option-04-transfer3-01.png)

「ファイル名」テキストボックスの上限文字数=1024  
「属性」テキストボックスの上限文字数=4

「OK」ボタンを押下時、当該ダイアログを閉じ、リストボックスの最後尾に入力されたファイル名と属性値を追加する。

「...」ボタン押下時、属性値を編集可能なダイアログ（下記参照）を表示する。この属性の概念はLinuxのファイル属性（パーミッション）のそれと同一である。

![「属性の変更」ダイアログ](./option-04-transfer3-02.png)

「現在の属性」テキストボックスの上限文字数=4

「...」ボタン押下時に設定されていた属性値を初期値として表示する。  
「現在の属性」テキストボックスには各チェックボックスをON/OFFするたび、それ時点での属性値を表示する。  
「OK」ボタン押下時、当該ダイアログを閉じ、編集された属性値を呼び出し元の「属性」テキストボックスに表示する。

## 「転送4」タブ

関連するシンボル名とそのソースファイル名: struct Transfer4 (option.cpp:283)

![「転送4」タブ](./option-05-transfer4.png)

### 各部品の値を保持している変数名およびそれに関連する変数名(05)

| UI部品 | 変数名(ffftp) | 変数名(libffftp) | 変数名(ffftpgui) | 備考 |
| --- | --- | --- | --- | --- |
| ローカルの漢字コード |  |  |  |  |
| Shift_JIS | TmpLocalKanjiCode=TRMODE4_SJIS_CNV | option::option_transfer4::local_kanjicode=SJIS | OptionTransfer4Form::Data::local_kanjicode=kSJIS |  |
| JIS | TmpLocalKanjiCode=TRMODE4_JIS_CNV | option::option_transfer4::local_kanjicode=JIS | OptionTransfer4Form::Data::local_kanjicode=kJIS |  |
| EUC | TmpLocalKanjiCode=TRMODE4_EUC_CNV | option::option_transfer4::local_kanjicode=EUC | OptionTransfer4Form::Data::local_kanjicode=kEUC |  |
| UTF-8 | TmpLocalKanjiCode=TRMODE4_UTF8N_CNV | option::option_transfer4::local_kanjicode=UTF8 | OptionTransfer4Form::Data::local_kanjicode=kUTF8 |  |
| UTF-8 BOM | TmpLocalKanjiCode=TRMODE4_UTF8BOM_CNV | option::option_transfer4::local_kanjicode=UTF8BOM | OptionTransfer4Form::Data::local_kanjicode=kUTF8BOM |  |
| インターネットから入手したものとしてファイルに情報を付加する | MarkAsInternet | option::option_transfer4::mark_as_internet | OptionTransfer4Form::Data::mark_as_internet |  |
|  |  |  |  |  |
