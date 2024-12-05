#ifndef FFFTPGUI_UI_HOST_HOSTSETTINGGENERALFORM_HPP_
#define FFFTPGUI_UI_HOST_HOSTSETTINGGENERALFORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class HostSettingGeneralForm : public BaseForm {
  Q_OBJECT

 public:
  struct Data : public BaseForm::Data {
    std::wstring host_name;
    std::wstring host_adrs;
    std::wstring username;
    std::wstring password;
    bool anonymous;
    std::wstring initdir_local;
    std::wstring initdir_remote;
    std::wstring initdir_remote_now;
    bool enabled_curdir;
    bool last_dir;
    Data();
    Data(const std::wstring& host_name, const std::wstring& host_adrs,
         const std::wstring& username, const std::wstring& password,
         bool anonymous, const std::wstring& initdir_local,
         const std::wstring& initdir_remote,
         const std::wstring& initdir_remote_now, bool enabled_curdir,
         bool last_dir);
  };

  explicit HostSettingGeneralForm(QWidget* parent = Q_NULLPTR);
  virtual ~HostSettingGeneralForm();

 protected:
  void setRawData(const BaseForm::Data& data);
  void updateUi(const BaseForm::Data& data);
  void updateData(BaseForm::Data& data) const;

 private slots:
  void onClick_toolButton_SelectLocalDir();
  void onClick_pushButton_CurDir();
  void onClick_checkBox_Anonymous(bool);

 private:
  const Data& mydata() const;

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY(HostSettingGeneralForm)
};

#endif  // FFFTPGUI_UI_HOST_HOSTSETTINGGENERALFORM_HPP_
