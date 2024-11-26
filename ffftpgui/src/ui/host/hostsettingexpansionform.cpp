#include "hostsettingexpansionform.hpp"
#include "ui_hostsettingexpansionform.h"
#include "stdafx.h"

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostSettingExpansionForm::Private {
public:
    Private() {}
    ~Private() {}
    Ui::HostSettingExpansionForm ui;
    HostSettingExpansionForm::Data data;
};

HostSettingExpansionForm::Data::Data() {}

HostSettingExpansionForm::HostSettingExpansionForm(QWidget* parent)
    : QWidget(parent), d_(new HostSettingExpansionForm::Private())
{
    d_->ui.setupUi(this);
}

void HostSettingExpansionForm::setData(const Data& data) const {
}

const HostSettingExpansionForm::Data& HostSettingExpansionForm::getData() const {
//    static Data data;
    return d_->data;
}

void HostSettingExpansionForm::setDataAsDefault() const {
    this->setData(Data());
}
