#include "hostsettingdialupform.hpp"
#include "ui_hostsettingdialupform.h"
#include "stdafx.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingDialupForm::Private {
public:
    Private() {}
    ~Private() = default;
    Ui::HostSettingDialupForm ui;
};

HostSettingDialupForm::Data::Data()
    : use_dialup(false)
    , dial_entry(0)
    , redial(false)
    , confirm_redial(true)
{}

HostSettingDialupForm::HostSettingDialupForm(QWidget* parent)
    : QWidget(parent), d_(new HostSettingDialupForm::Private())
{
    d_->ui.setupUi(this);
    setDataAsDefault();
}

void HostSettingDialupForm::setData(const Data& data) const {
    d_->ui.groupBox_UseDialup->setChecked(data.use_dialup);
    d_->ui.comboBox_DialupEntry->setCurrentIndex(data.dial_entry);
    d_->ui.groupBox_UseRedial->setChecked(data.redial);
    d_->ui.checkBox_ConfirmRedial->setChecked(data.confirm_redial);
}

const HostSettingDialupForm::Data& HostSettingDialupForm::getData() const {
    static Data data;
    data.use_dialup = d_->ui.groupBox_UseDialup->isChecked();
    data.dial_entry = d_->ui.comboBox_DialupEntry->currentIndex();
    data.redial = d_->ui.groupBox_UseRedial->isChecked();
    data.confirm_redial = d_->ui.checkBox_ConfirmRedial->isChecked();
    return data;
}

void HostSettingDialupForm::setDataAsDefault() const {
    this->setData(Data());
}
