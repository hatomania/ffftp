#include "hostsettingfeatureform.hpp"

#include "ui_hostsettingfeatureform.h"

#include"ui/uicommon.h"

namespace {
using ThisData = HostSettingFeatureForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingFeatureForm::Private {
 public:
  Private();
  ~Private();
  Ui::HostSettingFeatureForm ui;
};
HostSettingFeatureForm::Private::Private() {}
HostSettingFeatureForm::Private::~Private() {}

HostSettingFeatureForm::Data::Data()
    : max_thread_cnt(0),
      reuse_cmdsocket(false),
      no_pasv_adrs(false),
      noop_interval(0),
      error_mode(0),
      reconnect(false) {}

HostSettingFeatureForm::Data::Data(int max_thread_cnt, bool reuse_cmdsocket,
                                   bool no_pasv_adrs, int noop_interval,
                                   int error_mode, bool reconnect)
    : max_thread_cnt(max_thread_cnt),
      reuse_cmdsocket(reuse_cmdsocket),
      no_pasv_adrs(no_pasv_adrs),
      noop_interval(noop_interval),
      error_mode(error_mode),
      reconnect(reconnect) {}

HostSettingFeatureForm::HostSettingFeatureForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
HostSettingFeatureForm ::~HostSettingFeatureForm() {}

void HostSettingFeatureForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void HostSettingFeatureForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  UI_SETVALUE(d_->ui.spinBox_MaxThreadCount, data_in.max_thread_cnt);
  UI_SETCHECKED(d_->ui.checkBox_ReuseCmdSkt, data_in.reuse_cmdsocket);
  UI_SETCHECKED(d_->ui.checkBox_NoPasvAdrs, data_in.no_pasv_adrs);
  UI_SETVALUE(d_->ui.spinBox_NoopInterval, data_in.noop_interval);
  UI_SETCURRENTINDEX(d_->ui.comboBox_ErrorMode, data_in.error_mode);
  UI_SETCHECKED(d_->ui.checkBox_Reconnect, data_in.reconnect);
}

void HostSettingFeatureForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  UI_VALUE(data_out.max_thread_cnt, d_->ui.spinBox_MaxThreadCount);
  UI_ISCHECKED(data_out.reuse_cmdsocket, d_->ui.checkBox_ReuseCmdSkt);
  UI_ISCHECKED(data_out.no_pasv_adrs, d_->ui.checkBox_NoPasvAdrs);
  UI_VALUE(data_out.noop_interval, d_->ui.spinBox_NoopInterval);
  UI_CURRENTINDEX(data_out.error_mode, d_->ui.comboBox_ErrorMode);
  UI_ISCHECKED(data_out.reconnect, d_->ui.checkBox_Reconnect);
}
