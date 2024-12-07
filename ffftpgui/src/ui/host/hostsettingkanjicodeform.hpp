#ifndef FFFTPGUI_UI_HOST_HOSTSETTINGKANJICODEFORM_HPP_
#define FFFTPGUI_UI_HOST_HOSTSETTINGKANJICODEFORM_HPP_

#include <memory>

#include <QWidget>

#include "ui/base/baseform.hpp"

class HostSettingKanjiCodeForm : public BaseForm {
  Q_OBJECT

 public:
  enum class KanjiCode {
    kNOP,
    kAUTO,
    kJIS,
    kSJIS,
    kEUC,
    kSMH,
    kSMC,
    kUTF8N,
    kUTF8BOM,
    kUTF8HFSX,
  };
  struct Data : public BaseForm::Data {
    KanjiCode kanjicode;
    bool kanacnv;
    KanjiCode kanjicode_name;
    bool kanacnv_name;
    Data();
    Data(KanjiCode kanjicode, bool kanacnv, KanjiCode kanjicode_name,
         bool kanacnv_name);
  };

  explicit HostSettingKanjiCodeForm(QWidget* parent = Q_NULLPTR);
  virtual ~HostSettingKanjiCodeForm();

 protected:
  void setRawData(const BaseForm::Data& data);
  void updateUi(const BaseForm::Data& data);
  void updateData(BaseForm::Data& data) const;

 private slots:
  void onClick_radioButton_Host();
  void onClick_radioButton_File();

 private:
  class Private;
  Private* d_;
  Q_DISABLE_COPY(HostSettingKanjiCodeForm)
};

#endif  // FFFTPGUI_UI_HOST_HOSTSETTINGKANJICODEFORM_HPP_
