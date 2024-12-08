#ifndef FFFTPGUI_UI_HOST_HOSTSETTINGENCRYPTIONFORM_HPP_
#define FFFTPGUI_UI_HOST_HOSTSETTINGENCRYPTIONFORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class HostSettingEncryptionForm : public BaseForm {
  Q_OBJECT

 public:
  struct Data : public BaseForm::Data {
    bool use_no_encryption;
    bool use_ftp_es;
    bool use_ftp_is;
    Data();
    Data(bool use_no_encryption, bool use_ftp_es, bool use_ftp_is);
  };

  explicit HostSettingEncryptionForm(QWidget* parent = Q_NULLPTR);
  virtual ~HostSettingEncryptionForm();

 protected:
  void setRawData(const BaseForm::Data& data) override;
  void updateUi(const BaseForm::Data& data) override;
  void updateData(BaseForm::Data& data) const override;

 private slots:

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY(HostSettingEncryptionForm)
};

#endif  // FFFTPGUI_UI_HOST_HOSTSETTINGENCRYPTIONFORM_HPP_
