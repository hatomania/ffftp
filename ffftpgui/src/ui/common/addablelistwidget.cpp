#include "addablelistwidget.hpp"

#include <QInputDialog>
#include <QStandardItemModel>

#include "ui_addablelistwidget.h"

#include "ffftp.h"
#include "stdafx.h"
#include "ui/uicommon.h"

class AddableListWidget::Private {
 public:
  Private();
  ~Private();
  Ui::AddableListWidget ui;
  QStandardItemModel* model;
};
AddableListWidget::Private::Private() : ui{}, model{nullptr} {}
AddableListWidget::Private::~Private() {}

AddableListWidget::AddableListWidget(QWidget* parent)
    : QWidget(parent), d_(new Private()) {
  d_->ui.setupUi(this);
  d_->model = new QStandardItemModel(parent);
  d_->ui.listView->setModel(d_->model);
  updateEnabled();
}
AddableListWidget::~AddableListWidget() {}

void AddableListWidget::init(const QString& title, QChar accel, const QString& description) {
  UI_SETTITLE(d_->ui.groupBox, title);
  UI_SETTEXT(d_->ui.pushButton_Add, QString(d_->ui.pushButton_Add->text()).arg(accel));
  UI_SETTEXT(d_->ui.label_Description, description);
  if (description.isEmpty()) {
    d_->ui.label_Description->setFrameShape(QFrame::Shape::NoFrame);
  } else {
    d_->ui.label_Description->setFrameShape(QFrame::Shape::Box);
  }
}

void AddableListWidget::setData(const QStringList& data) {
  d_->model->clear();
  for (const auto& str : data) {
    addData(str);
  }
}

const QStringList& AddableListWidget::data() const {
  static QStringList data;
  int rc = d_->model->rowCount();
  data.clear();
  data.reserve(rc);
  for (int i = 0; i < rc; ++i) {
    data.push_back(d_->model->index(i, 0).data().toString());
  }
  return data;
}

void AddableListWidget::setData(const std::vector<std::wstring>& data) {
  setData(QStringList({data.begin(), data.end()}));
}

const std::vector<std::wstring>& AddableListWidget::toVectorStdWString() const {
  static std::vector<std::wstring> ret;
  const QStringList& qdata{data()};
  ret.clear();
  ret.reserve(qdata.size());
  for (const auto& str : qdata) {
    ret.push_back(str.toStdWString());
  }
  return ret;
}

void AddableListWidget::updateEnabled() {
  UI_SETENABLED(d_->ui.pushButton_Del, d_->ui.listView->currentIndex().isValid());
}

bool AddableListWidget::askData(QString& fname) {
  bool ok = false;
  fname = QInputDialog::getText(
    parentWidget(), kStringFileName, kStringFileNameAccess,
    QLineEdit::Normal, kEmptyString, &ok);
  return ok;
}

void AddableListWidget::addData(const QString& fname) {
  d_->model->appendRow([&fname]() {
    QStandardItem* item = new QStandardItem(fname);
    item->setData(fname);
    return item;
  }());
}

void AddableListWidget::onClick_pushButton_Add() {
  if (QString fname; askData(fname)) {
    addData(fname);
  }
}

void AddableListWidget::onClick_pushButton_Del() {
  d_->model->removeRow(d_->ui.listView->currentIndex().row());
  updateEnabled();
}

void AddableListWidget::onClick_listView() { updateEnabled(); }
