#include "transfer1datatransceiver.hpp"

#include "ffftp_option.h"

IMPL_DATATRANSCEIVER_BEGIN(OptionTransfer1Form);

IMPL_DATATRANSCEIVER_SEND(option_in) {
  const ffftp_option& opt = *static_cast<const ffftp_option*>(option_in);
  static const std::map<modes, OptionTransfer1Form::Modes> modes_table{
      { modes::AUTO,   OptionTransfer1Form::Modes::kAuto   },
      { modes::ASCII,  OptionTransfer1Form::Modes::kASCII  },
      { modes::BINARY, OptionTransfer1Form::Modes::kBinary },
  };
  ThisData form_data{
      modes_table.at(static_cast<modes>(opt.transfer1.trans_mode)),
      [&opt]() {
        std::vector<std::wstring> ret{};
        ret.reserve(opt.transfer1.ascii_ext_cnt);
        for (int i = 0; i < opt.transfer1.ascii_ext_cnt; ++i) {
          ret.push_back(opt.transfer1.ascii_ext[i]);
        }
        return ret;
      }(),
      opt.transfer1.rm_eof,
      opt.transfer1.save_timestamp,
      opt.transfer1.vax_semicolon,
      opt.transfer1.make_all_dir,
      opt.transfer1.abort_on_list_error,
  };
  form().setData(form_data);
}

IMPL_DATATRANSCEIVER_RECEIVE(option_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  ffftp_option& opt = *static_cast<ffftp_option*>(option_out);
  static const std::map<OptionTransfer1Form::Modes, modes> modes_table{
      { OptionTransfer1Form::Modes::kAuto,   modes::AUTO   },
      { OptionTransfer1Form::Modes::kASCII,  modes::ASCII  },
      { OptionTransfer1Form::Modes::kBinary, modes::BINARY },
  };
  opt.transfer1 = {
      .trans_mode = modes_table.at(form_data.trans_mode),
      .rm_eof = form_data.rm_eof,
      .save_timestamp = form_data.save_timestamp,
      .vax_semicolon = form_data.vax_semicolon,
      .make_all_dir = form_data.make_all_dir,
      .abort_on_list_error = form_data.abort_on_list_error,
  };
  delete[] opt.transfer1.ascii_ext;
  opt.transfer1.ascii_ext = new const wchar_t*[form_data.ascii_ext.size()];
  for (int i = 0; const auto& str : form_data.ascii_ext) {
    opt.transfer1.ascii_ext[i++] = str.c_str();
  }
  opt.transfer1.ascii_ext_cnt = form_data.ascii_ext.size();
}

IMPL_DATATRANSCEIVER_END(OptionTransfer1Form);
