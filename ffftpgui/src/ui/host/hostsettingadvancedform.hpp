#ifndef FFFTPGUI_UI_HOST_HOSTSETTINGADVANCEDFORM_HPP_
#define FFFTPGUI_UI_HOST_HOSTSETTINGADVANCEDFORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class HostSettingAdvancedForm : public BaseForm {
  Q_OBJECT

 public:
  struct Data : public BaseForm::Data {
    bool firewall;
    bool pasv;
    bool syncmove;
    int port;
    std::wstring account;
    int timezone;
    int security;
    std::wstring initcmd;
    Data();
    Data(bool firewall, bool pasv, bool syncmove, int port,
         const std::wstring& account, int timezone, int security,
         const std::wstring& initcmd);
  };

  explicit HostSettingAdvancedForm(QWidget* parent = Q_NULLPTR);
  virtual ~HostSettingAdvancedForm();

 protected:
  void setRawData(const BaseForm::Data& data);
  void updateUi(const BaseForm::Data& data);
  void updateData(BaseForm::Data& data) const;

 private slots:
  void onClick_pushButton_StdPort();

 private:
  class Private;
  Private* d_;
  Q_DISABLE_COPY(HostSettingAdvancedForm)
};

#endif  // FFFTPGUI_UI_HOST_HOSTSETTINGADVANCEDFORM_HPP_
