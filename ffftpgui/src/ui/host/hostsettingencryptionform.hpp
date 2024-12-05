#ifndef FFFTPGUI_UI_HOST_HOSTSETTINGENCRYPTIONFORM_HPP_
#define FFFTPGUI_UI_HOST_HOSTSETTINGENCRYPTIONFORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class HostSettingEncryptionForm : public BaseForm {
  Q_OBJECT

 public:
  struct Data : public BaseForm::Data {
    Data();
  };

  explicit HostSettingEncryptionForm(QWidget* parent = Q_NULLPTR);
  virtual ~HostSettingEncryptionForm();

 protected:
  void setRawData(const BaseForm::Data& data);
  void updateUi(const BaseForm::Data& data);
  void updateData(BaseForm::Data& data) const;

 private slots:

 private:
  class Private;
  Private* d_;
  Q_DISABLE_COPY(HostSettingEncryptionForm)
};

#endif  // FFFTPGUI_UI_HOST_HOSTSETTINGENCRYPTIONFORM_HPP_
