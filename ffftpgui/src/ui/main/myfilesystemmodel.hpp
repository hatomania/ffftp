#pragma once

#include <QtCore/QAbstractItemModel>
#include <QtCore/QFileInfo>

class MyDirList {
 public:
  explicit MyDirList();
};

class MyDir {
 public:
  explicit MyDir(const QString& path, bool isshowndot);
  void setShowDot(bool isshowndot);
  bool showDot() const;
  void setSorting(int flags);
  const QString& currentPath() const;
  virtual QString oneUpPath() = 0;
  virtual const QVector<MyDirList*>& fileList() const = 0;

 protected:
  QString path_;
  bool isshowndot_;
  int sortflags_;

 private:
  class Private;
  Private* d_;
};

class MyFileSystemModel : public QAbstractItemModel {
  Q_OBJECT

 public:
  explicit MyFileSystemModel(QWidget* parent = Q_NULLPTR,
                             const QString& path = "", bool isshowndot = false);
  void setShowDot(bool isshowndot);
  bool showDot() const;
  virtual QString fullPath(const QModelIndex& index) const = 0;
  virtual bool isDir(const QModelIndex& index) const = 0;

 public:
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  QModelIndex index(int row, int column,
                    const QModelIndex& parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex& index) const override;
  int rowCount(const QModelIndex& parent = QModelIndex()) const override;

 protected:
  virtual const QVector<QString>& headerList() const = 0;
  virtual QVariant data(const MyDirList& fi, int column, int role) const = 0;
  MyDir* dir_;
  QVector<MyDirList*> fl_;

 private:
  class Private;
  Private* d_;
  Q_DISABLE_COPY(MyFileSystemModel)
};
