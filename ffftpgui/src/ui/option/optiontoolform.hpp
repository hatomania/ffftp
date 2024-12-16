#ifndef FFFTPGUI_UI_OPTION_OPTIONTOOLFORM_HPP_
#define FFFTPGUI_UI_OPTION_OPTIONTOOLFORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class OptionToolForm : public BaseForm {
  Q_OBJECT;

 public:
  struct Data : public BaseForm::Data {
    enum { kViewerCnt = 3 };
    std::vector<std::wstring> viewer_name;
    Data();
    Data(const std::vector<std::wstring>& viewer_name);
  };

  explicit OptionToolForm(QWidget* parent = Q_NULLPTR);
  virtual ~OptionToolForm();
  int helpID() const override;

 protected:
  void setRawData(const BaseForm::Data& data) override;
  void updateUi(const BaseForm::Data& data) override;
  void updateData(BaseForm::Data& data) const override;

private:
  bool askFilename(QString& fname, const QString& path_in);

 private Q_SLOTS:
  void onClick_toolButton_SelectViewer1();
  void onClick_toolButton_SelectViewer2();
  void onClick_toolButton_SelectViewer3();

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(OptionToolForm);
};

#endif  // FFFTPGUI_UI_OPTION_OPTIONTOOLFORM_HPP_
