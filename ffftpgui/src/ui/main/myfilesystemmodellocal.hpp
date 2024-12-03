#pragma once

#include "myfilesystemmodel.hpp"

class MyDirListLocal : public MyDirList {
 public:
  explicit MyDirListLocal(const QString& fullpath, const QString& filename,
                          const QDateTime& time, const qint64& size,
                          const QString& ext);
  QString fullpath;
  QString filename;
  QDateTime time;
  qint64 size;
  QString ext;
};

class MyDirLocal : public MyDir {
 public:
  explicit MyDirLocal(const QString& path, bool isshowndot);
  QString oneUpPath() override;
  const QVector<MyDirList*>& fileList() const override;

 private:
  class Private;
  Private* d_;
};

class MyFileSystemModelLocal : public MyFileSystemModel {
  Q_OBJECT

 public:
  explicit MyFileSystemModelLocal(QWidget* parent = Q_NULLPTR,
                                  const QString& path = "",
                                  bool isshowndot = false);
  QString fullPath(const QModelIndex& index) const override;
  bool isDir(const QModelIndex& index) const override;
  QString oneUpPath();

 protected:
  const QVector<QString>& headerList() const override;
  QVariant data(const MyDirList& fi, int column, int role) const override;

 public:
  void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

 private:
  class Private;
  Private* d_;
  Q_DISABLE_COPY(MyFileSystemModelLocal)
};
