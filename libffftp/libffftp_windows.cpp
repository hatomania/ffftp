#define NOMINMAX
#define SECURITY_WIN32
#define WIN32_LEAN_AND_MEAN
#define UMDF_USING_NTSTATUS

#include "libffftp_windows.hpp"

#include <QCoreApplication>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QString>

#include "common.h"

#include "ffftp_common.h"
#include "libffftp_common.hpp"

namespace LIBFFFTP_WINDOWS {

#define MAKEPARAM(P1, P2, P3, P4) ffftp_procparam _param{ const_cast<void*>(reinterpret_cast<const void*>(P1)), const_cast<void*>(reinterpret_cast<const void*>(P2)), const_cast<void*>(reinterpret_cast<const void*>(P3)), const_cast<void*>(reinterpret_cast<const void*>(P4)) }
#define SHOWMESSAGEBOX_CALLPROC() static_cast<int>(ffftp_proc(SHOW_MESSAGEBOX, &_param));
#define SHOWDIALOGBOX_CALLPROC() static_cast<int>(ffftp_proc(SHOW_DIALOGBOX, &_param))

int messageBox(int textId, int captionId) {
  MAKEPARAM(textId, captionId, NULL, NULL);
  return SHOWMESSAGEBOX_CALLPROC();
}

template <int>
int Dialog(int dialogid, void* param) { return -1; }
template <> int Dialog<about_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<account_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<bmark_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<bmark_edit_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<certerr_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<chdir_br_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<chdir_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<chmod_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<corruptsettings_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<cwderr_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<def_attr_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<delete_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<diskfull_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<down_exist_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<downerr_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<downname_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<exit_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<filesize_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<filesize_notify_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<filter_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<find_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<fname_in_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<forcepasschange_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<forcerename_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<group_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<groupdel_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<hostconnect_dlg>(int dialogid, void* param) {
  MAKEPARAM(dialogid, NULL, NULL, NULL);
  return SHOWDIALOGBOX_CALLPROC();
}
template <> int Dialog<hostdel_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<hostlist_dlg>(int dialogid, void* param) {
  MAKEPARAM(dialogid, NULL, NULL, NULL);
  return SHOWDIALOGBOX_CALLPROC();
}
template <> int Dialog<hostname_dlg>(int dialogid, void* param) {
  struct QuickCon {
    std::wstring hostname;
    std::wstring username;
    std::wstring password;
    bool firewall;
    bool passive;
  };
  QuickCon* in_out_param = reinterpret_cast<QuickCon*>(param);
  in_out_param->hostname = L"";
  if (QuickAnonymous == YES) {
    in_out_param->username = L"anonymous";
    in_out_param->password = UserMailAdrs;
  } else {
    in_out_param->username = L"";
    in_out_param->password = L"";
  }
  in_out_param->firewall = FwallDefault == YES;
  in_out_param->passive  = PasvDefault  == YES;
  ffftp_procparam_quickconnect in_param;
  const std::vector<HISTORYDATA>& hist = GetHistories();
  assert(hist.size() < 20);
  for (int i = 0; const auto& hdata: hist) {
    in_param.history[i++] = hdata.HostAdrs.c_str();
  }
  in_param.history_cnt   = hist.size();
  in_param.username      = in_out_param->username.c_str();
  in_param.password      = in_out_param->password.c_str();
  in_param.use_firewall  = in_out_param->firewall;
  in_param.use_passive   = in_out_param->passive;
  ffftp_procparam_quickconnect out_param;
  MAKEPARAM(dialogid, &in_param, &out_param, NULL);
  const int ret{SHOWDIALOGBOX_CALLPROC()};
  if (ret) {
    in_out_param->hostname = out_param.hostname;
    in_out_param->username = out_param.username;
    in_out_param->password = out_param.password;
    in_out_param->firewall = out_param.use_firewall;
    in_out_param->passive  = out_param.use_passive;
  }
  return ret;
}
template <> int Dialog<hset_adv_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<hset_adv2_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<hset_adv3_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<hset_code_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<hset_crypt_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<hset_dialup_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<hset_main_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<ini_from_reg_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<masterpasswd_dlg>(int dialogid, void* param) {
  struct Data {
    UINT _;
    std::wstring& text;
  };
  Data* p = reinterpret_cast<Data*>(param);
  MAKEPARAM(dialogid, &p->text, NULL, NULL);
  return SHOWDIALOGBOX_CALLPROC();
}
template <> int Dialog<mirror_down_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<mirror_notify_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<mirror_up_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<mirrordown_notify_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<mkdir_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<move_notify_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<newmasterpasswd_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<noresume_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<opt_connect_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<opt_disp1_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<opt_disp2_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<opt_fire_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<opt_mirror_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<opt_misc_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<opt_notify_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<opt_tool_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<opt_trmode1_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<opt_trmode2_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<opt_trmode3_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<opt_trmode4_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<opt_user_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<otp_calc_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<otp_notify_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<passwd_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<rasnotify_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<rasreconnect_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<re_passwd_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<reginit_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<rename_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<savecrypt_dlg>(int dialogid, void* param) {
  // TODO: たぶん特殊化不要
  MAKEPARAM(dialogid, NULL, NULL, NULL);
    return SHOWDIALOGBOX_CALLPROC();
}
template <> int Dialog<savepass_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<sel_local_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<sel_remote_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<somecmd_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<sort_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<transfer_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<up_exist_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<updatesslroot_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<updown_as_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<updown_as_with_ext_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<uperr_dlg>(int dialogid, void* param) { return -1; }
template <> int Dialog<username_dlg>(int dialogid, void* param) { return -1; }

int dialogBox(int dialogid, void* param) {
  int ret{-1};
  switch (dialogid) {
  case about_dlg: break;
  case account_dlg: break;
  case bmark_dlg: break;
  case bmark_edit_dlg: break;
  case certerr_dlg: break;
  case chdir_br_dlg: break;
  case chdir_dlg: break;
  case chmod_dlg: break;
  case corruptsettings_dlg: break;
  case cwderr_dlg: break;
  case def_attr_dlg: break;
  case delete_dlg: break;
  case diskfull_dlg: break;
  case down_exist_dlg: break;
  case downerr_dlg: break;
  case downname_dlg: break;
  case exit_dlg: break;
  case filesize_dlg: break;
  case filesize_notify_dlg: break;
  case filter_dlg: break;
  case find_dlg: break;
  case fname_in_dlg: break;
  case forcepasschange_dlg: break;
  case forcerename_dlg: break;
  case group_dlg: break;
  case groupdel_dlg: break;
  case hostconnect_dlg:
    ret = Dialog<hostconnect_dlg>(dialogid, param);
    break;
  case hostdel_dlg: break;
  case hostlist_dlg:
    ret = Dialog<hostlist_dlg>(dialogid, param);
    break;
  case hostname_dlg:
    ret = Dialog<hostname_dlg>(dialogid, param);
    break;
  case hset_adv_dlg: break;
  case hset_adv2_dlg: break;
  case hset_adv3_dlg: break;
  case hset_code_dlg: break;
  case hset_crypt_dlg: break;
  case hset_dialup_dlg: break;
  case hset_main_dlg: break;
  case ini_from_reg_dlg: break;
  case masterpasswd_dlg:
    ret = Dialog<masterpasswd_dlg>(dialogid, param);
    break;
  case mirror_down_dlg: break;
  case mirror_notify_dlg: break;
  case mirror_up_dlg: break;
  case mirrordown_notify_dlg: break;
  case mkdir_dlg: break;
  case move_notify_dlg: break;
  case newmasterpasswd_dlg: break;
  case noresume_dlg: break;
  case opt_connect_dlg: break;
  case opt_disp1_dlg: break;
  case opt_disp2_dlg: break;
  case opt_fire_dlg: break;
  case opt_mirror_dlg: break;
  case opt_misc_dlg: break;
  case opt_notify_dlg: break;
  case opt_tool_dlg: break;
  case opt_trmode1_dlg: break;
  case opt_trmode2_dlg: break;
  case opt_trmode3_dlg: break;
  case opt_trmode4_dlg: break;
  case opt_user_dlg: break;
  case otp_calc_dlg: break;
  case otp_notify_dlg: break;
  case passwd_dlg: break;
  case rasnotify_dlg: break;
  case rasreconnect_dlg: break;
  case re_passwd_dlg: break;
  case reginit_dlg: break;
  case rename_dlg: break;
  case savecrypt_dlg:
    ret = Dialog<savecrypt_dlg>(dialogid, param);
    break;
  case savepass_dlg: break;
  case sel_local_dlg: break;
  case sel_remote_dlg: break;
  case somecmd_dlg: break;
  case sort_dlg: break;
  case transfer_dlg: break;
  case up_exist_dlg: break;
  case updatesslroot_dlg: break;
  case updown_as_dlg: break;
  case updown_as_with_ext_dlg: break;
  case uperr_dlg: break;
  case username_dlg: break;
  default: {
    const static bool unknown_dialog_id{false};
    assert(unknown_dialog_id);
  } break;
  }
  return ret;
}

BOOL SetWindowTextW(HWND hWnd, LPCWSTR lpString) {
  if (hWnd == GetMainHwnd()) {
    MAKEPARAM(lpString, NULL, NULL, NULL);
    ffftp_proc(ffftp_procmsg::SETWINDOWTITLE, &_param);
  }
  return TRUE;
}

void SetOption() {
  MAKEPARAM(ffftp_dialogid::OPTION_DLG, NULL, NULL, NULL);
  SHOWDIALOGBOX_CALLPROC();
}

INT WSAAddressToStringW(LPSOCKADDR lpsaAddress, DWORD dwAddressLength, LPWSAPROTOCOL_INFOW lpProtocolInfo, LPWSTR lpszAddressString, LPDWORD lpdwAddressStringLength) {
  // エラー処理は実装していません。常に0(=成功)を返します。lpszAddressStringは十分なバッファを確保しておいてください
  assert(lpsaAddress->sa_family == AF_INET || lpsaAddress->sa_family == AF_INET6);
  char ipstr[INET6_ADDRSTRLEN]{};
  uint16_t port{};
  switch (lpsaAddress->sa_family) {
    case AF_INET: {
      const sockaddr_in* sin = reinterpret_cast<decltype(sin)>(lpsaAddress);
      inet_ntop(AF_INET, &(sin->sin_addr), ipstr, sizeof ipstr);
      port = htons(sin->sin_port);
    } break;
    case AF_INET6: {
      const sockaddr_in6* sin6 = reinterpret_cast<decltype(sin6)>(lpsaAddress);
      inet_ntop(AF_INET6, &(sin6->sin6_addr), ipstr, sizeof ipstr);
      port = htons(sin6->sin6_port);
    } break;
  }
  std::wstring outaddr{QString(ipstr).toStdWString()};
  outaddr += L":" + std::to_wstring(port);
  wcscpy_s(lpszAddressString, *lpdwAddressStringLength, outaddr.c_str());
  *lpdwAddressStringLength = static_cast<DWORD>(outaddr.length() + 1);
  return 0;
}

class SoundPlayer {
public:
  enum class Type {
    Connected,
    Transferred,
    Error,
  };
  inline explicit SoundPlayer()
      : player_{std::make_unique<QMediaPlayer>()},
        audioo_{std::make_unique<QAudioOutput>()},
        urls_{
          {Type::Connected,   QUrl::fromLocalFile("C:/Users/takayuki/AppData/Local/Programs/Microsoft VS Code/resources/app/out/vs/platform/accessibilitySignal/browser/media/success.mp3")},
          {Type::Transferred, QUrl::fromLocalFile("C:/Users/takayuki/AppData/Local/Programs/Microsoft VS Code/resources/app/out/vs/platform/accessibilitySignal/browser/media/quickFixes.mp3")},
          {Type::Error,       QUrl::fromLocalFile("C:/Users/takayuki/AppData/Local/Programs/Microsoft VS Code/resources/app/out/vs/platform/accessibilitySignal/browser/media/foldedAreas.mp3")}, } {
    player_->setAudioOutput(audioo_.get());
  };
  inline void play(const Type playtype) {
    player_->setSource(urls_.value(playtype));
  }
private:
  std::unique_ptr<QMediaPlayer> player_;
  std::unique_ptr<QAudioOutput> audioo_;
  const QMap<Type, QUrl> urls_;
};
BOOL PlaySoundW(LPCWSTR pszSound, HMODULE hmod, DWORD fdwSound) {
  static SoundPlayer player{};
  QMap<QString, SoundPlayer::Type> sm{
    {"FFFTP_Connected",   SoundPlayer::Type::Connected},
    {"FFFTP_Transferred", SoundPlayer::Type::Transferred},
    {"FFFTP_Error",       SoundPlayer::Type::Error},
  };
  player.play(sm.value(QString(pszSound)));
  return TRUE;
}

HMODULE GetModuleHandleW(LPCWSTR lpModuleName) {
  return NULL;
}

DWORD GetCurrentThreadId() {
  return static_cast<DWORD>(QCoreApplication::applicationPid());
}

HRESULT OleInitialize(LPVOID pvReserved) {
  return S_OK;
}

}  // namespace LIBFFFTP_WINDOWS
