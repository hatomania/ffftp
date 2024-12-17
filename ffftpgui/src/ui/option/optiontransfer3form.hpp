#ifndef FFFTPGUI_UI_OPTION_OPTIONTRANSFER3FORM_HPP_
#define FFFTPGUI_UI_OPTION_OPTIONTRANSFER3FORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class OptionTransfer3Form : public BaseForm {
  Q_OBJECT;

 public:
  struct Data : public BaseForm::Data {
    std::vector<std::pair<std::wstring, int>> attr_list;
    bool use_folder_attr;
    int folder_attr;
    Data();
    Data(
      const std::vector<std::pair<std::wstring, int>>& attr_list,
      bool use_folder_attr,
      int folder_attr);
  };

  explicit OptionTransfer3Form(QWidget* parent = Q_NULLPTR);
  virtual ~OptionTransfer3Form();
  int helpID() const override;

 protected:
  void setRawData(const BaseForm::Data& data) override;
  void updateUi(const BaseForm::Data& data) override;
  void updateData(BaseForm::Data& data) const override;

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(OptionTransfer3Form);
};

#endif  // FFFTPGUI_UI_OPTION_OPTIONTRANSFER3FORM_HPP_
