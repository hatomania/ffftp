# ffftp (Qt version)
ffftpをQtやPOSIXその他のクロスプラットフォームライブラリを用いて、クロスプラットフォーム化する試み。

# 全体的な思想
1. GUIにはQt6を用いる
2. WindowsでもLinuxでもビルド可能
3. 最終的なビルドにはQtCreatorを用いる
4. 

# デザイン
* 既存のソースはなるべくいじらない
* 既存のソース全体をモジュール化のような感じでライブラリ化して自前で実装するインターフェースを介して情報をやり取りする<br>
（GUIと処理は完全に分ける必要がある）
* 

# 既知の問題
* GCCでstd::formatがまだ実装されていない -> QtかBoostのformatで代用できる？
* COMの代替(UPnP) -> https://github.com/pupnp/pupnp が使える？
* concurrent_queue.hがない -> https://github.com/oneapi-src/oneTBB が使える？
* モチベーションの維持
* その他たくさん...
