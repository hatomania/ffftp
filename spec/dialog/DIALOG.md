# ダイアログ

## InputDialog関数

common.h: 1371行目で定義

単に一つの文字列の入力を求めるダイアログを表示する関数。マスターパスワードの入力やユーザー名の入力など一つのテキストの入力を求める。オプションでチェックボックスを一つ設けることができる。表示にはWin32 APIのDialogBoxParamW関数を使用。

| Dialog-ID | イメージ画像 | 備考 |
| --- | --- | --- |
| account_dlg | ![InputDialog account_dlg](./inputdialog-account_dlg.png) |  |
| chdir_dlg | ![InputDialog chdir_dlg](./inputdialog-chdir_dlg.png) |  |
| downname_dlg | ![InputDialog downname_dlg](./inputdialog-downname_dlg.png) |  |
| find_dlg | ![InputDialog find_dlg](./inputdialog-find_dlg.png) |  |
| fname_in_dlg | ![InputDialog fname_in_dlg](./inputdialog-fname_in_dlg.png) |  |
| forcerename_dlg | ![InputDialog forcerename_dlg](./inputdialog-forcerename_dlg.png) |  |
| group_dlg | ![InputDialog group_dlg](./inputdialog-group_dlg.png) |  |
| masterpasswd_dlg | ![InputDialog masterpasswd_dlg](./inputdialog-masterpasswd_dlg.png) | ヘルプID=64 |
| mkdir_dlg | ![InputDialog mkdir_dlg](./inputdialog-mkdir_dlg.png) |  |
| newmasterpasswd_dlg | ![InputDialog newmasterpasswd_dlg](./inputdialog-newmasterpasswd_dlg.png) | ヘルプID=64 |
| passwd_dlg | ![InputDialog passwd_dlg](./inputdialog-passwd_dlg.png) |  |
| re_passwd_dlg | ![InputDialog re_passwd_dlg](./inputdialog-re_passwd_dlg.png) |  |
| somecmd_dlg | ![InputDialog somecmd_dlg](./inputdialog-somecmd_dlg.png) | ヘルプID=23 |
| username_dlg | ![InputDialog username_dlg](./inputdialog-username_dlg.png) |  |

## Dialog関数

dialog.h: 163行目で定義

Win32 APIのDialogBoxParamW関数を使用してダイアログを表示する関数。InputDialogとは異なり多数のUI部品を配置した自由で複雑な機能を持つダイアログを定義できる。

