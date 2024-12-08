#include "hostsettingencryptionform.hpp"

#include "ui_hostsettingencryptionform.h"

namespace {
using ThisData = HostSettingEncryptionForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingEncryptionForm::Private {
 public:
  Private();
  ~Private();
  Ui::HostSettingEncryptionForm ui;
};
HostSettingEncryptionForm::Private::Private() {}
HostSettingEncryptionForm::Private::~Private() {}

HostSettingEncryptionForm::Data::Data()
    : use_no_encryption(false), use_ftp_es(false), use_ftp_is(false) {}

HostSettingEncryptionForm::Data::Data(bool use_no_encryption, bool use_ftp_es,
                                      bool use_ftp_is)
    : use_no_encryption(use_no_encryption),
      use_ftp_es(use_ftp_es),
      use_ftp_is(use_ftp_is) {}

HostSettingEncryptionForm::HostSettingEncryptionForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
HostSettingEncryptionForm ::~HostSettingEncryptionForm() {}

void HostSettingEncryptionForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void HostSettingEncryptionForm::updateUi(const BaseForm::Data& data) {}

void HostSettingEncryptionForm::updateData(BaseForm::Data& data) const {}
