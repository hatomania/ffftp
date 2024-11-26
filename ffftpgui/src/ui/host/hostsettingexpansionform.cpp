#include "hostsettingexpansionform.hpp"
#include "ui_hostsettingexpansionform.h"
#include "stdafx.h"

namespace {
constexpr int kDefPort = 21;
}

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingExpansionForm::Private {
public:
    Private() {}
    ~Private() = default;
    Ui::HostSettingExpansionForm ui;
};

HostSettingExpansionForm::Data::Data()
    : use_firewall(false)
    , use_pasv_mode(true)
    , use_folder_samemove(false)
    , port(kDefPort)
    , account("")
    , timezone(21)
    , security(1)
    , cmd_when_connect("")
{}

HostSettingExpansionForm::HostSettingExpansionForm(QWidget* parent)
    : QWidget(parent), d_(new HostSettingExpansionForm::Private())
{
    d_->ui.setupUi(this);
    d_->ui.lineEdit_Port->setValidator(new QIntValidator(0, 0xFFFF, this));
    setDataAsDefault();
}

void HostSettingExpansionForm::setData(const Data& data) const {
    d_->ui.checkBox_UseFirewall->setChecked(data.use_firewall);
    d_->ui.checkBox_UserPASVMode->setChecked(data.use_pasv_mode);
    d_->ui.checkBox_UseFolderSameMove->setChecked(data.use_folder_samemove);
    d_->ui.lineEdit_Port->setText(QString::number(data.port));
    d_->ui.lineEdit_Account->setText(data.account);
    d_->ui.comboBox_Timezone->setCurrentIndex(data.timezone);
    d_->ui.comboBox_Security->setCurrentIndex(data.security);
    d_->ui.plainTextEdit_CmdWhenConnect->setPlainText(data.cmd_when_connect);
}

const HostSettingExpansionForm::Data& HostSettingExpansionForm::getData() const {
    static Data data;
    data.use_firewall = d_->ui.checkBox_UseFirewall->isChecked();
    data.use_pasv_mode = d_->ui.checkBox_UserPASVMode->isChecked();
    data.use_folder_samemove = d_->ui.checkBox_UseFolderSameMove->isChecked();
    data.port = d_->ui.lineEdit_Port->text().toInt();
    data.account = d_->ui.lineEdit_Account->text();
    data.timezone = d_->ui.comboBox_Timezone->currentIndex();
    data.security = d_->ui.comboBox_Security->currentIndex();
    data.cmd_when_connect = d_->ui.plainTextEdit_CmdWhenConnect->toPlainText();
    return data;
}

void HostSettingExpansionForm::setDataAsDefault() const {
    this->setData(Data());
}

void HostSettingExpansionForm::onClick_pushButton_StdPort() {
    d_->ui.lineEdit_Port->setText(QString::number(kDefPort));
}
