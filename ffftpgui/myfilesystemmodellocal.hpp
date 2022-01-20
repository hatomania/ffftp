#pragma once

#include "myfilesystemmodel.hpp"

class MyDirLocal : public MyDir {
public:
    explicit MyDirLocal(const QString& path, bool isshowndot);
    QVector<QVector<QVariant>> fileList() const;
private:
    class Private;
    Private* d_;
};

class MyFileSystemModelLocal : public MyFileSystemModel
{
    Q_OBJECT

public:
    explicit MyFileSystemModelLocal(QWidget *parent = Q_NULLPTR, const QString& path = "", bool isshowndot = false);

protected:
    const QVector<QString>& headerList() const;
    QVariant data(const QVector<QVariant>& fi, int column, int role) const;

public:
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

private:
    class Private;
    Private* d_;
    Q_DISABLE_COPY(MyFileSystemModelLocal)
};
