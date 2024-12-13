#ifndef FFFTPGUI_UI_OPTION_OPTIONTRANSFER1FORM_HPP_
#define FFFTPGUI_UI_OPTION_OPTIONTRANSFER1FORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class OptionTransfer1Form : public BaseForm {
  Q_OBJECT;

 public:
  enum class Modes {
    kAuto,
    kASCII,
    kBinary,
  };

  struct Data : public BaseForm::Data {
    Modes trans_mode;
    std::vector<std::wstring> ascii_ext;
    bool rm_eof;
    bool save_timestamp;
    bool vax_semicolon;
    bool make_all_dir;
    bool abort_on_list_error;
    Data();
    Data(
      Modes trans_mode,
      const std::vector<std::wstring>& ascii_ext,
      bool rm_eof,
      bool save_timestamp,
      bool vax_semicolon,
      bool make_all_dir,
      bool abort_on_list_error);
  };

  explicit OptionTransfer1Form(QWidget* parent = Q_NULLPTR);
  virtual ~OptionTransfer1Form();
  int helpID() const override;

 protected:
  void setRawData(const BaseForm::Data& data) override;
  void updateUi(const BaseForm::Data& data) override;
  void updateData(BaseForm::Data& data) const override;

 private:
  void updateEnabled();
  bool askFileName(QString& fname);
  void addFileName(const QString& fname);

 private slots:
  void onClick_radioButton_TransModeASCII();
  void onClick_radioButton_TransModeBin();
  void onClick_radioButton_TransModeAuto();
  void onClick_listView_AsciiExt();
  void onClick_pushButton_AddExt();
  void onClick_pushButton_DelExt();

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(OptionTransfer1Form);
};

#endif  // FFFTPGUI_UI_OPTION_OPTIONTRANSFER1FORM_HPP_
