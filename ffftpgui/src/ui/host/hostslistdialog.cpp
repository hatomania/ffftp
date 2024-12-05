#include "hostslistdialog.hpp"

#include <QStandardItem>
#include <QStandardItemModel>

#include "ffftp.h"
#include "hostsettingsdialog.hpp"
#include "stdafx.h"
#include "ui_hostslistdialog.h"

class HostItem : public QStandardItem {
 private:
  void* hostcontext_;
  bool isgroup_;
};

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostsListDialog::Private {
 public:
  Private()
      : rootnode(nullptr),
        model(new QStandardItemModel()),
        connecting_host_index(-1),
        selected_host_index(-1) {}
  ~Private() { delete model; }
  void buildHostTreeView(int current = -1);
  Ui::HostsListDialogClass ui;
  QStandardItem* rootnode;
  QStandardItemModel* model;
  int connecting_host_index;
  int selected_host_index;
};

static QStandardItem* _createHostTreeViewItem(const hostcontext_t hc) {
  return new QStandardItem(
      QIcon(ffftp_hostcontext_isgroup(hc) ? kResImage_closedfolder16x16
                                          : kResImage_desktop16x16),
#ifdef _DEBUG
      QString(R"([%1,%2]"%3")")
          .arg(ffftp_hostcontext_getindex(hc))
          .arg(ffftp_hostcontext_getlevel(hc))
          .arg(QString::fromWCharArray(ffftp_hostcontext_getname(hc)))
#else
      QString::fromWCharArray(ffftp_hostcontext_getname(hc))
#endif  // _DEBUG
  );
}

static void _buildHostTreeViewNode(hostcontext_t& hc, int level,
                                   QStandardItem* node) {
  QStandardItem* prevone = nullptr;
  while (hc) {
    if (int l = ffftp_hostcontext_getlevel(hc); l == level) {
      prevone = _createHostTreeViewItem(hc);
      prevone->setData(ffftp_hostcontext_getindex(hc));
      node->appendRow(prevone);
      hc = ffftp_hostcontext_next(hc);
    } else if (l > level) {
      Q_ASSERT(prevone);
      _buildHostTreeViewNode(hc, l, prevone);
      if (hc) {
        prevone = _createHostTreeViewItem(hc);
        prevone->setData(ffftp_hostcontext_getindex(hc));
        node->appendRow(prevone);
        hc = ffftp_hostcontext_next(hc);
      }
    } else {
      break;
    }
  }
}

static struct _FindModelIndexRet {
  bool b;
  QModelIndex m;
} _findModelIndex(const QStandardItemModel* model, const QModelIndex& mkey,
                  const QVariant& data) {
  _FindModelIndexRet _r{false, QModelIndex()};
  for (int i = 0; model->hasIndex(i, 0, mkey); ++i) {
    qDebug() << __FUNCTION__ << QString("try i=%1").arg(i);
    _r.m = model->index(i, 0, mkey);
    qDebug() << "finding data... got data="
             << model->itemFromIndex(_r.m)->data() << "finding data=" << data;
    if (model->itemFromIndex(_r.m)->data() == data) {
      qDebug() << "found data! data=" << data;
      _r.b = true;
      break;
    } else if (model->hasChildren(_r.m)) {
      qDebug() << "found children!";
      _r = _findModelIndex(model, _r.m, data);
      if (_r.b) break;
    }
  }
  return _r;
}

void HostsListDialog::Private::buildHostTreeView(int current) {
  ui.treeView_Host->setModel(nullptr);
  delete model;
  model = new QStandardItemModel();
  rootnode = model->invisibleRootItem();

  hostcontext_t hc = ffftp_hostcontext_first();
  _buildHostTreeViewNode(hc, 0, rootnode);

  // rootNode->appendRow(new QStandardItem(QIcon(":/resource/disconnect.png"),
  // QString("----------"))); for (hostcontext_t hc = ffftp_hostcontext_first();
  // hc; hc = ffftp_hostcontext_next(hc)) {
  //     rootNode->appendRow(
  //         new QStandardItem(
  //             QIcon(ffftp_hostcontext_isgroup(hc) ?
  //             ":/resource/closedfolder16x16.png" :
  //             ":/resource/desktop16x16.png"),
  //             QString("[%1]%2").arg(ffftp_hostcontext_getlevel(hc)).arg(QString::fromWCharArray(ffftp_hostcontext_getname(hc)))
  //         )
  //     );
  // }

  // defining a couple of items
  // QStandardItem* americaItem = new QStandardItem("America");
  // americaItem->setIcon(QIcon(":/resource/connect.png"));
  // QStandardItem* mexicoItem = new QStandardItem("Canada");
  // QStandardItem* usaItem = new QStandardItem("USA");
  // QStandardItem* bostonItem = new QStandardItem("Boston");
  // QStandardItem* europeItem = new QStandardItem("Europe");
  // QStandardItem* italyItem = new QStandardItem("Italy");
  // QStandardItem* romeItem = new QStandardItem("Rome");
  // romeItem->setIcon(QIcon(":/resource/quickconnect.png"));
  // QStandardItem* veronaItem = new QStandardItem("Verona");

  // building up the hierarchy
  // rootNode->appendRow(americaItem);
  // rootNode->appendRow(europeItem);
  // americaItem->appendRow(mexicoItem);
  // americaItem->appendRow(usaItem);
  // usaItem->appendRow(bostonItem);
  // europeItem->appendRow(italyItem);
  // italyItem->appendRow(romeItem);
  // italyItem->appendRow(veronaItem);

  // register the model
  ui.treeView_Host->setModel(model);
  // d_->ui.treeView_Host->expandAll();

  // 選択状態を復元
  // 他に開いていたグループは閉じてしまう。開いたままのグループは開いたままにする処理を追加するには
  // UP-DOWNで変化するindexで頑張るより、グループ作成時に一意のIDを割り振ってそのIDを使ったほうが堅実
  if (current >= 0) {
    // TreeViewを作り直しても選択状態を維持するため適切なindex(=current)を探す
    _FindModelIndexRet r = _findModelIndex(model, QModelIndex(), current);
    Q_ASSERT(r.b);  // indexが見つからないはずはない
    ui.treeView_Host->setCurrentIndex(r.m);
  }
}

