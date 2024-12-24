#include "optiontoolform.hpp"

#include <QFileDialog>

#include "ui_optiontoolform.h"

#include "stdafx.h"
#include "ui/uicommon.h"

namespace {
using ThisData = OptionToolForm::Data;
inline const ThisData& castData(const BaseForm::Data& data) {
  return static_cast<const ThisData&>(data);
}
inline ThisData& castData(BaseForm::Data& data) {
  return static_cast<ThisData&>(data);
}
}  // namespace

class OptionToolForm::Private {
 public:
  Private();
  ~Private();
  Ui::OptionToolForm ui;
};
OptionToolForm::Private::Private() : ui() {}
OptionToolForm::Private::~Private() {}

OptionToolForm::Data::Data()
    : viewer_name() {
  viewer_name.reserve(Data::kViewerCnt);
}

OptionToolForm::Data::Data(const std::vector<std::wstring>& viewer_name)
    : viewer_name(viewer_name) {
  this->viewer_name.reserve(Data::kViewerCnt);
}

OptionToolForm::OptionToolForm(QWidget* parent)
    : BaseForm(new Data(), parent), d_(new Private()) {
  d_->ui.setupUi(this);
}
OptionToolForm::~OptionToolForm() {}

int OptionToolForm::helpID() const {
  return kHelpTopicOptionTool;
}

void OptionToolForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void OptionToolForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  UI_SETTEXT(d_->ui.lineEdit_ViewerName1, QString(data_in.viewer_name[0]));
  UI_SETTEXT(d_->ui.lineEdit_ViewerName2, QString(data_in.viewer_name[1]));
  UI_SETTEXT(d_->ui.lineEdit_ViewerName3, QString(data_in.viewer_name[2]));
}

void OptionToolForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
  UI_TEXT(data_out.viewer_name[0], d_->ui.lineEdit_ViewerName1).toStdWString();
  UI_TEXT(data_out.viewer_name[1], d_->ui.lineEdit_ViewerName2).toStdWString();
  UI_TEXT(data_out.viewer_name[2], d_->ui.lineEdit_ViewerName3).toStdWString();
}

bool OptionToolForm::askFilename(QString& fname, const QString& path) {
  QString fname_tmp = QFileDialog::getOpenFileName(this, QString(), path, tr("実行可能ファイル (*.exe;*.com;*.bat);;すべてのファイル (*.*)"));
  bool ok = !fname_tmp.isNull();
  if (ok) { fname = fname_tmp; }
  return ok;
}

void OptionToolForm::onClick_toolButton_SelectViewer1() {
  QLineEdit& edit = *d_->ui.lineEdit_ViewerName1;
  if (QString fname{}; askFilename(fname, edit.text())) {
    edit.setText(fname);
  }
}

void OptionToolForm::onClick_toolButton_SelectViewer2() {
  QLineEdit& edit = *d_->ui.lineEdit_ViewerName2;
  if (QString fname{}; askFilename(fname, edit.text())) {
    edit.setText(fname);
  }
}

void OptionToolForm::onClick_toolButton_SelectViewer3() {
  QLineEdit& edit = *d_->ui.lineEdit_ViewerName3;
  if (QString fname{}; askFilename(fname, edit.text())) {
    edit.setText(fname);
  }
}
