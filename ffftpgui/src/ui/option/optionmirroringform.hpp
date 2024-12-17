#ifndef FFFTPGUI_UI_OPTION_OPTIONMIRRORINGFORM_HPP_
#define FFFTPGUI_UI_OPTION_OPTIONMIRRORINGFORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class OptionMirroringForm : public BaseForm {
  Q_OBJECT;

 public:
  struct Data : public BaseForm::Data {
    std::vector<std::wstring> no_trn;
    std::vector<std::wstring> no_del;
    bool fname_cnv;
    bool up_del_notify;
    bool down_del_notify;
    bool no_transfer_contents;
    Data();
    Data(
      const std::vector<std::wstring>& no_trn,
      const std::vector<std::wstring>& no_del,
      bool fname_cnv,
      bool up_del_notify,
      bool down_del_notify,
      bool no_transfer_contents);
  };

  explicit OptionMirroringForm(QWidget* parent = Q_NULLPTR);
  virtual ~OptionMirroringForm();
  int helpID() const override;

 protected:
  void setRawData(const BaseForm::Data& data) override;
  void updateUi(const BaseForm::Data& data) override;
  void updateData(BaseForm::Data& data) const override;

 private slots:

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(OptionMirroringForm);
};

#endif  // FFFTPGUI_UI_OPTION_OPTIONMIRRORINGFORM_HPP_
