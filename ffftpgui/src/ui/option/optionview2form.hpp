#ifndef FFFTPGUI_UI_OPTION_OPTIONVIEW2FORM_HPP_
#define FFFTPGUI_UI_OPTION_OPTIONVIEW2FORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class OptionView2Form : public BaseForm {
  Q_OBJECT;

 public:
  struct Data : public BaseForm::Data {
    bool disp_permissions_number;
    bool auto_refresh_filelist;
    bool remove_old_log;
    Data();
    Data(bool disp_permissions_number,
         bool auto_refresh_filelist,
         bool remove_old_log);
  };

  explicit OptionView2Form(QWidget* parent = Q_NULLPTR);
  virtual ~OptionView2Form();
  int helpID() const override;

 protected:
  void setRawData(const BaseForm::Data& data) override;
  void updateUi(const BaseForm::Data& data) override;
  void updateData(BaseForm::Data& data) const override;

 private slots:

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(OptionView2Form);
};

#endif  // FFFTPGUI_UI_OPTION_OPTIONVIEW2FORM_HPP_
