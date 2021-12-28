#include "hostslistdialog.hpp"
#include "ui_hostslistdialog.h"
#include "hostsettingsdialog.hpp"
#include "stdafx.h"

class HostItem : public QStandardItem {
private:
    void* hostcontext_;
    bool isgroup_;
};

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostsListDialog::Private {
public:
    Private() : model(new QStandardItemModel()) {}
    ~Private() { delete model; }
    Ui::HostsListDialogClass ui;
    QStandardItemModel* model;
};

static QStandardItem* _createHostTreeView(const hostcontext_t hc) {
    return new QStandardItem(
        QIcon(ffftp_hostcontext_isgroup(hc) ? kResImage_closedfolder16x16 : kResImage_desktop16x16),
#ifdef _DEBUG
        QString("[%1]%2").arg(ffftp_hostcontext_getlevel(hc)).arg(QString::fromWCharArray(ffftp_hostcontext_getname(hc)))
#else
        QString::fromWCharArray(ffftp_hostcontext_getname(hc))
#endif // _DEBUG
    );
}

static void _buildHostTreeView(hostcontext_t& hc, int level, QStandardItem* node) {
    QStandardItem* prevone = nullptr;
    while (hc) {
        if (int l = ffftp_hostcontext_getlevel(hc); l == level) {
            prevone = _createHostTreeView(hc);
            node->appendRow(prevone);
            hc = ffftp_hostcontext_next(hc);
        }
        else if (l > level) {
            Q_ASSERT(prevone);
            _buildHostTreeView(hc, l, prevone);
            if (hc) {
                prevone = _createHostTreeView(hc);
                node->appendRow(prevone);
                hc = ffftp_hostcontext_next(hc);
            }
        }
        else {
            break;
        }
    }
}

HostsListDialog::HostsListDialog(QWidget* parent)
    : QDialog(parent), d_(new HostsListDialog::Private())
{
    d_->ui.setupUi(this);
    QStandardItem* rootNode = d_->model->invisibleRootItem();

    hostcontext_t hc = ffftp_hostcontext_first();
    _buildHostTreeView(hc, 0, rootNode);

    //rootNode->appendRow(new QStandardItem(QIcon(":/resource/disconnect.png"), QString("----------")));
    //for (hostcontext_t hc = ffftp_hostcontext_first(); hc; hc = ffftp_hostcontext_next(hc)) {
    //    rootNode->appendRow(
    //        new QStandardItem(
    //            QIcon(ffftp_hostcontext_isgroup(hc) ? ":/resource/closedfolder16x16.png" : ":/resource/desktop16x16.png"),
    //            QString("[%1]%2").arg(ffftp_hostcontext_getlevel(hc)).arg(QString::fromWCharArray(ffftp_hostcontext_getname(hc)))
    //        )
    //    );
    //}

    //defining a couple of items
    //QStandardItem* americaItem = new QStandardItem("America");
    //americaItem->setIcon(QIcon(":/resource/connect.png"));
    //QStandardItem* mexicoItem = new QStandardItem("Canada");
    //QStandardItem* usaItem = new QStandardItem("USA");
    //QStandardItem* bostonItem = new QStandardItem("Boston");
    //QStandardItem* europeItem = new QStandardItem("Europe");
    //QStandardItem* italyItem = new QStandardItem("Italy");
    //QStandardItem* romeItem = new QStandardItem("Rome");
    //romeItem->setIcon(QIcon(":/resource/quickconnect.png"));
    //QStandardItem* veronaItem = new QStandardItem("Verona");

    //building up the hierarchy
    //rootNode->appendRow(americaItem);
    //rootNode->appendRow(europeItem);
    //americaItem->appendRow(mexicoItem);
    //americaItem->appendRow(usaItem);
    //usaItem->appendRow(bostonItem);
    //europeItem->appendRow(italyItem);
    //italyItem->appendRow(romeItem);
    //italyItem->appendRow(veronaItem);

    //register the model
    d_->ui.treeView_Host->setModel(d_->model);
    //d_->ui.treeView_Host->expandAll();
}

void HostsListDialog::onClick_pushButton_NewHost() {
    qDebug() << __FUNCTION__ << "called!";
    HostSettingsDialog(this).exec();
}

void HostsListDialog::onClick_pushButton_NewGroup() {
    qDebug() << __FUNCTION__ << "called!";
}

void HostsListDialog::onClick_pushButton_Mod() {
    qDebug() << __FUNCTION__ << "called!";
}

void HostsListDialog::onClick_pushButton_Copy() {
    qDebug() << __FUNCTION__ << "called!";
}

void HostsListDialog::onClick_pushButton_Del() {
    qDebug() << __FUNCTION__ << "called!";
}

void HostsListDialog::onClick_pushButton_Up() {
    qDebug() << __FUNCTION__ << "called!";
}

void HostsListDialog::onClick_pushButton_Down() {
    qDebug() << __FUNCTION__ << "called!";
}

void HostsListDialog::onClick_pushButton_Default() {
    qDebug() << __FUNCTION__ << "called!";
}

void HostsListDialog::onClick_pushButton_Help() {
    qDebug() << __FUNCTION__ << "called!";
}

void HostsListDialog::onClick_pushButton_Connect() {
    qDebug() << __FUNCTION__ << "called!";
}

void HostsListDialog::selectedHost(const QModelIndex& index) {
    qDebug() << __FUNCTION__ << "called!";
}
