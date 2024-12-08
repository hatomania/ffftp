#include "kanjicodedatatransceiver.hpp"

#include "ffftp_hostdata.h"

IMPL_DATATRANSCEIVER_BEGIN(HostSettingKanjiCodeForm);

IMPL_DATATRANSCEIVER_SEND(hdata_in) {
  const hostdata& hdata = *static_cast<const hostdata*>(hdata_in);
  static const std::map<int, HostSettingKanjiCodeForm::KanjiCode> convtable{
      {KC_NOP, HostSettingKanjiCodeForm::KanjiCode::kNOP},
      {KC_SJIS, HostSettingKanjiCodeForm::KanjiCode::kSJIS},
      {KC_JIS, HostSettingKanjiCodeForm::KanjiCode::kJIS},
      {KC_EUC, HostSettingKanjiCodeForm::KanjiCode::kEUC},
      {KC_UTF8N, HostSettingKanjiCodeForm::KanjiCode::kUTF8N},
      {KC_UTF8BOM, HostSettingKanjiCodeForm::KanjiCode::kUTF8BOM},
  };
  static const std::map<int, HostSettingKanjiCodeForm::KanjiCode>
      convtable_name{
          {KC_AUTO, HostSettingKanjiCodeForm::KanjiCode::kAUTO},
          {KC_SJIS, HostSettingKanjiCodeForm::KanjiCode::kSJIS},
          {KC_JIS, HostSettingKanjiCodeForm::KanjiCode::kJIS},
          {KC_EUC, HostSettingKanjiCodeForm::KanjiCode::kEUC},
          {KC_SMH, HostSettingKanjiCodeForm::KanjiCode::kSMH},
          {KC_SMC, HostSettingKanjiCodeForm::KanjiCode::kSMC},
          {KC_UTF8N, HostSettingKanjiCodeForm::KanjiCode::kUTF8N},
          {KC_UTF8HFSX, HostSettingKanjiCodeForm::KanjiCode::kUTF8HFSX},
      };
  ThisData form_data{
      convtable.at(hdata.kanjicode.kanjicode),
      hdata.kanjicode.kanacnv,
      convtable_name.at(hdata.kanjicode.kanjicode_name),
      hdata.kanjicode.kanacnv_name,
  };
  form().setData(form_data);
}

IMPL_DATATRANSCEIVER_RECEIVE(hdata_out) {
  static ThisData form_data;
  form_data = static_cast<const ThisData&>(form().data());
  hostdata& hdata = *static_cast<hostdata*>(hdata_out);
  static const std::map<HostSettingKanjiCodeForm::KanjiCode, int> convtable{
      {HostSettingKanjiCodeForm::KanjiCode::kNOP, KC_NOP},
      {HostSettingKanjiCodeForm::KanjiCode::kSJIS, KC_SJIS},
      {HostSettingKanjiCodeForm::KanjiCode::kJIS, KC_JIS},
      {HostSettingKanjiCodeForm::KanjiCode::kEUC, KC_EUC},
      {HostSettingKanjiCodeForm::KanjiCode::kUTF8N, KC_UTF8N},
      {HostSettingKanjiCodeForm::KanjiCode::kUTF8BOM, KC_UTF8BOM},
  };
  static const std::map<HostSettingKanjiCodeForm::KanjiCode, int>
      convtable_name{
          {HostSettingKanjiCodeForm::KanjiCode::kAUTO, KC_AUTO},
          {HostSettingKanjiCodeForm::KanjiCode::kSJIS, KC_SJIS},
          {HostSettingKanjiCodeForm::KanjiCode::kJIS, KC_JIS},
          {HostSettingKanjiCodeForm::KanjiCode::kEUC, KC_EUC},
          {HostSettingKanjiCodeForm::KanjiCode::kSMH, KC_SMH},
          {HostSettingKanjiCodeForm::KanjiCode::kSMC, KC_SMC},
          {HostSettingKanjiCodeForm::KanjiCode::kUTF8N, KC_UTF8N},
          {HostSettingKanjiCodeForm::KanjiCode::kUTF8HFSX, KC_UTF8HFSX},
      };
  hdata.kanjicode = {
      .kanjicode = convtable.at(form_data.kanjicode),
      .kanacnv = form_data.kanacnv,
      .kanjicode_name = convtable_name.at(form_data.kanjicode_name),
      .kanacnv_name = form_data.kanacnv_name,
  };
}

IMPL_DATATRANSCEIVER_END(HostSettingKanjiCodeForm);
