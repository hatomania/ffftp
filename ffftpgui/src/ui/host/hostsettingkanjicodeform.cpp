#include "hostsettingkanjicodeform.hpp"

#include "ui/uicommon.h"
#include "ui_hostsettingkanjicodeform.h"

namespace {
using ThisData = HostSettingKanjiCodeForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingKanjiCodeForm::Private {
 public:
  Private();
  ~Private();
  Ui::HostSettingKanjiCodeForm ui;
};
HostSettingKanjiCodeForm::Private::Private() {}
HostSettingKanjiCodeForm::Private::~Private() {}

HostSettingKanjiCodeForm::Data::Data()
    : kanjicode(KanjiCode::kNOP),
      kanacnv(false),
      kanjicode_name(KanjiCode::kAUTO),
      kanacnv_name(false) {}

HostSettingKanjiCodeForm::Data::Data(KanjiCode kanjicode, bool kanacnv,
                                     KanjiCode kanjicode_name,
                                     bool kanacnv_name)
    : kanjicode(kanjicode),
      kanacnv(kanacnv),
      kanjicode_name(kanjicode_name),
      kanacnv_name(kanacnv_name) {}

HostSettingKanjiCodeForm::HostSettingKanjiCodeForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
HostSettingKanjiCodeForm ::~HostSettingKanjiCodeForm() {}

void HostSettingKanjiCodeForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void HostSettingKanjiCodeForm::updateUi(const BaseForm::Data& data) {
  const ThisData& tdata = castData(data);
  struct TValue {
    QRadioButton& rbtn;
    bool conv;
    //TValue() : rbtn(Q_NULLPTR),conv(false) {};
    //TValue(const TValue& v) : rbtn(v.rbtn), conv(v.conv) {}
    TValue(QRadioButton& rbtn, bool conv) : rbtn(rbtn), conv(conv) {}
  };
  const std::map<KanjiCode, const TValue> host_codes{
      {KanjiCode::kNOP, {*d_->ui.radioButton_1_1_NOP, false}},
      {KanjiCode::kSJIS, {*d_->ui.radioButton_1_2_SJIS, true}},
      {KanjiCode::kJIS, {*d_->ui.radioButton_1_3_JIS, true}},
      {KanjiCode::kEUC, {*d_->ui.radioButton_1_4_EUC, true}},
      {KanjiCode::kUTF8N, {*d_->ui.radioButton_1_5_UTF8N, false}},
      {KanjiCode::kUTF8BOM, {*d_->ui.radioButton_1_6_UTF8BOM, false}},
  };
  const std::map<KanjiCode, const TValue> name_codes{
      {KanjiCode::kAUTO, TValue{*d_->ui.radioButton_2_1_AUTO, false}},
      {KanjiCode::kSJIS, TValue{*d_->ui.radioButton_2_2_SJIS, false}},
      {KanjiCode::kJIS, TValue{*d_->ui.radioButton_2_3_JIS, true}},
      {KanjiCode::kEUC, TValue{*d_->ui.radioButton_2_4_EUC, true}},
      {KanjiCode::kSMH, TValue{*d_->ui.radioButton_2_5_SMB_HEX, false}},
      {KanjiCode::kSMC, TValue{*d_->ui.radioButton_2_6_SMB_CAP, false}},
      {KanjiCode::kUTF8N, TValue{*d_->ui.radioButton_2_7_UTF8, false}},
      {KanjiCode::kUTF8HFSX, TValue{*d_->ui.radioButton_2_8_UTF8HFSP, false}},
  };
  //host_codes[tdata.kanjicode].rbtn.setChecked(true);// ←この書き方だとなぜかエラーなる
  host_codes.at(tdata.kanjicode).rbtn.setChecked(true);
  UI_SETCHECKED(d_->ui.checkBox_1_1_KanaConv, tdata.kanacnv);
  UI_SETENABLED(d_->ui.checkBox_1_1_KanaConv,
                host_codes.find(tdata.kanjicode)->second.conv);
  name_codes.at(tdata.kanjicode_name).rbtn.setChecked(true);
  UI_SETCHECKED(d_->ui.checkBox_2_1_KanaConv, tdata.kanacnv_name);
  UI_SETENABLED(d_->ui.checkBox_2_1_KanaConv,
                name_codes.find(tdata.kanjicode_name)->second.conv);
}

void HostSettingKanjiCodeForm::updateData(BaseForm::Data& data) const {
  ThisData& tdata = castData(data);
  const std::map<KanjiCode, const QRadioButton&> host_codes{
      {KanjiCode::kNOP, *d_->ui.radioButton_1_1_NOP},
      {KanjiCode::kSJIS, *d_->ui.radioButton_1_2_SJIS},
      {KanjiCode::kJIS, *d_->ui.radioButton_1_3_JIS},
      {KanjiCode::kEUC, *d_->ui.radioButton_1_4_EUC},
      {KanjiCode::kUTF8N, *d_->ui.radioButton_1_5_UTF8N},
      {KanjiCode::kUTF8BOM, *d_->ui.radioButton_1_6_UTF8BOM},
  };
  const std::map<KanjiCode, const QRadioButton&> name_codes{
      {KanjiCode::kAUTO, *d_->ui.radioButton_2_1_AUTO},
      {KanjiCode::kSJIS, *d_->ui.radioButton_2_2_SJIS},
      {KanjiCode::kJIS, *d_->ui.radioButton_2_3_JIS},
      {KanjiCode::kEUC, *d_->ui.radioButton_2_4_EUC},
      {KanjiCode::kSMH, *d_->ui.radioButton_2_5_SMB_HEX},
      {KanjiCode::kSMC, *d_->ui.radioButton_2_6_SMB_CAP},
      {KanjiCode::kUTF8N, *d_->ui.radioButton_2_7_UTF8},
      {KanjiCode::kUTF8HFSX, *d_->ui.radioButton_2_8_UTF8HFSP},
  };
  for (const auto& p : host_codes) {
    if (p.second.isChecked()) {
      tdata.kanjicode = p.first;
      break;
    }
  }
  UI_ISCHECKED(tdata.kanacnv, d_->ui.checkBox_1_1_KanaConv);
  for (const auto& p : name_codes) {
    if (p.second.isChecked()) {
      tdata.kanjicode_name = p.first;
      break;
    }
  }
  UI_ISCHECKED(tdata.kanacnv_name, d_->ui.checkBox_2_1_KanaConv);
}

void HostSettingKanjiCodeForm::onClick_radioButton_Host() {
  ThisData tdata;
  updateData(tdata);
  updateUi(tdata);
}

void HostSettingKanjiCodeForm::onClick_radioButton_File() {
  onClick_radioButton_Host();
}
