#pragma once

#include <QtWidgets/QWidget>

class HostSettingCharCodeForm : public QWidget
{
    Q_OBJECT

public:
    enum class Code {
        NOP,
        SJIS,
        JIS,
        EUC,
        UTF8,
        UTF8BOM,
        AUTO,
        SMBHEX,
        SMBCAP,
        UTF8HFSP,
    };

    struct Data {
        Code host_code;
        Code file_code;
        std::optional<bool> is_host_hkana_to_wkana;
        std::optional<bool> is_file_hkana_to_wkana;
        Data();
    };
    explicit HostSettingCharCodeForm(QWidget *parent = Q_NULLPTR);
    void setData(const Data& data) const;
    const Data& getData() const;
    void setDataAsDefault() const;

private slots:
    void onClick_radioButton_Host();
    void onClick_radioButton_File();

private:
    class Private;
    Private* d_;
    Q_DISABLE_COPY(HostSettingCharCodeForm)
};
