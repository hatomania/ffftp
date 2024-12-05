#ifndef FFFTPGUI_UI_UICOMMON_H_
#define FFFTPGUI_UI_UICOMMON_H_

#define UI_SETTEXT(c, d) c->setText(d)
#define UI_SETCHECKED(c, d) c->setChecked(d)
#define UI_SETENABLED(c, d) c->setEnabled(d)
#define UI_SETCURRENTINDEX(c, d) c->setCurrentIndex(d)
#define UI_SETPLAINTEXT(c, d) c->setPlainText(d)

#define UI_TEXT(d, c) d = c->text()
#define UI_ISCHECKED(d, c) d = c->isChecked()
#define UI_CURRENTINDEX(d, c) d = c->currentIndex()
#define UI_TOPLAINTEXT(d, c) d = c->toPlainText()

#endif /* FFFTPGUI_UI_UICOMMON_H_ */