| Dialog-ID | イメージ画像 | 備考 |
| --- | --- | --- |
| about_dlg | ![Dialog about_dlg](./dialog-about_dlg.png) |  |
| bmark_dlg | ![Dialog bmark_dlg](./dialog-bmark_dlg.png) |  |
| bmark_edit_dlg | ![Dialog bmark_edit_dlg](./dialog-bmark_edit_dlg.png) |  |
| certerr_dlg | ![Dialog certerr_dlg](./dialog-certerr_dlg.png) |  |
| chmod_dlg | ![Dialog chmod_dlg](./dialog-chmod_dlg.png) |  |
| corruptsettings_dlg | ![Dialog corruptsettings_dlg](./dialog-corruptsettings_dlg.png) |  |
| cwderr_dlg | ![Dialog cwderr_dlg](./dialog-cwderr_dlg.png) |  |
| def_attr_dlg | ![Dialog def_attr_dlg](./dialog-def_attr_dlg.png) |  |
| delete_dlg | ![Dialog delete_dlg](./dialog-delete_dlg.png) |  |
| down_exist_dlg | ![Dialog down_exist_dlg](./dialog-down_exist_dlg.png) |  |
| downerr_dlg | ![Dialog downerr_dlg](./dialog-downerr_dlg.png) |  |
| exit_dlg | ![Dialog exit_dlg](./dialog-exit_dlg.png) |  |
| filesize_dlg | ![Dialog filesize_dlg](./dialog-filesize_dlg.png) |  |
| filesize_notify_dlg | ![Dialog filesize_notify_dlg](./dialog-filesize_notify_dlg.png) |  |
| filter_dlg | ![Dialog filter_dlg](./dialog-filter_dlg.png) |  |
| forcepasschange_dlg | ![Dialog forcepasschange_dlg](./dialog-forcepasschange_dlg.png) |  |
| groupdel_dlg | ![Dialog groupdel_dlg](./dialog-groupdel_dlg.png) |  |
| hostconnect_dlg | ![Dialog hostconnect_dlg](./dialog-hostconnect_dlg.png) |  |
| hostdel_dlg | ![Dialog hostdel_dlg](./dialog-hostdel_dlg.png) |  |
| hostlist_dlg | ![Dialog hostlist_dlg](./dialog-hostlist_dlg.png) |  |
| hostname_dlg | ![Dialog hostname_dlg](./dialog-hostname_dlg.png) |  |
| ini_from_reg_dlg | ![Dialog ini_from_reg_dlg](./dialog-ini_from_reg_dlg.png) |  |
| mirror_down_dlg | ![Dialog mirror_down_dlg](./dialog-mirror_down_dlg.png) |  |
| mirror_notify_dlg | ![Dialog mirror_notify_dlg](./dialog-mirror_notify_dlg.png) |  |
| mirror_up_dlg | ![Dialog mirror_up_dlg](./dialog-mirror_up_dlg.png) |  |
| mirrordown_notify_dlg | ![Dialog mirrordown_notify_dlg](./dialog-mirrordown_notify_dlg.png) |  |
| move_notify_dlg | ![Dialog move_notify_dlg](./dialog-move_notify_dlg.png) |  |
| noresume_dlg | ![Dialog noresume_dlg](./dialog-noresume_dlg.png) |  |
| otp_calc_dlg | ![Dialog otp_calc_dlg](./dialog-otp_calc_dlg.png) |  |
| otp_notify_dlg | ![Dialog otp_notify_dlg](./dialog-otp_notify_dlg.png) |  |
| rasnotify_dlg | ![Dialog rasnotify_dlg](./dialog-rasnotify_dlg.png) |  |
| rasreconnect_dlg | ![Dialog rasreconnect_dlg](./dialog-rasreconnect_dlg.png) |  |
| reginit_dlg | ![Dialog reginit_dlg](./dialog-reginit_dlg.png) |  |
| rename_dlg | ![Dialog rename_dlg](./dialog-rename_dlg.png) |  |
| savecrypt_dlg | ![Dialog savecrypt_dlg](./dialog-savecrypt_dlg.png) |  |
| savepass_dlg | ![Dialog savepass_dlg](./dialog-savepass_dlg.png) |  |
| sel_local_dlg | ![Dialog sel_local_dlg](./dialog-sel_local_dlg.png) |  |
| sel_remote_dlg | ![Dialog sel_remote_dlg](./dialog-sel_remote_dlg.png) |  |
| sort_dlg | ![Dialog sort_dlg](./dialog-sort_dlg.png) |  |
| transfer_dlg | ![Dialog transfer_dlg](./dialog-transfer_dlg.png) |  |
| up_exist_dlg | ![Dialog up_exist_dlg](./dialog-up_exist_dlg.png) |  |
| updown_as_dlg | ![Dialog updown_as_dlg](./dialog-updown_as_dlg.png) |  |
| updown_as_with_ext_dlg | ![Dialog updown_as_with_ext_dlg](./dialog-updown_as_with_ext_dlg.png) |  |
| uperr_dlg | ![Dialog uperr_dlg](./dialog-uperr_dlg.png) |  |

## （参考）未使用Dialog

ダイアログIDが定義されているにもかかわらず、どこからも参照がされていないダイアログ。

| Dialog-ID | イメージ画像 | 備考 |
| --- | --- | --- |
| chdir_br_dlg | ![unused Dialog chdir_br_dlg](./unuseddialog-chdir_br_dlg.png) |  |
| diskfull_dlg | ![unused Dialog diskfull_dlg](./unuseddialog-diskfull_dlg.png) |  |
| FILEOPENORD_1 | ![unused Dialog FILEOPENORD_1](./unuseddialog-fileopenord_1.png) |  |
| updatesslroot_dlg | ![unused Dialog updatesslroot_dlg](./unuseddialog-updatesslroot_dlg.png) |  |

## （参考）プロパティシートのタブページとして組み込まれるDialog

プロパティシートのタブページとして組み込まれることを予定されたダイアログ。ホスト設定ダイアログとオプションダイアログで使用される。

| Dialog-ID | イメージ画像 | 備考 |
| --- | --- | --- |
| hset_adv_dlg | ![Form Dialog hset_adv_dlg](./formdialog-hset_adv_dlg.png) |  |
| hset_adv2_dlg | ![Form Dialog hset_adv2_dlg](./formdialog-hset_adv2_dlg.png) |  |
| hset_adv3_dlg | ![Form Dialog hset_adv3_dlg](./formdialog-hset_adv3_dlg.png) |  |
| hset_code_dlg | ![Form Dialog hset_code_dlg](./formdialog-hset_code_dlg.png) |  |
| hset_crypt_dlg | ![Form Dialog hset_crypt_dlg](./formdialog-hset_crypt_dlg.png) |  |
| hset_dialup_dlg | ![Form Dialog hset_dialup_dlg](./formdialog-hset_dialup_dlg.png) |  |
| hset_main_dlg | ![Form Dialog hset_main_dlg](./formdialog-hset_main_dlg.png) |  |
| opt_connect_dlg | ![Form Dialog opt_connect_dlg](./formdialog-opt_connect_dlg.png) |  |
| opt_disp1_dlg | ![Form Dialog opt_disp1_dlg](./formdialog-opt_disp1_dlg.png) |  |
| opt_disp2_dlg | ![Form Dialog opt_disp2_dlg](./formdialog-opt_disp2_dlg.png) |  |
| opt_fire_dlg | ![Form Dialog opt_fire_dlg](./formdialog-opt_fire_dlg.png) |  |
| opt_mirror_dlg | ![Form Dialog opt_mirror_dlg](./formdialog-opt_mirror_dlg.png) |  |
| opt_misc_dlg | ![Form Dialog opt_misc_dlg](./formdialog-opt_misc_dlg.png) |  |
| opt_notify_dlg | ![Form Dialog opt_notify_dlg](./formdialog-opt_notify_dlg.png) |  |
| opt_tool_dlg | ![Form Dialog opt_tool_dlg](./formdialog-opt_tool_dlg.png) |  |
| opt_trmode1_dlg | ![Form Dialog opt_trmode1_dlg](./formdialog-opt_trmode1_dlg.png) |  |
| opt_trmode2_dlg | ![Form Dialog opt_trmode2_dlg](./formdialog-opt_trmode2_dlg.png) |  |
| opt_trmode3_dlg | ![Form Dialog opt_trmode3_dlg](./formdialog-opt_trmode3_dlg.png) |  |
| opt_trmode4_dlg | ![Form Dialog opt_trmode4_dlg](./formdialog-opt_trmode4_dlg.png) |  |
| opt_user_dlg | ![Form Dialog opt_user_dlg](./formdialog-opt_user_dlg.png) |  |

