#include "transfer4datatransceiver.hpp"

#include "ffftp_option.h"

IMPL_DATATRANSCEIVER_BEGIN(OptionTransfer4Form);

IMPL_DATATRANSCEIVER_SEND(option_in) {
  const ffftp_option& opt = *static_cast<const ffftp_option*>(option_in);
  ThisData form_data{
    opt.transfer4.local_kanjicode == modes::SJIS    ? Form::Codes::kSJIS    :
    opt.transfer4.local_kanjicode == modes::JIS     ? Form::Codes::kJIS     :
    opt.transfer4.local_kanjicode == modes::EUC     ? Form::Codes::kEUC     :
    opt.transfer4.local_kanjicode == modes::UTF8N   ? Form::Codes::kUTF8N   :
    opt.transfer4.local_kanjicode == modes::UTF8BOM ? Form::Codes::kUTF8BOM : Form::Codes::kSJIS,
    opt.transfer4.mark_as_internet,
  };
  form().setData(form_data);
}

IMPL_DATATRANSCEIVER_RECEIVE(option_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  ffftp_option& opt = *static_cast<ffftp_option*>(option_out);
  opt.transfer4 = {
    .local_kanjicode =
      form_data.local_kanjicode == Form::Codes::kSJIS    ? modes::SJIS    :
      form_data.local_kanjicode == Form::Codes::kJIS     ? modes::JIS     :
      form_data.local_kanjicode == Form::Codes::kEUC     ? modes::EUC     :
      form_data.local_kanjicode == Form::Codes::kUTF8N   ? modes::UTF8N   :
      form_data.local_kanjicode == Form::Codes::kUTF8BOM ? modes::UTF8BOM : modes::SJIS,
    .mark_as_internet = form_data.mark_as_internet,
  };
}

IMPL_DATATRANSCEIVER_END(OptionTransfer4Form);
