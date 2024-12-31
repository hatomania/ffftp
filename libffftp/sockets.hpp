#ifndef SOCKETS_94BDBD12_04EE_446D_B4E2_020814ED9AF9_HPP_
#define SOCKETS_94BDBD12_04EE_446D_B4E2_020814ED9AF9_HPP_

#include <memory>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <netdb.h>  // for getaddrinfo
#include <sys/socket.h>
#endif

#include <QSslSocket>

#if 0
namespace std {
template <>
struct default_delete<addrinfo> {
  void operator()(addrinfo* ai) const noexcept { freeaddrinfo(ai); }
};
}  // namespace std
#endif

//--------------------------------------------------------------------------------------------------
// TelnetSocket
class TelnetSocket : public QSslSocket {
  Q_OBJECT
 public:
  explicit TelnetSocket(QObject* parent = Q_NULLPTR);
  // ！重要事項！
  // コンストラクタのhost_or_ipaddrとportは接続先サーバのアドレスとそのポートです。
  // Socks4Socketの場合も、まず接続するのはSOCKS4サーバですのでコンストラクタにはSOCKS4サーバのアドレスとポートを指定します。そして、Socks4Socket::start関数の引数に本来接続したいサーバのアドレスとポートを指定します。
  // しかし！！Socks5Socketの場合は逆です。コンストラクタに本来接続したいサーバのアドレスとポートを、Socks5Socket::start関数の引数にSOCKS5サーバのアドレスとポートを指定します。
  // SOCKS5だけQtを使用している関係上、このようになってしまいました（QtはSOCKS4が未対応なのです。SOCKS5はSOCKS4を内包しているのにね）。
  TelnetSocket(const QString& host_or_ipaddr, quint16 port, QObject* parent = Q_NULLPTR);
  virtual ~TelnetSocket() = default;

  // ベースのconnectToHost関数は使わないでください。同期です。接続するまで帰ってきません
  void connect(const QString& host_or_ipaddr, quint16 port);
  void connect(const QHostAddress& host_or_ipaddr, quint16 port);

  QByteArray transceiveData(const QByteArray& data);
  void sendData(const QByteArray& data);
  QByteArray receiveData();

  QString transceiveMessage(const QString& msg);
  void sendMessage(const QString& msg);
  QString receiveMessage();

  inline const QString& host() const { return host_; }
  inline quint16 port() const { return port_; }
  inline const addrinfo& addrInfo() const { return *addrinfo_; }
  inline const QHostAddress& hostAddr() const { return hostaddr_; }

 private:
  QString host_;
  quint16 port_;
  std::unique_ptr<addrinfo> addrinfo_;
  QHostAddress hostaddr_;

 private:
  Q_DISABLE_COPY_MOVE(TelnetSocket)
};

//--------------------------------------------------------------------------------------------------
// Socks4Socket
class Socks4Socket : public TelnetSocket {
  Q_OBJECT
 public:
  enum class Command : uint8_t {
    Connect = 1,
    Bind    = 2,
  };

 public:
  explicit Socks4Socket(QObject* parent = Q_NULLPTR);
  // コンストラクタにはSOCKS4サーバのアドレスとポートを指定してください。
  Socks4Socket(const QString& host_or_ipaddr, quint16 port, QObject* parent = Q_NULLPTR);
  virtual ~Socks4Socket() = default;

  // 引数に転送先（本来接続したいサーバ）のアドレスとポートを指定してください。
  bool start(Command cmd, const QString& host_or_ipaddr, quint16 port, const QString& userid);
  bool start(Command cmd, const sockaddr& ai_addr, const QString& userid);

 private:
  Q_DISABLE_COPY_MOVE(Socks4Socket)
};

//--------------------------------------------------------------------------------------------------
// Socks5Socket
class Socks5Socket : public Socks4Socket {
  Q_OBJECT
 public:
  enum class Method : uint8_t {
    // SOCKS5プロキシはQtの実装を使用します。Qtは現在以下のメソッドに対応しています。
    NoAuthentication    = 0x00,  // 認証不要
    UsernameAndPassword = 0x02,  // ユーザ名/パスワード
  };

 public:
  explicit Socks5Socket(QObject* parent = Q_NULLPTR);
  // コンストラクタには転送先（本来接続したいサーバ）のアドレスとポートを指定してください。
  Socks5Socket(const QString& host_or_ipaddr, quint16 port, QObject* parent = Q_NULLPTR);
  virtual ~Socks5Socket() = default;

  // 引数にSOCKS5サーバのアドレスとポートを指定してください。
  void start(Method method, const QString& socks5_host_or_ipaddr, quint16 port, const bool plz_resolve = true, const QString& username = QString{}, const QString& password = QString{});
  void start(Method method, const QHostAddress& socks5_host_or_ipaddr, quint16 port, const bool plz_resolve = true, const QString& username = QString{}, const QString& password = QString{});
  // connect後に接続状態にならない場合、原因がプロキシにあるかどうか確認する場合に使用します
  bool isSocks5Error() const;

 private:
  Q_DISABLE_COPY_MOVE(Socks5Socket)
};

//--------------------------------------------------------------------------------------------------
// FtpSocket
class FtpSocket : public Socks5Socket {
  Q_OBJECT

 public:
  enum Command {
    HELP,
  };

 public:
  explicit FtpSocket(QObject* parent = Q_NULLPTR);
  FtpSocket(const QString& host_or_ipaddr, quint16 port = 21,
            QObject* parent = Q_NULLPTR);
  virtual ~FtpSocket() = default;

  QString transceiveCommand(Command cmd, const QString& var = QString{});

 private:
  Q_DISABLE_COPY_MOVE(FtpSocket)
};

#endif  // SOCKETS_94BDBD12_04EE_446D_B4E2_020814ED9AF9_HPP_
