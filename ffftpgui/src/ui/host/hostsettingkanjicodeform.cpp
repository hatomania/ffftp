#include "hostsettingkanjicodeform.hpp"

#include "ui_hostsettingkanjicodeform.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingKanjiCodeForm::Private {
 public:
  Private() {}
  ~Private() = default;
  Ui::HostSettingKanjiCodeForm ui;
  QMap<HostSettingKanjiCodeForm::Code, QRadioButton*> vec_host_radio;
  QMap<HostSettingKanjiCodeForm::Code, QRadioButton*> vec_file_radio;
  Code getHostCode() const;
  Code getFileCode() const;
  bool isEnabledHostCheckbox() const;
  bool isEnabledFileCheckbox() const;
  void enableHostCheckbox() const;
  void enableFileCheckbox() const;
};

HostSettingKanjiCodeForm::Data::Data()
    : host_code(Code::NOP),
      file_code(Code::AUTO),
      is_host_hkana_to_wkana(true),
      is_file_hkana_to_wkana(false) {}

HostSettingKanjiCodeForm::Code HostSettingKanjiCodeForm::Private::getHostCode()
    const {
  Code ret = Code::NOP;
  for (auto [k, v] : vec_host_radio.asKeyValueRange()) {
    if (v->isChecked()) {
      ret = k;
      break;
    }
  }
  return ret;
}

HostSettingKanjiCodeForm::Code HostSettingKanjiCodeForm::Private::getFileCode()
    const {
  Code ret = Code::AUTO;
  for (auto [k, v] : vec_file_radio.asKeyValueRange()) {
    if (v->isChecked()) {
      ret = k;
      break;
    }
  }
  return ret;
}

bool HostSettingKanjiCodeForm::Private::isEnabledHostCheckbox() const {
  bool enabled = false;
  QVector<Code> check_kana_code = {Code::SJIS, Code::JIS, Code::EUC};
  if (check_kana_code.indexOf(getHostCode()) >= 0) enabled = true;
  return enabled;
}

bool HostSettingKanjiCodeForm::Private::isEnabledFileCheckbox() const {
  bool enabled = false;
  QVector<Code> check_kana_code = {Code::JIS, Code::EUC};
  if (check_kana_code.indexOf(getFileCode()) >= 0) enabled = true;
  return enabled;
}

void HostSettingKanjiCodeForm::Private::enableHostCheckbox() const {
  ui.checkBox_1_1_HKanaToW->setEnabled(isEnabledHostCheckbox());
}

void HostSettingKanjiCodeForm::Private::enableFileCheckbox() const {
  ui.checkBox_2_1_HKanaToW->setEnabled(isEnabledFileCheckbox());
}

HostSettingKanjiCodeForm::HostSettingKanjiCodeForm(QWidget* parent)
    : QWidget(parent), d_(new HostSettingKanjiCodeForm::Private()) {
  d_->ui.setupUi(this);
  d_->vec_host_radio = {
      {Code::NOP, d_->ui.radioButton_1_1_NOP},
      {Code::SJIS, d_->ui.radioButton_1_2_SJIS},
      {Code::JIS, d_->ui.radioButton_1_3_JIS},
      {Code::EUC, d_->ui.radioButton_1_4_EUC},
      {Code::UTF8, d_->ui.radioButton_1_5_UTF8},
      {Code::UTF8BOM, d_->ui.radioButton_1_6_UTF8BOM},
  };
  d_->vec_file_radio = {
      {Code::AUTO, d_->ui.radioButton_2_1_Auto},
      {Code::SJIS, d_->ui.radioButton_2_2_SJIS},
      {Code::JIS, d_->ui.radioButton_2_3_JIS},
      {Code::EUC, d_->ui.radioButton_2_4_EUC},
      {Code::SMBHEX, d_->ui.radioButton_2_5_SMB_HEX},
      {Code::SMBCAP, d_->ui.radioButton_2_6_SMB_CAP},
      {Code::UTF8, d_->ui.radioButton_2_7_UTF8},
      {Code::UTF8HFSP, d_->ui.radioButton_2_8_UTF8HFSp},
  };
  setDataAsDefault();
}

void HostSettingKanjiCodeForm::setData(const Data& data) const {
  // 念のためすべてuncheckしてからチェックする
  for (auto [k, v] : d_->vec_host_radio.asKeyValueRange()) {
    v->setChecked(false);
  }
  for (auto [k, v] : d_->vec_file_radio.asKeyValueRange()) {
    v->setChecked(false);
  }
  d_->vec_host_radio[data.host_code]->setChecked(true);
  d_->vec_file_radio[data.file_code]->setChecked(true);
  d_->ui.checkBox_1_1_HKanaToW->setChecked(data.is_host_hkana_to_wkana.value());
  d_->ui.checkBox_2_1_HKanaToW->setChecked(data.is_file_hkana_to_wkana.value());
  d_->enableHostCheckbox();
  d_->enableFileCheckbox();
}

const HostSettingKanjiCodeForm::Data& HostSettingKanjiCodeForm::getData() const {
  static Data data;
  data.host_code = d_->getHostCode();
  data.file_code = d_->getFileCode();
  data.is_host_hkana_to_wkana = d_->ui.checkBox_1_1_HKanaToW->isChecked();
  data.is_file_hkana_to_wkana = d_->ui.checkBox_2_1_HKanaToW->isChecked();
  if (d_->isEnabledHostCheckbox()) data.is_host_hkana_to_wkana.reset();
  if (d_->isEnabledFileCheckbox()) data.is_file_hkana_to_wkana.reset();
  return data;
}

void HostSettingKanjiCodeForm::setDataAsDefault() const {
  this->setData(Data());
}

void HostSettingKanjiCodeForm::onClick_radioButton_Host() {
  qDebug() << __FUNCTION__ << "called!";
  d_->enableHostCheckbox();
}

void HostSettingKanjiCodeForm::onClick_radioButton_File() {
  qDebug() << __FUNCTION__ << "called!";
  d_->enableFileCheckbox();
}
