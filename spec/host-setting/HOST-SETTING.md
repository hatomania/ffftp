# 「ホストの設定」ダイアログ 仕様・設計

接続先リストを編集するダイアログ。

これはダイアログというか正確にはプロパティシート。Win32 APIのPropertySheetW関数を利用して生成している。  
なのでリソースファイル(*.rc)には「ホストの設定」というキャプションのダイアログは定義されていない。

UI部品設定値のデフォルト値について、デフォルト値はエンドユーザーが設定できる仕様になっている。  
一度もエンドユーザーに設定されていないデフォルト値（つまり、デフォルト値のデフォルト値）を含め、デフォルト値はアプリ側(ffftp)から提供される。  
従ってデフォルト値の仕様の解析は行わない。ただし、一部のUI部品については固定のデフォルト値が採用されているためそれについてはその限りではない。

変数の型について

| | 文字列系 | チェックボックス | コンボボックス |
| --- | --- | --- | --- |
| ffftp | std::wstring | int (YES=ON, NO=OFF) | int (先頭選択時=0) |
| libffftp | char* | bool (true=ON, false=OFF) | int (先頭選択時=0) |
| ffftpgui | std::wstring | bool (true=ON, false=OFF) | int (先頭選択時=0) |

(YES, NOは#defineで定義されている)

「ヘルプ」ボタン押下時、HTMLヘルプを表示する。

## 目次

* [「基本」タブ](#基本タブ)
* [「拡張」タブ](#拡張タブ)
* [「文字コード」タブ](#文字コードタブ)

## 「基本」タブ

関連するシンボル名とそのソースファイル名: struct General (hostman.cpp:943)

![「基本」タブ](./host-setting-1-general.png)

### 各部品の値を保持している変数名およびそれに関連する変数名(1)

| UI部品 | 変数名(ffftp) | 変数名(libffftp) | 変数名(ffftpgui) | 備考 |
| --- | --- | --- | --- | --- |
| ホストの設定名 | HOSTDATA::HostName | hostdata::hostdata_general::host_name | HostSettingGeneralForm::Data::host_name | 上限文字数=40 |
| ホスト名 | HOSTDATA::HostAdrs | hostdata::hostdata_general::host_adrs | HostSettingGeneralForm::Data::host_adrs | 上限文字数=80 |
| ユーザー名 | HOSTDATA::UserName | hostdata::hostdata_general::username | HostSettingGeneralForm::Data::username | 上限文字数=80 |
| パスワード | HOSTDATA::PassWord | hostdata::hostdata_general::password | HostSettingGeneralForm::Data::password | 上限文字数=80 |
| anonymous | HOSTDATA::Anonymous | hostdata::hostdata_general::anonymous | HostSettingGeneralForm::Data::anonymous | - |
| ローカルの初期フォルダ | HOSTDATA::LocalInitDir | hostdata::hostdata_general::initdir_local | HostSettingGeneralForm::Data::initdir_local | 上限文字数=1024-40=984 |
| リモートの初期フォルダ | HOSTDATA::RemoteInitDir | hostdata::hostdata_general::initdir_remote | HostSettingGeneralForm::Data::initdir_remote | 上限文字数=1024-40=984 |
| 現在のフォルダ | AskRemoteCurDir関数で取得可能 | hostdata::hostdata_general::initdir_remote_now | HostSettingGeneralForm::Data::initdir_remote_now | カレントディレクトリパス文字列を保持[(参照)](#現在のフォルダボタン) |
| 最後にアクセスした～ | HOSTDATA::LastDir | hostdata::hostdata_general::last_dir | HostSettingGeneralForm::Data::last_dir | - |

### 「anonymous」チェックボックス

OFFからONにしたとき、以下の通り、値を書き換える。

| ユーザー名 | パスワード |
| --- | --- |
| anonymous | who\@example.com |

ONからOFFにしたとき、ONしたときに入力されていた「ユーザー名」および「パスワード」をそれぞれ書き戻す。

### 「...」ボタン

押下時、フォルダ選択ダイアログを表示し「ローカルの初期フォルダ」に選択したフォルダへの絶対パスを表示する。  

### 「現在のフォルダ」ボタン

リモート先に接続状態でないときは、Disableとする。  
押下時、リモート側のカレントディレクトリパスを「リモートの初期フォルダ」に表示する。

### 「OK」ボタン(1)

* 各文字列型の変数について、前後の連続する空欄があれば削除する。
* 「ホストの設定名」が空かつ「ホスト名」が空でなければ「ホストの設定名」を「ホスト名」とする。
* その逆、「ホストの設定名」が空でない、かつ「ホスト名」が空であれば「ホスト名」と「ホストの設定名」する。

### その他1

* 現在の仕様だと、「ホストの設定名」および「ホスト名」が両方空でも設定できてしまう。

## 「拡張」タブ

関連するシンボル名とそのソースファイル名: struct Advanced (hostman.cpp:1015)

![「拡張」タブ](./host-setting-2-advanced.png)

### 各部品の値を保持している変数名およびそれに関連する変数名(2)

| UI部品 | 変数名(ffftp) | 変数名(libffftp) | 変数名(ffftpgui) | 備考 |
| --- | --- | --- | --- | --- |
| FireWallを使う | HOSTDATA::FireWall | hostdata::hostdata_advanced::firewall | HostSettingAdvancedForm::Data::firewall |  |
| PASVモードを使う | HOSTDATA::Pasv | hostdata::hostdata_advanced::pasv | HostSettingAdvancedForm::Data::pasv |  |
| フォルダ同時移動を使う | HOSTDATA::SyncMove | hostdata::hostdata_advanced::syncmove | HostSettingAdvancedForm::Data::syncmove |  |
| ポート番号 | HOSTDATA::Port | hostdata::hostdata_advanced::port | HostSettingAdvancedForm::Data::port | 上限文字数=5 |
| アカウント | HOSTDATA::Account | hostdata::hostdata_advanced::account | HostSettingAdvancedForm::Data::account | 上限文字数=80 |
| ホストのタイムゾーン | HOSTDATA::TimeZone | hostdata::hostdata_advanced::timezone | HostSettingAdvancedForm::Data::timezone |  |
| セキュリティ | HOSTDATA::Security | hostdata::hostdata_advanced::security | HostSettingAdvancedForm::Data::security |  |
| 接続時にホストに送るコマンド | HOSTDATA::InitCmd | hostdata::hostdata_advanced::initcmd | HostSettingAdvancedForm::Data::initcmd | 上限文字数=256 |

### 「標準」ボタン

押下時「ポート番号」に21を設定する。

### 「ホストのタイムゾーン」コンボボックス

リストは以下の通り:

```text
GMT-12:00
GMT-11:00
GMT-10:00
GMT-09:00
GMT-08:00
GMT-07:00
GMT-06:00
GMT-05:00
GMT-04:00
GMT-03:00
GMT-02:00
GMT-01:00
GMT
GMT+01:00
GMT+02:00
GMT+03:00
GMT+04:00
GMT+05:00
GMT+06:00
GMT+07:00
GMT+08:00
GMT+09:00 (日本)
GMT+10:00
GMT+11:00
GMT+12:00
```

### 「セキュリティ」コンボボックス

リストは以下の通り:

```text
使用しない
自動認識
OTP MD4, S/KEY
OTP MD5
OTP SHA-1
```

## 「文字コード」タブ

関連するシンボル名とそのソースファイル名: struct KanjiCode (hostman.cpp:1067)

![「拡張」タブ](./host-setting-3-kanjicode.png)

### 各部品の値を保持している変数名およびそれに関連する変数名(3)

| UI部品 | 変数名(ffftp) | 変数名(libffftp) | 変数名(ffftpgui) | 備考 |
| --- | --- | --- | --- | --- |
| **ホストの漢字コード** |  |  |  |  |
| 無変換 | HOSTDATA::KanjiCode==HSET_NO_CNV | hostdata::hostdata_kanjicode::kanji_code==KC_NOP | HostSettingKanjiCodeForm::Data::kanji_code==kNOP |  |
| Shift_JIS | HOSTDATA::KanjiCode==HSET_SJIS_CNV | hostdata::hostdata_kanjicode::kanji_code==KC_SJIS | HostSettingKanjiCodeForm::Data::kanji_code==kSJIS |  |
| JIS | HOSTDATA::KanjiCode==HSET_JIS_CNV | hostdata::hostdata_kanjicode::kanji_code==KC_JIS | HostSettingKanjiCodeForm::Data::kanji_code==kJIS |  |
| EUC | HOSTDATA::KanjiCode==HSET_EUC_CNV | hostdata::hostdata_kanjicode::kanji_code==KC_EUC | HostSettingKanjiCodeForm::Data::kanji_code==kEUC |  |
| UTF-8 | HOSTDATA::KanjiCode==HSET_UTF8N_CNV | hostdata::hostdata_kanjicode::kanji_code==KC_UTF8N | HostSettingKanjiCodeForm::Data::kanji_code==kUTF8N |  |
| UTF-8 BOM | HOSTDATA::KanjiCode==HSET_UTF8BOM_CNV | hostdata::hostdata_kanjicode::kanji_code==KC_UTF8BOM | HostSettingKanjiCodeForm::Data::kanji_code==kUTF8BOM |  |
| 半角カナを全角に変換 | HOSTDATA::KanaCnv | hostdata::hostdata_kanjicode::kana_cnv | HostSettingKanjiCodeForm::Data::kana_cnv | Shift_JIS,JIS,EUC選択時のみEnable |
| **ファイル名の漢字コード** |  |  |  |  |
| 自動 | HOSTDATA::NameKanjiCode==HSET_FN_AUTO_CNV | hostdata::hostdata_kanjicode::name_kanji_code==KC_AUTO | HostSettingKanjiCodeForm::Data::name_kanji_code==kAUTO |  |
| Shift_JIS | HOSTDATA::NameKanjiCode==HSET_FN_SJIS_CNV | hostdata::hostdata_kanjicode::name_kanji_code==KC_SJIS | HostSettingKanjiCodeForm::Data::name_kanji_code==kSJIS |  |
| JIS | HOSTDATA::NameKanjiCode==HSET_FN_JIS_CNV | hostdata::hostdata_kanjicode::name_kanji_code==KC_JIS | HostSettingKanjiCodeForm::Data::name_kanji_code==kJIS |  |
| EUC | HOSTDATA::NameKanjiCode==HSET_FN_EUC_CNV | hostdata::hostdata_kanjicode::name_kanji_code==KC_EUC | HostSettingKanjiCodeForm::Data::name_kanji_code==kEUC |  |
| Samba-HEX | HOSTDATA::NameKanjiCode==HSET_FN_SMH_CNV | hostdata::hostdata_kanjicode::name_kanji_code==KC_SMH | HostSettingKanjiCodeForm::Data::name_kanji_code==kSMH |  |
| Samba-CAP | HOSTDATA::NameKanjiCode==HSET_FN_SMC_CNV | hostdata::hostdata_kanjicode::name_kanji_code==KC_SMC | HostSettingKanjiCodeForm::Data::name_kanji_code==kSMC |  |
| UTF-8 | HOSTDATA::NameKanjiCode==HSET_FN_UTF8N_CNV | hostdata::hostdata_kanjicode::name_kanji_code==KC_UTF8N | HostSettingKanjiCodeForm::Data::name_kanji_code==kUTF8N |  |
| UTF-8 HFS+ | HOSTDATA::NameKanjiCode==HSET_FN_UTF8HFSX_CNV | hostdata::hostdata_kanjicode::name_kanji_code==KC_UTF8HFSX | HostSettingKanjiCodeForm::Data::name_kanji_code==kUTF8HFSX |  |
| 半角カナを全角に変換 | HOSTDATA::NameKanaCnv | hostdata::hostdata_kanjicode::name_kana_cnv | HostSettingKanjiCodeForm::Data::name_kana_cnv | JIS,EUC選択時のみEnable |
