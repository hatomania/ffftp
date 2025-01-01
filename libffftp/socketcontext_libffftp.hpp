#include "sockets.hpp"

template<class T>
constexpr T CreateInvalidateHandle() {
	T handle;
	SecInvalidateHandle(&handle);
	return handle;
}

//struct SocketContext : public WSAOVERLAPPED {
//	static inline int recvlen = 8192;
//	SOCKET const handle;
//	std::wstring const originalTarget;
//	std::wstring const punyTarget;
//	int mapPort = 0;
//	std::variant<sockaddr_storage, std::tuple<std::wstring, int>> target;
//	CtxtHandle sslContext = CreateInvalidateHandle<CtxtHandle>();
//	bool sslSecure = false;
//	SecPkgContext_StreamSizes sslStreamSizes = {};
//	std::vector<char> readRaw;
//	std::vector<char> readPlain;
//	bool sslNeedRenegotiate = false;
//	SECURITY_STATUS sslReadStatus = SEC_E_OK;
//	int recvStatus = 0;
//	ULONG readRawSize = 0;
//
//	inline SocketContext(SOCKET s, std::wstring originalTarget, std::wstring punyTarget);
//	SocketContext(SocketContext const&) = delete;
//	inline ~SocketContext();
//	static std::shared_ptr<SocketContext> Create(int af, std::variant<std::wstring_view, std::reference_wrapper<const SocketContext>> originalTarget);
//	std::shared_ptr<SocketContext> Accept(_Out_writes_bytes_opt_(*addrlen) struct sockaddr* addr, _Inout_opt_ int* addrlen);
//	BOOL AttachSSL(BOOL* pbAborted);
//	constexpr bool IsSSLAttached() {
//		return SecIsValidHandle(&sslContext);
//	}
//	std::vector<char> Encrypt(std::string_view plain);
//	int Connect(const sockaddr* name, int namelen, int* CancelCheckWork);
//	int Listen(int backlog);
//	void OnComplete(DWORD error, DWORD transferred, DWORD flags);
//	int AsyncFetch();
//	int GetReadStatus() noexcept;
//	std::tuple<int, std::wstring> ReadReply(int* CancelCheckWork);
//	bool ReadSpan(std::span<char>& span, int* CancelCheckWork);
//	template<class Data>
//	bool ReadData(Data& data, int* CancelCheckWork) {
//		std::span span{ reinterpret_cast<char*>(&data), sizeof data };
//		return ReadSpan(span, CancelCheckWork);
//	}
//	int ReadAll(int* CancelCheckWork, std::function<bool(std::vector<char> const&)> callback);
//	void ClearReadBuffer() noexcept;
//	int Send(const char* buf, int len, int flags, int* CancelCheckWork);
//};
struct SocketContext : public WSAOVERLAPPED {
	static inline int recvlen = 8192;
  SOCKET const handle{};
  std::unique_ptr<FtpSocket> socket;
	std::wstring const originalTarget;
	std::wstring const punyTarget;
	int mapPort = 0;
	std::variant<sockaddr_storage, std::tuple<std::wstring, int>> target;
	CtxtHandle sslContext = CreateInvalidateHandle<CtxtHandle>();
	bool sslSecure = false;
	SecPkgContext_StreamSizes sslStreamSizes = {};
	std::vector<char> readRaw;
	std::vector<char> readPlain;
	bool sslNeedRenegotiate = false;
	SECURITY_STATUS sslReadStatus = SEC_E_OK;
	int recvStatus = 0;
	ULONG readRawSize = 0;

	inline SocketContext(std::unique_ptr<FtpSocket> s, std::wstring originalTarget, std::wstring punyTarget);
	SocketContext(SocketContext const&) = delete;
	inline ~SocketContext();
	static std::shared_ptr<SocketContext> Create(std::variant<std::wstring_view, std::reference_wrapper<const SocketContext>> originalTarget);
	std::shared_ptr<SocketContext> Accept(_Out_writes_bytes_opt_(*addrlen) struct sockaddr* addr, _Inout_opt_ int* addrlen);
	BOOL AttachSSL(BOOL* pbAborted);
	constexpr bool IsSSLAttached() {
		return SecIsValidHandle(&sslContext);
	}
	std::vector<char> Encrypt(std::string_view plain);
	int Connect(const sockaddr* name, int namelen, int Fwall, int* CancelCheckWork);
	int Listen(int backlog);
	void OnComplete(DWORD error, DWORD transferred, DWORD flags);
	int AsyncFetch();
	int GetReadStatus() noexcept;
	std::tuple<int, std::wstring> ReadReply(int* CancelCheckWork);
	bool ReadSpan(std::span<char>& span, int* CancelCheckWork);
	template<class Data>
	bool ReadData(Data& data, int* CancelCheckWork) {
		std::span span{ reinterpret_cast<char*>(&data), sizeof data };
		return ReadSpan(span, CancelCheckWork);
	}
	int ReadAll(int* CancelCheckWork, std::function<bool(std::vector<char> const&)> callback);
	void ClearReadBuffer() noexcept;
	int Send(const char* buf, int len, int flags, int* CancelCheckWork);
};
