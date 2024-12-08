#ifndef FFFTPGUI_UI_HOST_HOSTSETTINGFEATUREFORM_HPP_
#define FFFTPGUI_UI_HOST_HOSTSETTINGFEATUREFORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class HostSettingFeatureForm : public BaseForm {
  Q_OBJECT

 public:
  struct Data : public BaseForm::Data {
    Data();
  };

  explicit HostSettingFeatureForm(QWidget* parent = Q_NULLPTR);
  virtual ~HostSettingFeatureForm();

 protected:
  void setRawData(const BaseForm::Data& data) override;
  void updateUi(const BaseForm::Data& data) override;
  void updateData(BaseForm::Data& data) const override;

 private slots:

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY(HostSettingFeatureForm)
};

#endif  // FFFTPGUI_UI_HOST_HOSTSETTINGFEATUREFORM_HPP_
