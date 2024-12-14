#include "addabletreewidget.hpp"

#include <QStandardItemModel>

#include "ui_addabletreewidget.h"

#include "ui/uicommon.h"

class AddableTreeWidget::Private {
 public:
  Private();
  ~Private();
  Ui::AddableTreeWidget ui;
  QStandardItemModel* model;
};
AddableTreeWidget::Private::Private() : ui{}, model{nullptr} {}
AddableTreeWidget::Private::~Private() {}

AddableTreeWidget::AddableTreeWidget(QWidget* parent)
    : QWidget(parent), d_(new Private()) {
  d_->ui.setupUi(this);
  d_->model = new QStandardItemModel(parent);
  d_->ui.treeView->setModel(d_->model);
  updateEnabled();
}
AddableTreeWidget::~AddableTreeWidget() { delete d_->model; }

void AddableTreeWidget::setup(const QString& title,
                              QChar accel,
                              const QStringList& headers,
                              const QString& description) {
  UI_SETTITLE(d_->ui.groupBox, title);
  UI_SETTEXT(d_->ui.pushButton_Add,
             QString(d_->ui.pushButton_Add->text()).arg(accel));
  UI_SETTEXT(d_->ui.label_Description, description);
  if (description.isEmpty()) {
    d_->ui.label_Description->setFrameShape(QFrame::Shape::NoFrame);
  } else {
    d_->ui.label_Description->setFrameShape(QFrame::Shape::Box);
  }
  d_->model->setHorizontalHeaderLabels(headers);
}

void AddableTreeWidget::setData(const std::vector<std::vector<std::wstring>>& data) {
  for (const auto& v : data) { addData(v); }
}

void AddableTreeWidget::addData(const std::vector<std::wstring>& data) {
  d_->model->appendRow([&data](){
    QList<QStandardItem*> items{};
    items.reserve(data.size());
    for (const auto& str : data) {
      items.push_back([&str](){
        QStandardItem* item = new QStandardItem(QString(str));
        item->setData(QString(str));
        return item;
      }());
    }
    return items;
  }());
}

const std::vector<std::vector<std::wstring>>& AddableTreeWidget::data() const {
  static std::vector<std::vector<std::wstring>> ret{};
  int rc = d_->model->rowCount();
  ret.reserve(rc);
  for (int i = 0; i < rc; ++i) {
    ret.push_back([&i](QStandardItemModel* model) {
      std::vector<std::wstring> ret{};
      int cc = model->columnCount(model->index(i, 0));
      ret.reserve(cc);
      for (int j = 0; j < cc; ++j) {
        ret.push_back(model->index(i, j).data().toString().toStdWString());
      }
      return ret;
    }(d_->model));
  }
  return ret;
}

void AddableTreeWidget::updateEnabled() {
  UI_SETENABLED(d_->ui.pushButton_Del, d_->ui.treeView->currentIndex().isValid());
}

void AddableTreeWidget::onClick_pushButton_Add() {
  if (std::vector<std::wstring> data; askRowData(data)) {
    addData(data);
  }
}

void AddableTreeWidget::onClick_pushButton_Del() {
  d_->model->removeRow(d_->ui.treeView->currentIndex().row());
  updateEnabled();
}

void AddableTreeWidget::onClick_treeView() { updateEnabled(); }
