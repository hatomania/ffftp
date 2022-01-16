#pragma once

#include <QtCore/QAbstractItemModel>

class MyFileSystemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit MyFileSystemModel(QWidget *parent = Q_NULLPTR);

public:
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

private slots:

private:
    class Private;
    Private* d_;
    Q_DISABLE_COPY(MyFileSystemModel)
};
