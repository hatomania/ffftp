#include "hostsettingdialupform.hpp"

#include "ui_hostsettingdialupform.h"

#include "ui/uicommon.h"

namespace {
using ThisData = HostSettingDialupForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingDialupForm::Private {
 public:
  Private();
  ~Private();
  Ui::HostSettingDialupForm ui;
};
HostSettingDialupForm::Private::Private() {}
HostSettingDialupForm::Private::~Private() {}

HostSettingDialupForm::Data::Data()
    : dialup(false),
      dial_entries(),
      dial_entry(),
      dialup_always(false),
      dialup_notify(false) {}

HostSettingDialupForm::Data::Data(bool dialup,
                                  const std::vector<std::wstring>& dial_entries,
                                  const std::wstring& dial_entry,
                                  bool dialup_always, bool dialup_notify)
    : dialup(dialup),
      dial_entries(dial_entries),
      dial_entry(dial_entry),
      dialup_always(dialup_always),
      dialup_notify(dialup_notify) {}

HostSettingDialupForm::HostSettingDialupForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
HostSettingDialupForm ::~HostSettingDialupForm() {}

void HostSettingDialupForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void HostSettingDialupForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  // TODO:
  // 「RASの制御を行わない」チェックボックス（オプションダイアログの「接続/切断」タブ）がONの時
  // チェックをOFFにしてDisable
  UI_SETCHECKED(d_->ui.groupBox_Dialup, data_in.dialup);
  d_->ui.comboBox_DialupEnties->clear();
  int curindex = 0;
  for (int i = 0; const auto& entry : data_in.dial_entries) {
    d_->ui.comboBox_DialupEnties->addItem(QString(entry.c_str()));
    if (entry == data_in.dial_entry) curindex = i;
    ++i;
  }
  d_->ui.comboBox_DialupEnties->setCurrentIndex(curindex);
  UI_SETCHECKED(d_->ui.groupBox_DialupAlways, data_in.dialup_always);
  UI_SETCHECKED(d_->ui.checkBox_DialupNotify, data_in.dialup_notify);
}

void HostSettingDialupForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  UI_ISCHECKED(data_out.dialup, d_->ui.groupBox_Dialup);
  data_out.dial_entry =
      d_->ui.comboBox_DialupEnties
          ->itemData(d_->ui.comboBox_DialupEnties->currentIndex())
          .toString()
          .toStdWString();
  UI_ISCHECKED(data_out.dialup_always, d_->ui.groupBox_DialupAlways);
  UI_ISCHECKED(data_out.dialup_notify, d_->ui.checkBox_DialupNotify);
}
