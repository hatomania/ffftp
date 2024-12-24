# 使用しているコンポーネント

## CLSID_PersistentZoneIdentifier

代替案: 代替不要

ホストからダウンロードしたファイルに対して、インターネットからダウンロードしたファイルとするゾーンIDを付与するために使用するCOM。  
これはNTFSファイルシステムを利用したWindows固有の機能であり、Linux版では代替不要。

参考URL: <https://qiita.com/SAITO_Keita/items/4ce171bce91b6daa5cbf>

## CLSID_TaskbarList

代替案: QTaskbarControl

タスクバーのアイコン上にファイル転送の進捗（プログレス）を表示するために使用するCOM。Windows 7から実装された機能。ただ、私の環境Windows11 Pro 23H2では動作を確認できなかった。

Linuxのデスクトップ環境でも(少なくともGNOMEであるUbuntu DockやKDE Plasmaは)この機能を有している。しかし、QtにはLinux用はないようだ（Windows用のみQWinTaskbarProgressクラスで機能が提供されている）。

そこで、代替がないか少し調べたところ、有志がタスクバープログレスのクロスプラットフォームライブラリをGitHubで公開しているのを発見した。しかもどうもQtで実装しているようだ。相性が良い。以後、このライブラリの実装を目指して検証しようと思う。

GitHub URL: <https://github.com/Skycoder42/QTaskbarControl>  
参考URL: <https://stackoverflow.com/questions/43875343/kde-taskbar-progress>

続き。QTaskbarControlを実際に動かそうと調べてみたら、内部で使用しているQWinTaskbarProgressクラスはQt6では廃止されていた。<https://doc.qt.io/qt-6/extras-changes-qt6.html>  
Qtの中の人？がQt6への移植のつなぎとしてWinExtraの部分だけGitHubにフォークしてくれていた。<https://github.com/BLumia/qtwinextras>  
ドキュメントによるとどうもQt6ではWindowsのタスクバープログレス機能は復活しないようなニュアンスで書かれていた（『QWinTaskbarProgressクラスは、クロスプラットフォームソリューションを保証するために削除されました。』と書かれていた）。よってつなぎであるフォークのWinExtraまで使って無理して全プラットフォームでQTaskbarControlを使おうと思わず、WindowsならCOMを、その他のプラットフォームならQTaskbarControlを使うべきかも。

## SHCreateStreamOnFileEx関数、CreateXmlWriter関数

代替案: Qt XML

設定をFileZillaの形式へエクスポートする時に使用される関数。FileZillaのファイル形式がXMLなのだろう。XMLファイルを書き出すためのXMLファイルストリームを作成するために用いられている。QtにはXMLのサポートがあります。<https://doc.qt.io/qt-6/qtxml-module.html>

## CLSID_UPnPNAT

代替案: miniupnpc

アクティブモードでの接続時用。サーバ側から制御用コネクションの接続要請が来るため、そのポートを開放しておくため使用するCOM。UPnPのライブラリはいくらかあるが、ポートマッピング機能に特化したのは以下のものがある。

GitHub URL: <https://github.com/Ri0n/QNatPortMapper>

続き。ビルドが通らなかった。作りかけ？ほかにいいのがないか調べていたらminiupnpcを見つけた。libupnpの機能を限定した軽量版。

GitHub URL: <https://github.com/miniupnp/miniupnp>

続き。動作を確認し、実際にポートマッピングを行うことを確認した。

## SSL

代替案: Qt SSL

内部的にはOpenSSLを使用している模様。<https://doc.qt.io/qt-6/ssl.html>

### 以上
