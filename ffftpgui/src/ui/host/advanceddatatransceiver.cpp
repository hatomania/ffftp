#include "advanceddatatransceiver.hpp"

#include "ffftp_hostdata.h"

IMPL_DATATRANSCEIVER_BEGIN(HostSettingAdvancedForm);

IMPL_DATATRANSCEIVER_SEND(hdata_in) {
  const ffftp_hostdata& hdata = *static_cast<const ffftp_hostdata*>(hdata_in);
  ThisData form_data{
      hdata.advanced.firewall, hdata.advanced.pasv,    hdata.advanced.syncmove,
      hdata.advanced.port,     hdata.advanced.account, hdata.advanced.timezone,
      hdata.advanced.security, hdata.advanced.initcmd,
  };
  form().setData(form_data);
}

IMPL_DATATRANSCEIVER_RECEIVE(hdata_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  ffftp_hostdata& hdata = *static_cast<ffftp_hostdata*>(hdata_out);
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

IMPL_DATATRANSCEIVER_END(HostSettingAdvancedForm);
