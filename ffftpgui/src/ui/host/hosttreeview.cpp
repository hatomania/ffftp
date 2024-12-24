﻿#include "hosttreeview.hpp"

#include <QStandardItem>
#include <QStandardItemModel>

#include "ffftp.h"
#include "stdafx.h"
#include "ui/uicommon.h"

namespace {

class HostItemModel : public QStandardItemModel {
 public:
  HostItemModel() = delete;
  explicit HostItemModel(QObject* parent = Q_NULLPTR);
  virtual ~HostItemModel();
  void update();

 private:
  void build(QStandardItem* node, ffftp_hostcontext_t* hc);
};
HostItemModel::HostItemModel(QObject* parent) : QStandardItemModel(parent) {
  update();
}
HostItemModel::~HostItemModel() {}

void HostItemModel::update() {
  clear();
  QStandardItem* root_node = invisibleRootItem();
  ffftp_hostcontext_t root_hc = ffftp_hostcontext_first();
  build(root_node, &root_hc);
}

void HostItemModel::build(QStandardItem* node, ffftp_hostcontext_t* hc) {
  if (!*hc) return;
  int first_level = ffftp_hostcontext_level(*hc);
  while (*hc) {
    QStandardItem* new_node = new QStandardItem(
        QIcon(ffftp_hostcontext_isgroup(*hc) ? kResImage_closedfolder16x16
                                             : kResImage_desktop16x16),
        QString::fromWCharArray(ffftp_hostcontext_name(*hc)));
    // ノードのユーザーデータとしてホストコンテキストを保存
    new_node->setData(QVariant::fromValue(*hc), kUserRole);
    node->appendRow(new_node);
    *hc = ffftp_hostcontext_next(*hc);
    if (*hc) {
      int next_level = ffftp_hostcontext_level(*hc);
      if (first_level < next_level) {
        build(new_node, hc);
      } else if (first_level > next_level) {
        break;
      }
    }
  }
}

HostItemModel* model_;

}  // namespace

HostTreeView::HostTreeView(QWidget* parent) : QTreeView(parent) {
  model_ = new HostItemModel(parent);
  setModel(model_);
}
HostTreeView::~HostTreeView() { delete model_; }

void HostTreeView::update() const { model_->update(); }

// 選択されているノードのユーザーデータ（＝ホストコンテキスト）を返す
ffftp_hostcontext_t HostTreeView::currentHostContext() const {
  ffftp_hostcontext_t ret = nullptr;
  QModelIndex index = currentIndex();
  if (index.isValid()) {
    ret = index.data(kUserRole).value<ffftp_hostcontext_t>();
  }
  return ret;
}

// 指定したホストコンテキストをユーザーデータに持つノードを選択状態にする
void HostTreeView::setCurrentIndex(ffftp_hostcontext_t hc) {
  QModelIndexList match_list =
      model_->match(model_->index(0, 0), kUserRole, QVariant::fromValue(hc), -1,
                    Qt::MatchExactly | Qt::MatchWrap | Qt::MatchRecursive);
  if (!match_list.isEmpty()) {
    QModelIndex& index_first = match_list.first();
    QTreeView::setCurrentIndex(index_first);
  }
}