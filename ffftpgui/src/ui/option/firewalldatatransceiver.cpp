#include "firewalldatatransceiver.hpp"

#include "ffftp_option.h"

IMPL_DATATRANSCEIVER_BEGIN(OptionFirewallForm);

IMPL_DATATRANSCEIVER_SEND(option_in) {
  const ffftp_option& opt = *static_cast<const ffftp_option*>(option_in);
  ThisData form_data{
      opt.firewall.type,
      opt.firewall.host,
      opt.firewall.port,
      opt.firewall.username,
      opt.firewall.password,
      opt.firewall.delimiter,
      opt.firewall.security,
      opt.firewall.resolve,
      opt.firewall.lower,
      opt.firewall.fwall_default,
      opt.firewall.pasv_default,
      opt.firewall.no_save_user,
  };
  form().setData(form_data);
}

IMPL_DATATRANSCEIVER_RECEIVE(option_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  ffftp_option& opt = *static_cast<ffftp_option*>(option_out);
  opt.firewall = {
      .type = form_data.type,
      .host = form_data.host.c_str(),
      .port = form_data.port,
      .username = form_data.username.c_str(),
      .password = form_data.password.c_str(),
      .delimiter = form_data.delimiter,
      .security = form_data.security,
      .resolve = form_data.resolve,
      .lower = form_data.lower,
      .fwall_default = form_data.fwall_default,
      .pasv_default = form_data.pasv_default,
      .no_save_user = form_data.no_save_user,
  };
}

IMPL_DATATRANSCEIVER_END(OptionFirewallForm);
