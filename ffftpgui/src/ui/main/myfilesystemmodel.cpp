#include "myfilesystemmodel.hpp"

#include "stdafx.h"

MyDirList::MyDirList() {}

class MyDir::Private {
 public:
  Private() {}
  ~Private() {}
};

MyDir::MyDir(const QString& path, bool isshowndot)
    : path_(path), isshowndot_(isshowndot), d_(new MyDir::Private()) {}
void MyDir::setShowDot(bool isshowndot) { isshowndot_ = isshowndot; }
bool MyDir::showDot() const { return isshowndot_; }
void MyDir::setSorting(int flags) { sortflags_ = flags; }
const QString& MyDir::currentPath() const { return path_; }

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class MyFileSystemModel::Private {
 public:
  Private() {}
  ~Private() {}
  // QDir* dir;
  // QFileInfoList ifinfo;
};

// static const QVector<QString> _headerdata = {
//     kStringName,
//     kStringDate,
//     kStringSize,
//     kStringExtension,
//     kStringPermission,
//     kStringOwner,
// };

MyFileSystemModel::MyFileSystemModel(QWidget* parent, const QString& path,
                                     bool isshowndot)
    : QAbstractItemModel(parent), d_(new MyFileSystemModel::Private()) {}

void MyFileSystemModel::setShowDot(bool isshowndot) {
  dir_->setShowDot(isshowndot);
  fl_ = dir_->fileList();
  emit dataChanged(QModelIndex(), QModelIndex());
  emit layoutChanged();
}

bool MyFileSystemModel::showDot() const { return dir_->showDot(); }

// ↓なぜか各種純粋仮想関数の実装が何度もコールされる
// スプリッタやウィンドウのリサイズ等がとても重くなる
// qDebug()アンコメントするとメッセージが表示されまくる
// 実装が間違っているのか原因はよく分からない
// QStandardItemModelでちまちま構築するべきなのか

int MyFileSystemModel::columnCount(const QModelIndex& parent) const {
  // qDebug() << __FUNCTION__ << " called. _headerdata.size()=" <<
  // _headerdata.size();
  if (parent != QModelIndex()) return 0;  // ルートでなければ0
  return headerList().size();
}

QVariant MyFileSystemModel::data(const QModelIndex& index, int role) const {
  // qDebug() << __FUNCTION__ << " called. index=" << index << " role = " <<
  // role;
  QVariant _r = QVariant();
  if (index.isValid() && index != QModelIndex()) {
    MyDirList* info = static_cast<MyDirList*>(index.internalPointer());
    _r = data(*info, index.column(), role);
  }
  return _r;
}

QVariant MyFileSystemModel::headerData(int section, Qt::Orientation orientation,
                                       int role) const {
  // qDebug() << __FUNCTION__ << " called. section=" << section << "
  // orientation=" << orientation << " role=" << role;
  if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
    return QVariant();
  Q_ASSERT(headerList().size() >= section);
  return QVariant(headerList()[section]);
}

QModelIndex MyFileSystemModel::index(int row, int column,
                                     const QModelIndex& parent) const {
  if (parent.isValid()) return QModelIndex();
  Q_ASSERT(fl_.size() > row);
  return createIndex(
      row, column,
      fl_[row]);  // 第3引数について、&fl_[row]とするのは間違い。実体がポインタなのでそのまま実体を渡す
}

QModelIndex MyFileSystemModel::parent(const QModelIndex& index) const {
  return QModelIndex();
}

int MyFileSystemModel::rowCount(const QModelIndex& parent) const {
  if (parent != QModelIndex()) return 0;  // ルートでなければ0
  return fl_.size();
}
