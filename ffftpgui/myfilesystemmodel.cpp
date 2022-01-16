#include "myfilesystemmodel.hpp"
#include "stdafx.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class MyFileSystemModel::Private {
public:
    Private() {}
    ~Private() {}
    QFileInfoList ifinfo;
};

static const QVector<QString> _headerdata = {
    kStringName,
    kStringDate,
    kStringSize,
    kStringExtension,
    kStringPermission,
    kStringOwner,
};

MyFileSystemModel::MyFileSystemModel(QWidget* parent)
    : QAbstractItemModel(parent), d_(new MyFileSystemModel::Private()) {
    QDir dir(QDir::homePath());
    d_->ifinfo = dir.entryInfoList();
}

// ↓なぜか各種純粋仮想関数の実装が何度もコールされる
// スプリッタやウィンドウのリサイズ等がとても重くなる
// qDebug()アンコメントするとメッセージが表示されまくる
// 実装が間違っているのか原因はよく分からない
// QStandardItemModelでちまちま構築するべきなのか

int MyFileSystemModel::columnCount(const QModelIndex& parent) const {
    //qDebug() << __FUNCTION__ << " called. _headerdata.size()=" << _headerdata.size();
    if (parent != QModelIndex()) return 0; // ルートでなければ0
    return _headerdata.size();
}

QVariant MyFileSystemModel::data(const QModelIndex& index, int role) const {
    //qDebug() << __FUNCTION__ << " called. index=" << index << " role = " << role;
    QVariant _r = QVariant();
    QFileInfo* info = static_cast<QFileInfo*>(index.internalPointer());
    if (index.isValid() && index != QModelIndex()) {
        if (role == Qt::TextAlignmentRole && index.column() == 2) _r = Qt::AlignRight;
        else if (role == Qt::DecorationRole && index.column() == 0) {
            _r = info->isDir() ? QIcon(kResImage_closedfolder16x16) : QIcon(kResImage_desktop16x16);
        }
        else if (role == Qt::DisplayRole) {
            switch (index.column()) {
            case 0: _r = info->fileName(); break;
            case 1: _r = info->fileTime(QFileDevice::FileModificationTime); break;
            case 2: _r = info->isDir() ? QVariant("<DIR>") : QVariant(info->size()); break;
            case 3: _r = info->suffix(); break;
            case 4: _r = kEmptyString; break;
            case 5: _r = kEmptyString; break;
            }
        }
    }
    return _r;
}

QVariant MyFileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const {
    //qDebug() << __FUNCTION__ << " called. section=" << section << " orientation=" << orientation << " role=" << role;
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return QVariant();
    Q_ASSERT(_headerdata.size() >= section);
    return QVariant(_headerdata[section]);
}

QModelIndex MyFileSystemModel::index(int row, int column, const QModelIndex& parent) const {
    if (parent.isValid()) return QModelIndex();
    return createIndex(row, column, &d_->ifinfo[row]);
}

QModelIndex MyFileSystemModel::parent(const QModelIndex& index) const {
    return QModelIndex();
}

int MyFileSystemModel::rowCount(const QModelIndex& parent) const {
    if (parent != QModelIndex()) return 0; // ルートでなければ0
    return d_->ifinfo.size();
}
