#ifndef FFFTPGUI_UI_HOST_HOSTSETTINGFEATUREFORM_HPP_
#define FFFTPGUI_UI_HOST_HOSTSETTINGFEATUREFORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class HostSettingFeatureForm : public BaseForm {
  Q_OBJECT

 public:
  struct Data : public BaseForm::Data {
    int max_thread_cnt;
    bool reuse_cmdsocket;
    bool no_pasv_adrs;
    int noop_interval;
    int error_mode;
    bool reconnect;
    Data();
    Data(int max_thread_cnt, bool reuse_cmdsocket, bool no_pasv_adrs,
         int noop_interval, int error_mode, bool reconnect);
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
