#ifndef FFFTPGUI_UI_HOST_ADVANCEDDATATRANSCEIVER_HPP_
#define FFFTPGUI_UI_HOST_ADVANCEDDATATRANSCEIVER_HPP_

#include "ffftp_hostdata.h"
#include "ui/base/formdatatransceiver.hpp"
#include "hostsettingadvancedform.hpp"

DATATRANSCEIVER_BEGIN(HostSettingAdvancedForm)
DATATRANSCEIVER_SEND(hdata_in) {
  const hostdata& hdata = *static_cast<const hostdata*>(hdata_in);
  ThisData form_data{
      hdata.advanced.firewall, hdata.advanced.pasv,    hdata.advanced.syncmove,
      hdata.advanced.port,     hdata.advanced.account, hdata.advanced.timezone,
      hdata.advanced.security, hdata.advanced.initcmd,
  };
  form().setData(form_data);
}
DATATRANSCEIVER_RECEIVE(hdata_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  hostdata& hdata = *static_cast<hostdata*>(hdata_out);
  hdata.advanced = {
      .firewall = form_data.firewall,
      .pasv = form_data.pasv,
      .syncmove = form_data.syncmove,
      .port = form_data.port,
      .account = form_data.account.c_str(),
      .timezone = form_data.timezone,
      .security = form_data.security,
      .initcmd = form_data.initcmd.c_str(),
  };
}
DATATRANSCEIVER_END()

#endif  // FFFTPGUI_UI_HOST_ADVANCEDDATATRANSCEIVER_HPP_
