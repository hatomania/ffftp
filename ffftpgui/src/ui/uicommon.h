#ifndef FFFTPGUI_UI_UICOMMON_H_
#define FFFTPGUI_UI_UICOMMON_H_

#include <map>

#include <QRadioButton>

#define UI_SETTEXT(c, d) c->setText(d)
#define UI_SETCHECKED(c, d) c->setChecked(d)
#define UI_SETENABLED(c, d) c->setEnabled(d)
#define UI_SETCURRENTINDEX(c, d) c->setCurrentIndex(d)
#define UI_SETPLAINTEXT(c, d) c->setPlainText(d)
#define UI_SETVALUE(c, d) c->setValue(d)
#define UI_SETTITLE(c, d) c->setTitle(d)

#define UI_TEXT(d, c) d = c->text()
#define UI_ISCHECKED(d, c) d = c->isChecked()
#define UI_CURRENTINDEX(d, c) d = c->currentIndex()
#define UI_TOPLAINTEXT(d, c) d = c->toPlainText()
#define UI_VALUE(d, c) d = c->value()

#define MAKE_TRANSCEIVER(K, T, F) \
  d_->transceiver.insert(std::make_pair(K, std::make_unique<T>(F)));

// ラジオボタンを集合で扱うテンプレート
template <typename _KEY>
class RadioButtons {
 public:
  RadioButtons() = delete;
  explicit RadioButtons(
      const std::initializer_list<std::pair<_KEY, QRadioButton&>>& list)
      : radios_(list.begin(), list.end()) {}
  virtual ~RadioButtons() {}

  _KEY checked() const {
    _KEY ret{};
    for (const auto& [k, v] : radios_) {
      if (v.isChecked()) {
        ret = k;
        break;
      }
    }
    return ret;
  }

  void setChecked(const _KEY& key) { radios_.at(key).setChecked(true); }

 private:
  const std::map<_KEY, QRadioButton&> radios_;
};

#endif /* FFFTPGUI_UI_UICOMMON_H_ */
