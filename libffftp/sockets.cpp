#include "sockets.hpp"

#include <QNetworkProxy>

namespace {
constexpr const int kTimeoutConnected{5000};
inline std::unique_ptr<addrinfo> hostPort2AddrInfo(const QString& host_or_ipaddr, quint16 port) {
  addrinfo hints{0, AF_UNSPEC, SOCK_STREAM};
  addrinfo* result{};
  if (getaddrinfo(host_or_ipaddr.toStdString().c_str(), QString::number(port).toStdString().c_str(), &hints, &result)) {
    if (result) freeaddrinfo(result);
    return {};
  }
  return std::unique_ptr<addrinfo>(result);
}
}  // namespace

//--------------------------------------------------------------------------------------------------
// TelnetSocket
TelnetSocket::TelnetSocket(QObject* parent)
    : QSslSocket{parent}, host_{}, port_{0}, addrinfo_{}, hostaddr_{} {}

TelnetSocket::TelnetSocket(const QString& host_or_ipaddr, quint16 port, QObject* parent)
    : QSslSocket{parent},
      host_{host_or_ipaddr},
      port_{port},
      addrinfo_{hostPort2AddrInfo(host_or_ipaddr, port)},
      hostaddr_{addrinfo_ ? QHostAddress{addrinfo_->ai_addr} : QHostAddress{}} {
  if (!hostaddr_.isNull()) {
    connectToHost(hostaddr_, port);
    waitForConnected(kTimeoutConnected);
  }
}

void TelnetSocket::connect(const QString& host_or_ipaddr, quint16 port) {
  host_ = host_or_ipaddr;
  port_ = port;
  addrinfo_ = hostPort2AddrInfo(host_or_ipaddr, port);
  hostaddr_ = addrinfo_ ? QHostAddress{addrinfo_->ai_addr} : QHostAddress{};
  if (!hostaddr_.isNull()) {
    connectToHost(hostaddr_, port);
    waitForConnected(kTimeoutConnected);
  }
}

void TelnetSocket::connect(const QHostAddress& host_or_ipaddr, quint16 port) {
  connect(host_or_ipaddr.toString(), port);
}

QByteArray TelnetSocket::transceiveData(const QByteArray& data) {
  sendData(data);
  return receiveData();
}

void TelnetSocket::sendData(const QByteArray& data) {
  write(data);
  flush();
}

QByteArray TelnetSocket::receiveData() {
  waitForReadyRead();
  return readAll();
}

QString TelnetSocket::transceiveMessage(const QString& msg) {
  sendMessage(msg);
  return receiveMessage();
}

void TelnetSocket::sendMessage(const QString& msg) {
  write(msg.toStdString().c_str());
  flush();
}

QString TelnetSocket::receiveMessage() {
  waitForReadyRead();
  return QString::fromUtf8(readAll());
}

//--------------------------------------------------------------------------------------------------
// Socks4Socket
Socks4Socket::Socks4Socket(QObject* parent) : TelnetSocket{parent} {}
Socks4Socket::Socks4Socket(const QString& host_or_ipaddr, quint16 port, QObject* parent)
    : TelnetSocket{host_or_ipaddr, port, parent} {}

bool Socks4Socket::start(Command cmd, const QString& host_or_ipaddr, quint16 port, const QString& userid) {
  bool ret{false};
  std::unique_ptr<addrinfo> result = hostPort2AddrInfo(host_or_ipaddr, port);
  if (result) {
    ret = start(cmd, *result->ai_addr, userid);
  } else {
    ret = false;
  }
  return ret;
}

bool Socks4Socket::start(Command cmd, const sockaddr& ai_addr, const QString& userid) {
  if (addrInfo().ai_family != AF_INET || state() != Socks4Socket::ConnectedState) { return false; }  // SOCKS4はIPv4のみ対応
  auto sin = reinterpret_cast<const sockaddr_in*>(&ai_addr);
  // SOCKS4のプロトコル: https://ja.wikipedia.org/wiki/SOCKS#SOCKS_4
  QByteArray buffer{};
  buffer.append(4);
  buffer.append(static_cast<char>(cmd));
  buffer.append(reinterpret_cast<const char*>(&sin->sin_port), sizeof sin->sin_port);
  buffer.append(reinterpret_cast<const char*>(&sin->sin_addr), sizeof sin->sin_addr);
  const std::string uid{userid.toStdString()};
  buffer.append(uid.c_str(), uid.length() + 1);  // +1しているのは文字列終端のNULLも書き込むため
  const QByteArray responsd{transceiveData(buffer)};
  return responsd.size() == 8 && responsd[1] == 0x5a;
}

//--------------------------------------------------------------------------------------------------
// Socks5Socket
Socks5Socket::Socks5Socket(QObject* parent) : Socks4Socket{parent} {}
Socks5Socket::Socks5Socket(const QString& host_or_ipaddr, quint16 port, QObject* parent)
    : Socks4Socket{host_or_ipaddr, port, parent} {}

void Socks5Socket::start(Method method, const QString& socks5_host_or_ipaddr, quint16 port, const bool plz_resolve, const QString& username, const QString& password) {
  const QString username_{method == Method::NoAuthentication ? QString{} : username};
  const QString password_{method == Method::NoAuthentication ? QString{} : password};
  QNetworkProxy proxy{QNetworkProxy::Socks5Proxy, socks5_host_or_ipaddr, port, username_, password_};
  QNetworkProxy::Capabilities cap{
      plz_resolve
          ? proxy.capabilities() |  QNetworkProxy::HostNameLookupCapability
          : proxy.capabilities() & ~QNetworkProxy::HostNameLookupCapability};
  proxy.setCapabilities(cap);
  setProxy(proxy);
}

void Socks5Socket::start(Method method, const QHostAddress& socks5_host_or_ipaddr, quint16 port, const bool plz_resolve, const QString& username, const QString& password) {
  start(method, socks5_host_or_ipaddr.toString(), port, plz_resolve, username, password);
}

bool Socks5Socket::isSocks5Error() const {
  Socks5Socket::SocketError err{error()};
  return 
    err == Socks5Socket::ProxyAuthenticationRequiredError ||
    err == Socks5Socket::ProxyConnectionRefusedError ||
    err == Socks5Socket::ProxyConnectionClosedError ||
    err == Socks5Socket::ProxyConnectionTimeoutError ||
    err == Socks5Socket::ProxyNotFoundError ||
    err == Socks5Socket::ProxyProtocolError;
}

//--------------------------------------------------------------------------------------------------
// FtpSocket
FtpSocket::FtpSocket(QObject* parent) : Socks5Socket{parent} {}
FtpSocket::FtpSocket(const QString& host_or_ipaddr, quint16 port, QObject* parent)
    : Socks5Socket{host_or_ipaddr, port, parent} {}

QString FtpSocket::transceiveCommand(Command cmd, const QString& var) {
  QString ret{};
  switch (cmd) {
    case HELP:
      ret = transceiveMessage("HELP\r\n");
      break;
  }
  return ret;
}