## Message関数

common.h: 1304行目で定義

Win32 APIのMessageBoxIndirectW関数を使用して単純なモーダルのメッセージボックスを表示する関数。[OK]ボタンのみを配置したメッセージや、加えて[キャンセル]ボタンを配置したメッセージなどがある。キャプションは特に指定がない限りすべて`FFFTP`である。

| Message-ID | メッセージ | スタイル | 備考 |
| --- | --- | --- | --- |
| IDS_REMOVE_READONLY | `読み取り専用ファイルです.読み取り専用属性を解除しますか？` | MB_YESNO | キャプションID=IDS_MSGJPN086=`ダウンロード` |
| IDS_MASTER_PASSWORD_INCORRECT | `指定されたマスターパスワードが登録されたものと一致しません.\r\n再度入力しますか？\r\n「いいえ」を選ぶと記憶されたFTPパスワードは利用できません.` | MB_YESNO \| MB_ICONEXCLAMATION |  |
| IDS_FAIL_TO_INIT_OLE | `OLEの初期化に失敗しました.` | MB_OK \| MB_ICONERROR |  |
| IDS_ERR_SSL | `SSLの初期化に失敗しました.\nアプリケーションを終了します.` | MB_OK \| MB_ICONERROR |  |
| IDS_FOUND_NEW_VERSION_INI | `新しいバージョンの設定が検出されました.\nこのバージョンでは一部の設定が正しく読み込まれない,またはこのバージョンで設定を上書きすると設定が変化する可能性があります.\nこのバージョン用に設定を上書きして保存するには「はい」を選択してください.\n設定をレジストリではなくINIファイルに保存するには「いいえ」を選択してください.\n読み取り専用で設定を読み込むには「キャンセル」を選択してください.` | MB_YESNOCANCEL \| MB_DEFBUTTON2 |  |
| IDS_MANAGE_STATEFUL_FTP | `WindowsファイアウォールのステートフルFTPフィルタの有効無効を設定します.\nこれはWindows Vista以降でのみ動作します.\n有効化または無効化することで通信状態が改善されることがあります.\n有効化するには「はい」,無効化するには「いいえ」を選択してください.` | MB_YESNOCANCEL |  |
| IDS_FAIL_TO_MANAGE_STATEFUL_FTP | `ステートフルFTPフィルタを設定できませんでした.` | MB_OK \| MB_ICONERROR |  |
| IDS_NEED_RESTART | `設定をファイルから復元するためには,FFFTPを再起動してください.` | MB_OK |  |
| IDS_PASSWORD_ISNOT_IDENTICAL | `新しいマスターパスワードが一致しません.` | MB_OK \| MB_ICONERROR |  |
| IDS_FAIL_TO_EXEC_REDEDIT | `レジストリエディタが起動できませんでした` | MB_OK \| MB_ICONERROR |  |
| IDS_MUST_BE_REG_OR_INI | `設定ファイルは拡張子が.regか.iniでなければなりません.` | MB_OK \| MB_ICONERROR |  |
| IDS_CANT_SAVE_TO_INI | `INIファイルに設定が保存できません` | MB_OK \| MB_ICONERROR |  |
| IDS_FAIL_TO_EXPORT | `設定のエクスポートに失敗しました.\n保存する場所や形式を変更してください.` | MB_OK \| MB_ICONERROR |  |
| IDS_NEED_EXSITING_WINSCP_INI | `この機能で新規作成したINIファイルをWinSCPで読み込むと全ての設定が失われます.\nすでにWinSCPをお使いでありホストの設定のみ移行したい場合は既存のWinSCP.iniを選択してください.` | MB_OK |  |

### 以上
