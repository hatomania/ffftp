# コマンドライン引数

[ ] オプション。指定しても指定しなくてもいい。  
< > 必ず必要。値を指定しなければならない。

すべての引数が省略可能であるため、すべての引数が [ ] となっていることに留意。  
まだ解析途中のため、間違えている可能性があります。

```[text]
[<ftp-server-addr>]         FTPサーバー<ftp-server-addr>に接続する。
[-n, --ini <inifile-path>]  設定をINIファイル<inifile-path>から読み書きするようにする。省略するとレジストリから読み書きする。
[-z, --mpasswd <mpasswd>]   マスターパスワード<mpasswd>を指定する。
[-s, --set <host-name>]     登録したホスト情報<host-name>に接続する。
[-m, --mirror]              ミラーリングアップロードを行う。
[-d, --mirrordown]          ミラーリングダウンロードを行う。
[-eu, -e, --euc]            転送時の漢字コードをEUCとする。
[-ji, -j, --jis]            転送時の漢字コードをJISとする。
[-a, --ascii]               アスキー転送モードで転送する。
[-b, --binary]              バイナリ転送モードで転送する。
[-x, --auto]                転送モードを自動判別する。
[-f, --force]               ミラーリング開始の確認をしない。
[-q, --quit]                転送終了後にプログラムを終了する。
[-k, --kana]                半角かなをそのまま転送する。
[-eun, -u, --eucname]       ファイル名をEUCに変換して転送する？
[-jin, -i, --jisname]       ファイル名をJISに変換して転送する？
[--saveoff]                 設定の保存を中止する？
[--saveon]                  設定の保存を再開する？
[-sj, --sjis]               転送時の漢字コードをShift_JISとする。
[-u8, --utf8]               転送時の漢字コードをUTF-8とする。
[-8b, --utf8bom]            転送時の漢字コードをUTF-8 BOMとする。
[-sjn, --sjisname]          ファイル名をShift_JISに変換して転送する？
[-u8n, --utf8name]          ファイル名をUTF-8に変換して転送する？
[-h, --help]                ヘルプ（HTMLHelpウィンドウ）を起動する。
```

```[c++]
const std::map<std::wstring_view, int> map{
    { L"-m"sv, OPT_MIRROR }, { L"--mirror"sv, OPT_MIRROR },
    { L"-d"sv, OPT_MIRRORDOWN }, { L"--mirrordown"sv, OPT_MIRRORDOWN },
    { L"-eu"sv, OPT_EUC }, { L"-e"sv, OPT_EUC }, { L"--euc"sv, OPT_EUC },
    { L"-ji"sv, OPT_JIS }, { L"-j"sv, OPT_JIS }, { L"--jis"sv, OPT_JIS },
    { L"-a"sv, OPT_ASCII }, { L"--ascii"sv, OPT_ASCII },
    { L"-b"sv, OPT_BINARY }, { L"--binary"sv, OPT_BINARY },
    { L"-x"sv, OPT_AUTO }, { L"--auto"sv, OPT_AUTO },
    { L"-f"sv, OPT_FORCE }, { L"--force"sv, OPT_FORCE },
    { L"-q"sv, OPT_QUIT }, { L"--quit"sv, OPT_QUIT },
    { L"-k"sv, OPT_KANA }, { L"--kana"sv, OPT_KANA },
    { L"-eun"sv, OPT_EUC_NAME }, { L"-u"sv, OPT_EUC_NAME }, { L"--eucname"sv, OPT_EUC_NAME },
    { L"-jin"sv, OPT_JIS_NAME }, { L"-i"sv, OPT_JIS_NAME }, { L"--jisname"sv, OPT_JIS_NAME },
    { L"--saveoff"sv, OPT_SAVEOFF },
    { L"--saveon"sv, OPT_SAVEON },
    { L"-sj"sv, OPT_SJIS }, { L"--sjis"sv, OPT_SJIS },
    { L"-u8"sv, OPT_UTF8N }, { L"--utf8"sv, OPT_UTF8N },
    { L"-8b"sv, OPT_UTF8BOM }, { L"--utf8bom"sv, OPT_UTF8BOM },
    { L"-sjn"sv, OPT_SJIS_NAME }, { L"--sjisname"sv, OPT_SJIS_NAME },
    { L"-u8n"sv, OPT_UTF8N_NAME }, { L"--utf8name"sv, OPT_UTF8N_NAME },
};
```
