#include "mirroringdatatransceiver.hpp"

#include "ffftp_option.h"

IMPL_DATATRANSCEIVER_BEGIN(OptionMirroringForm);

IMPL_DATATRANSCEIVER_SEND(option_in) {
  const ffftp_option& opt = *static_cast<const ffftp_option*>(option_in);
  ThisData form_data{
    wchar2VectorWstr(opt.mirroring.no_trn, opt.mirroring.no_trn_cnt),
    wchar2VectorWstr(opt.mirroring.no_del, opt.mirroring.no_del_cnt),
    opt.mirroring.fname_cnv,
    opt.mirroring.up_del_notify,
    opt.mirroring.down_del_notify,
    opt.mirroring.no_transfer_contents,
  };
  form().setData(form_data);
}

IMPL_DATATRANSCEIVER_RECEIVE(option_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  ffftp_option& opt = *static_cast<ffftp_option*>(option_out);
  vectorWstr2Wchar(opt.mirroring.no_trn, opt.mirroring.no_trn_cnt, form_data.no_trn);
  vectorWstr2Wchar(opt.mirroring.no_del, opt.mirroring.no_del_cnt, form_data.no_del);
  opt.mirroring.fname_cnv = form_data.fname_cnv;
  opt.mirroring.up_del_notify = form_data.up_del_notify;
  opt.mirroring.down_del_notify = form_data.down_del_notify;
  opt.mirroring.no_transfer_contents = form_data.no_transfer_contents;
}

IMPL_DATATRANSCEIVER_END(OptionMirroringForm);
