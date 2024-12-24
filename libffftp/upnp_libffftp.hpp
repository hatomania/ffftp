#include <miniupnpc/miniupnpc.h>
#include <miniupnpc/upnpcommands.h>

// TODO: 今のところWin32 APIの使用を含んでいます。

namespace {
UPNPDev* upnp_devlist{nullptr};
UPNPDev* upnp_device{nullptr};
UPNPUrls upnp_urls{};
IGDdatas upnp_data{};
int upnp_igd{-1};
constexpr const char* const kUpnpDesc  = "FFFTP active mode";
constexpr const char* const kUpnpProto = "TCP";

const wchar_t* convchar(const char* str) {
  const size_t wsize = mblen(str, MB_CUR_MAX) * (strlen(str) + 1);
  static wchar_t* wstr{nullptr};
  delete[] wstr;
  wstr = new wchar_t[wsize];
  size_t ret;
  mbstowcs_s(&ret, wstr, wsize, str, _TRUNCATE);
  return wstr;
}

const char* convchar(const wchar_t* wstr) {
  const size_t wsize = wcslen(wstr) + 1;
  static char* str{nullptr};
  delete[] str;
  str = new char[wsize];
  size_t ret;
  wcstombs_s(&ret, str, wsize, wstr, _TRUNCATE);
  return str;
}
}  // namespace


int LoadUPnP() {
  int ret{FFFTP_FAIL};
#ifdef _WINDOWS
  WSAData wsadata{};
  if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
    return FFFTP_FAIL;
  }
#endif // _WINDOWS
  if (IsMainThread()) {
    if (int err; upnp_devlist = upnpDiscover(2000, NULL, NULL, UPNP_LOCAL_PORT_ANY, 0, 2, &err)) {
      // デバイスが複数見つかった場合でも一番最初に見つかったデバイスを使用する（走査を行わない）
      upnp_device = upnp_devlist;

      char lanaddr[64];
      char wanaddr[64];
      upnp_igd = UPNP_GetValidIGD(upnp_device, &upnp_urls, &upnp_data, lanaddr, sizeof(lanaddr), wanaddr, sizeof(wanaddr));
      if (upnp_igd == 0) {
        // IGDが見つからない。見つからないこと自体はエラーではない。単にルーター等がUPnPによるポートマッピング機能を搭載していないだけである。
        // これをどう解釈するかはFFFTPの仕様による。現状はFFFTP_SUCCESSを返し、しかしポートマッピング機能は機能しない状態とする。
        ret = FFFTP_SUCCESS;
      }
      ret = FFFTP_SUCCESS;
    } else {
        // UPnP対応デバイスが見つからない。見つからないこと自体はエラーではない。単にルーター等がUPnP機能を搭載していないだけである。
        // これをどう解釈するかはFFFTPの仕様による。現状はFFFTP_SUCCESSを返し、しかしポートマッピング機能は機能しない状態とする。
      ret = FFFTP_SUCCESS;
    }
  }
  return ret;
}

void FreeUPnP() {
  if (IsMainThread()) {
    FreeUPNPUrls(&upnp_urls);
    freeUPNPDevlist(upnp_devlist);
  }
}

int IsUPnPLoaded() noexcept {
  return upnp_igd > 0 ? YES : NO;
}

std::optional<std::wstring> AddPortMapping(std::wstring const& internalAddress, int port) {
  if (!IsUPnPLoaded()) return {};
  struct Data : public MainThreadRunner {
    long port;
    std::wstring const& internalAddress;
    char externalAddress[64]{};
    Data(std::wstring const& internalAddress, long port) noexcept : port{port}, internalAddress{internalAddress} {}
    int DoWork() override {
      int result = UPNP_AddPortMapping(upnp_urls.controlURL, upnp_data.first.servicetype, std::to_string(port).c_str(), std::to_string(port).c_str(), convchar(internalAddress.c_str()), kUpnpDesc, kUpnpProto, nullptr, nullptr);
      if (result == 0)
        result = UPNP_GetExternalIPAddress(upnp_urls.controlURL, upnp_data.first.servicetype, externalAddress);
      return result;
    }
  } data{internalAddress, port};
  if (auto const result = (HRESULT)data.Run(); result == S_OK)
    return { convchar(data.externalAddress) };
  return {};
}

bool RemovePortMapping(int port) {
  struct Data : public MainThreadRunner {
    long port;
    Data(long port) noexcept : port{port} {}
    int DoWork() override {
      return UPNP_DeletePortMapping(upnp_urls.controlURL, upnp_data.first.servicetype, std::to_string(port).c_str(), kUpnpProto, nullptr);
    }
  } data{port};
  const auto result = (HRESULT)data.Run();
  return result == 0;
}
