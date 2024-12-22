#define NOMINMAX
#define SECURITY_WIN32
#define WIN32_LEAN_AND_MEAN
#define UMDF_USING_NTSTATUS

#include "libffftp_windows.hpp"

#include "common.h"

#include "ffftp_common.h"
#include "libffftp_common.hpp"

namespace LIBFFFTP_WINDOWS {

#define SHOWMESSAGEBOX_CALLPROC(P1, P2, P3, P4) static_cast<int>(ffftp_proc(SHOW_MESSAGEBOX, { const_cast<void*>(reinterpret_cast<const void*>(P1)), const_cast<void*>(reinterpret_cast<const void*>(P2)), const_cast<void*>(reinterpret_cast<const void*>(P3)), const_cast<void*>(reinterpret_cast<const void*>(P4)) }))
#define SHOWDIALOGBOX_CALLPROC(P1, P2, P3, P4) static_cast<INT_PTR>(ffftp_proc(SHOW_DIALOGBOX, { reinterpret_cast<void*>(P1), reinterpret_cast<void*>(P2), reinterpret_cast<void*>(P3), reinterpret_cast<void*>(P4) }))

int MessageBoxIndirectW(const MSGBOXPARAMSW *lpmbp) {
  return SHOWMESSAGEBOX_CALLPROC(lpmbp->lpszText, lpmbp->lpszCaption, NULL, NULL);
}

template <unsigned long long>
INT_PTR Dialog(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<about_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<account_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<bmark_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<bmark_edit_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<certerr_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<chdir_br_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<chdir_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<chmod_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<corruptsettings_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<cwderr_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<def_attr_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<delete_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<diskfull_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<down_exist_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<downerr_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<downname_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<exit_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<filesize_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<filesize_notify_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<filter_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<find_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<fname_in_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<forcepasschange_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<forcerename_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<group_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<groupdel_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<hostconnect_dlg>(unsigned long long dialogid, LPARAM dwInitParam) {
  return SHOWDIALOGBOX_CALLPROC(dialogid, NULL, NULL, NULL);
}
template <> INT_PTR Dialog<hostdel_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<hostlist_dlg>(unsigned long long dialogid, LPARAM dwInitParam) {
  return SHOWDIALOGBOX_CALLPROC(dialogid, NULL, NULL, NULL);
}
template <> INT_PTR Dialog<hostname_dlg>(unsigned long long dialogid, LPARAM dwInitParam) {
  struct QuickCon {
    std::wstring hostname;
    std::wstring username;
    std::wstring password;
    bool firewall;
    bool passive;
  };
  QuickCon* in_out_param = reinterpret_cast<QuickCon*>(dwInitParam);
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
  const INT_PTR ret{SHOWDIALOGBOX_CALLPROC(dialogid, &in_param, &out_param, NULL)};
  if (ret) {
    in_out_param->hostname = out_param.hostname;
    in_out_param->username = out_param.username;
    in_out_param->password = out_param.password;
    in_out_param->firewall = out_param.use_firewall;
    in_out_param->passive  = out_param.use_passive;
  }
  return ret;
}
template <> INT_PTR Dialog<hset_adv_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<hset_adv2_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<hset_adv3_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<hset_code_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<hset_crypt_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<hset_dialup_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<hset_main_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<ini_from_reg_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<masterpasswd_dlg>(unsigned long long dialogid, LPARAM dwInitParam) {
  struct Data {
    UINT _;
    std::wstring& text;
  };
  Data* p = reinterpret_cast<Data*>(dwInitParam);
  return SHOWDIALOGBOX_CALLPROC(dialogid, &p->text, NULL, NULL);
}
template <> INT_PTR Dialog<mirror_down_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<mirror_notify_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<mirror_up_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<mirrordown_notify_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<mkdir_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<move_notify_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<newmasterpasswd_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<noresume_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<opt_connect_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<opt_disp1_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<opt_disp2_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<opt_fire_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<opt_mirror_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<opt_misc_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<opt_notify_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<opt_tool_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<opt_trmode1_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<opt_trmode2_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<opt_trmode3_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<opt_trmode4_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<opt_user_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<otp_calc_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<otp_notify_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<passwd_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<rasnotify_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<rasreconnect_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<re_passwd_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<reginit_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<rename_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<savecrypt_dlg>(unsigned long long dialogid, LPARAM dwInitParam) {
  // TODO: たぶん特殊化不要
    return SHOWDIALOGBOX_CALLPROC(dialogid, NULL, NULL, NULL);
}
template <> INT_PTR Dialog<savepass_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<sel_local_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<sel_remote_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<somecmd_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<sort_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<transfer_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<up_exist_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<updatesslroot_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<updown_as_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<updown_as_with_ext_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<uperr_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }
template <> INT_PTR Dialog<username_dlg>(unsigned long long dialogid, LPARAM dwInitParam) { return -1; }

INT_PTR DialogBoxParamW(HINSTANCE hInstance, LPCWSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam) {
  INT_PTR ret{-1};
  const unsigned long long dialogid = reinterpret_cast<const unsigned long long>(lpTemplateName);
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
    ret = Dialog<hostconnect_dlg>(dialogid, dwInitParam);
    break;
  case hostdel_dlg: break;
  case hostlist_dlg:
    ret = Dialog<hostlist_dlg>(dialogid, dwInitParam);
    break;
  case hostname_dlg:
    ret = Dialog<hostname_dlg>(dialogid, dwInitParam);
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
    ret = Dialog<masterpasswd_dlg>(dialogid, dwInitParam);
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
    ret = Dialog<savecrypt_dlg>(dialogid, dwInitParam);
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

}  // namespace LIBFFFTP_WINDOWS
