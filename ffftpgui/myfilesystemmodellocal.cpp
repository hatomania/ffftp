#include "myfilesystemmodellocal.hpp"
#include "stdafx.h"

enum SortFlag {
    Ascending = 0x00,
    Descending = 0xF0,
    Name = 0x00,
    Time = 0x02,
    Size = 0x04,
    Type = 0x08,
};
class MyDirLocal::Private {
public:
    Private() {}
    ~Private() {}
    QDir* dir;
    QFileInfoList ifinfo;
};
MyDirLocal::MyDirLocal(const QString& path, bool isshowndot)
    : MyDir(path, isshowndot), d_(new MyDirLocal::Private()) {
    d_->dir = new QDir(path, "*", QDir::Name | QDir::DirsFirst, QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
    d_->ifinfo = d_->dir->entryInfoList();
}
QVector<QVector<QVariant>> MyDirLocal::fileList() const {
    QDir::SortFlags sflags = QDir::DirsFirst;
    if ((sortflags_ & Descending) > 0) sflags |= QDir::Reversed;
    if ((sortflags_ & Name) > 0) sflags |= QDir::Name;
    else if ((sortflags_ & Time) > 0) sflags |= QDir::Time;
    else if ((sortflags_ & Size) > 0) sflags |= QDir::Size;
    else if ((sortflags_ & Type) > 0) sflags |= QDir::Type;
    d_->dir->setSorting(sflags);
    QVector<QVector<QVariant>> _r;
    d_->ifinfo = d_->dir->entryInfoList();

    for (QFileInfo& f : d_->ifinfo) {
        Q_ASSERT(f.fileName().size() > 0);
        if (!isshowndot_ && f.fileName().front() == '.') continue;
        _r.push_back(QVector<QVariant>({
            f.fileName(),
            f.fileTime(QFileDevice::FileModificationTime),
            f.isDir() ? -1 : f.size(),
            f.suffix()
        }));
    }
    return _r;
}

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class MyFileSystemModelLocal::Private {
public:
    Private() {}
    ~Private() {}
};

static const QVector<QString> _headerdata = {
    kStringName,
    kStringDate,
    kStringSize,
    kStringExtension,
};

MyFileSystemModelLocal::MyFileSystemModelLocal(QWidget* parent, const QString& path, bool isshowndot)
    : MyFileSystemModel(parent, path), d_(new MyFileSystemModelLocal::Private()) {
    dir_ = new MyDirLocal(path, isshowndot);
    fl_ = dir_->fileList();
}

const QVector<QString>& MyFileSystemModelLocal::headerList() const {
    return _headerdata;
}

QVariant MyFileSystemModelLocal::data(const QVector<QVariant>& fi, int column, int role) const {
    Q_ASSERT(fi.size() == 4);
    QVariant _r = QVariant();
    if (role == Qt::TextAlignmentRole && column == 2) _r = Qt::AlignRight;
    else if (role == Qt::DecorationRole && column == 0) {
        _r = fi[2].toInt() < 0 ? QIcon(kResImage_closedfolder16x16) : QIcon(kResImage_cleanfile16x16);
    }
    else if (role == Qt::DisplayRole) {
        switch (column) {
        case 0: _r = fi[0].toString(); break;
        case 1: _r = fi[1].toDateTime(); break;
        case 2: _r = fi[2].toInt() < 0 ? QVariant("<DIR>") : QVariant(fi[2].toInt()); break;
        case 3: _r = fi[3].toString(); break;
        }
    }
    return _r;
}

void MyFileSystemModelLocal::sort(int column, Qt::SortOrder order) {
    qDebug() << __FUNCTION__ << " called. column=" << column << " SortOrder=" << order;
    int sflag = Ascending;
    if (order == Qt::DescendingOrder) sflag |= Descending;
    switch (column) {
    case 0: sflag |= Name; break;
    case 1: sflag |= Time; break;
    case 2: sflag |= Size; break;
    case 3: sflag |= Type; break;
    }
    dir_->setSorting(sflag);
    fl_ = dir_->fileList();
    // ソート後にモデルに接続しているGUIを更新するために必要
    // https://stackoverflow.com/questions/18854753/qtableview-sorting-updates-slowly
    //emit dataChanged(QModelIndex(), QModelIndex()); // 落ちる
    emit layoutChanged();
}
