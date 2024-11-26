#pragma once

#include <QtWidgets/QWidget>

class HostSettingCharCodeForm : public QWidget
{
    Q_OBJECT

public:
    struct Data {
        Data();
    };
    explicit HostSettingCharCodeForm(QWidget *parent = Q_NULLPTR);
    void setData(const Data& data) const;
    const Data& getData() const;
    void setDataAsDefault() const;

private slots:

private:
    class Private;
    Private* d_;
    Q_DISABLE_COPY(HostSettingCharCodeForm)
};
