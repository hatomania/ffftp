#ifndef FFFTPGUI_UI_HOST_HOSTSETTINGSPECIALFORM_HPP_
#define FFFTPGUI_UI_HOST_HOSTSETTINGSPECIALFORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class HostSettingSpecialForm : public BaseForm {
  Q_OBJECT

 public:
  struct Data : public BaseForm::Data {
    bool list_cmd_only;
    bool use_mlsd;
    bool use_nlst_r;
    bool no_fullpath;
    std::wstring chmod_cmd;
    int host_type;
    std::wstring ls_name;
    Data();
    Data(bool list_cmd_only, bool use_mlsd, bool use_nlst_r, bool no_fullpath,
         const std::wstring& chmod_cmd, int host_type,
         const std::wstring& ls_name);
  };

  explicit HostSettingSpecialForm(QWidget* parent = Q_NULLPTR);
  virtual ~HostSettingSpecialForm();

 protected:
  void setRawData(const BaseForm::Data& data) override;
  void updateUi(const BaseForm::Data& data) override;
  void updateData(BaseForm::Data& data) const override;

 private slots:

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY(HostSettingSpecialForm)
};

#endif  // FFFTPGUI_UI_HOST_HOSTSETTINGSPECIALFORM_HPP_