HostsListDialog::HostsListDialog(QWidget* parent)
    : QDialog(parent), d_(new HostsListDialog::Private()) {
  d_->ui.setupUi(this);
  // TODO: リストが非選択の時、ボタンを押せなくする
  d_->buildHostTreeView();
}

void HostsListDialog::accept() {
  qDebug()
      << __FUNCTION__ << "called! index="
      << d_->model->itemFromIndex(d_->ui.treeView_Host->currentIndex())->data();
  d_->connecting_host_index =
      d_->model->itemFromIndex(d_->ui.treeView_Host->currentIndex())
          ->data()
          .toInt();
  QDialog::accept();
}

int HostsListDialog::connectingHostIndex() { return d_->connecting_host_index; }

void HostsListDialog::onClick_pushButton_NewHost() {
  qDebug() << __FUNCTION__ << "called!";
  hostdata hdata;
  ffftp_hostcontext_hostdata_default(&hdata);
  if (showSettingDialog(hdata)) {
    int insert_index =
        d_->selected_host_index <= 0 ? 0 : d_->selected_host_index;
    ffftp_hostcontext_new(insert_index, &hdata);
    d_->buildHostTreeView(ffftp_hostcontext_getcurrentindex());
  }
}

void HostsListDialog::onClick_pushButton_NewGroup() {
  qDebug() << __FUNCTION__ << "called!";
}

void HostsListDialog::onClick_pushButton_Mod() {
  qDebug() << __FUNCTION__ << "called!";
  hostdata hdata;
  ffftp_hostcontext_hostdata(d_->selected_host_index, &hdata);
  if (showSettingDialog(hdata)) {
    int insert_index =
        d_->selected_host_index <= 0 ? 0 : d_->selected_host_index;
    // TODO: newのまま
    ffftp_hostcontext_new(insert_index, &hdata);
    d_->buildHostTreeView(ffftp_hostcontext_getcurrentindex());
  }
}

void HostsListDialog::onClick_pushButton_Copy() {
  qDebug() << __FUNCTION__ << "called!";
}

void HostsListDialog::onClick_pushButton_Del() {
  qDebug() << __FUNCTION__ << "called!";
}

void HostsListDialog::onClick_pushButton_Up() {
  qDebug() << __FUNCTION__ << "called!";
  int c = ffftp_hostcontext_up(
      d_->model->itemFromIndex(d_->ui.treeView_Host->currentIndex())
          ->data()
          .toInt());
  qDebug() << "c=" << c;
  HostsListDialog::d_->buildHostTreeView(c);
}

void HostsListDialog::onClick_pushButton_Down() {
  qDebug() << __FUNCTION__ << "called!";
  int c = ffftp_hostcontext_down(
      d_->model->itemFromIndex(d_->ui.treeView_Host->currentIndex())
          ->data()
          .toInt());
  qDebug() << "c=" << c;
  HostsListDialog::d_->buildHostTreeView(c);
}

void HostsListDialog::onClick_pushButton_Default() {
  qDebug() << __FUNCTION__ << "called!";
}

void HostsListDialog::onClick_pushButton_Help() {
  qDebug() << __FUNCTION__ << "called!";
}

void HostsListDialog::selectedHost(const QModelIndex& index) {
  qDebug() << __FUNCTION__
           << "called! data=" << d_->model->itemFromIndex(index)->data();
  d_->selected_host_index = d_->model->itemFromIndex(index)->data().toInt();
}

bool HostsListDialog::showSettingDialog(hostdata& in_out_data) /* const */ {
  qDebug() << __FUNCTION__ << "called!";
  bool ret = false;
  HostSettingsDialog setting_dlg(in_out_data, this);// const付けるとthisもconst型になり型不一致でエラー
  if (setting_dlg.exec() == QDialog::Accepted) {
    setting_dlg.hostData(in_out_data);
    ret = true;
  }
  return ret;
}
