#include "hostsettingspecialform.hpp"

#include "ui_hostsettingspecialform.h"

namespace {
using ThisData = HostSettingSpecialForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingSpecialForm::Private {
 public:
  Private();
  ~Private();
  Ui::HostSettingSpecialForm ui;
};
HostSettingSpecialForm::Private::Private() {}
HostSettingSpecialForm::Private::~Private() {}

HostSettingSpecialForm::Data::Data()
    : list_cmd_only(false),
      use_mlsd(false),
      use_nlst_r(false),
      no_fullpath(false),
      chmod_cmd(),
      host_type(0),
      ls_name() {}

HostSettingSpecialForm::Data::Data(bool list_cmd_only, bool use_mlsd,
                                   bool use_nlst_r, bool no_fullpath,
                                   const std::wstring& chmod_cmd, int host_type,
                                   const std::wstring& ls_name)
    : list_cmd_only(list_cmd_only),
      use_mlsd(use_mlsd),
      use_nlst_r(use_nlst_r),
      no_fullpath(no_fullpath),
      chmod_cmd(chmod_cmd),
      host_type(host_type),
      ls_name(ls_name) {}

HostSettingSpecialForm::HostSettingSpecialForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
HostSettingSpecialForm ::~HostSettingSpecialForm() { delete d_; }

void HostSettingSpecialForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void HostSettingSpecialForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  // TODO: UIへの入出力
  // TODO: UIの挙動
}

void HostSettingSpecialForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
}
