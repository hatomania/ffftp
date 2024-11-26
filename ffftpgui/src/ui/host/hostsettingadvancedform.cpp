#include "hostsettingadvancedform.hpp"
#include "ui_hostsettingadvancedform.h"
#include "stdafx.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingAdvancedForm::Private {
public:
    Private() {}
    ~Private() {}
    Ui::HostSettingAdvancedForm ui;
    HostSettingAdvancedForm::Data data;
};

HostSettingAdvancedForm::Data::Data() {}

HostSettingAdvancedForm::HostSettingAdvancedForm(QWidget* parent)
    : QWidget(parent), d_(new HostSettingAdvancedForm::Private())
{
    d_->ui.setupUi(this);
}

void HostSettingAdvancedForm::setData(const Data& data) const {
}

const HostSettingAdvancedForm::Data& HostSettingAdvancedForm::getData() const {
//    static Data data;
    return d_->data;
}

void HostSettingAdvancedForm::setDataAsDefault() const {
    this->setData(Data());
}
