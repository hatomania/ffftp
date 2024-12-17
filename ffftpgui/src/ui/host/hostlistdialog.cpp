#include "hostlistdialog.hpp"

#include <QInputDialog>
#include <QMessageBox>
#include <QStandardItem>
#include <QStandardItemModel>

#include "ffftp.h"
#include "hostsettingsdialog.hpp"
#include "stdafx.h"
#include "ui/uicommon.h"
#include "ui_hostlistdialog.h"

// TODO: 選択しているホストのインデックスを保存している？

// D-Pointer(PImplメカニズム)による隠ぺいの実装
class HostListDialog::Private {
 public:
  Private();
  ~Private();
  Ui::HostListDialogClass ui;
  hostcontext_t selected_hc;
};
HostListDialog::Private::Private() : ui(), selected_hc(nullptr) {}
HostListDialog::Private::~Private() {}

HostListDialog::HostListDialog(QWidget* parent)
    : QDialog(parent), d_(new Private()) {
  d_->ui.setupUi(this);
  updateEnabled();
}
HostListDialog::~HostListDialog() {}

// リスト選択中のホストを示すホストコンテキストを返す
const hostcontext_t HostListDialog::hostcontext() const {
  return d_->selected_hc;
}

// [接続]ボタンを押下したときの処理
// 実際の接続処理はこのダイアログを呼び出した側(MainWindowクラス)で行う
void HostListDialog::accept() {
  d_->selected_hc = d_->ui.treeView_HostList->currentHostContext();
  QDialog::accept();
}

// [新規ホスト]ボタンを押下したときの処理
void HostListDialog::onClick_pushButton_NewHost() {
  hostcontext_t hc = d_->ui.treeView_HostList->currentHostContext();
  hostdata hdata;
  ffftp_hostdata_initialize(&hdata);
  ffftp_hostcontext_hostdata_default(&hdata);
  if (showSettingDialog(hdata)) {
    hostcontext_t new_hc = ffftp_hostcontext_new(hc, &hdata);
    d_->ui.treeView_HostList->update();
    d_->ui.treeView_HostList->setCurrentIndex(new_hc);
    updateEnabled();
  }
  ffftp_hostdata_finalize(&hdata);
}

// [新規グループ]ボタンを押下したときの処理
void HostListDialog::onClick_pushButton_NewGroup() {
  hostcontext_t hc = d_->ui.treeView_HostList->currentHostContext();
  if (QString group_name{}; askGroupName(group_name, kStringGroupNameNew)) {
    hostcontext_t new_hc =
        ffftp_hostcontext_newgroup(hc, group_name.toStdWString().c_str());
    d_->ui.treeView_HostList->update();
    d_->ui.treeView_HostList->setCurrentIndex(new_hc);
    updateEnabled();
  }
}

// [設定変更]ボタンを押下したときの処理
void HostListDialog::onClick_pushButton_Mod() {
  hostcontext_t hc = d_->ui.treeView_HostList->currentHostContext();
  if (ffftp_hostcontext_isgroup(hc)) {
    if (QString group_name{}; askGroupName(group_name, kStringGroupNameMod)) {
      hostcontext_t mod_hc =
          ffftp_hostcontext_modifygroup(hc, group_name.toStdWString().c_str());
      d_->ui.treeView_HostList->update();
      d_->ui.treeView_HostList->setCurrentIndex(mod_hc);
      updateEnabled();
    }
  } else {
    hostdata hdata;
    ffftp_hostdata_initialize(&hdata);
    ffftp_hostcontext_hostdata(hc, &hdata);
    if (showSettingDialog(hdata)) {
      hostcontext_t mod_hc = ffftp_hostcontext_modify(hc, &hdata);
      d_->ui.treeView_HostList->update();
      d_->ui.treeView_HostList->setCurrentIndex(mod_hc);
      updateEnabled();
    }
    ffftp_hostdata_finalize(&hdata);
  }
}

// [コピー]ボタンを押下したときの処理
void HostListDialog::onClick_pushButton_Copy() {
  hostcontext_t hc = d_->ui.treeView_HostList->currentHostContext();
  hostcontext_t new_hc = ffftp_hostcontext_copy(hc);
  d_->ui.treeView_HostList->update();
  d_->ui.treeView_HostList->setCurrentIndex(new_hc);
  updateEnabled();
}

// [削除]ボタンを押下したときの処理
void HostListDialog::onClick_pushButton_Del() {
  hostcontext_t hc = d_->ui.treeView_HostList->currentHostContext();
  bool isgroup = ffftp_hostcontext_isgroup(hc);
  QString title{isgroup ? kStringDeleteGroup : kStringDeleteHost};
  QString message{isgroup ? kStringDeleteGroupMsg : kStringDeleteHostMsg};
  if (QMessageBox::question(this, title, message) == QMessageBox::Yes) {
    hostcontext_t rem_hc = ffftp_hostcontext_delete(hc);
    d_->ui.treeView_HostList->update();
    d_->ui.treeView_HostList->setCurrentIndex(rem_hc);
    updateEnabled();
  }
}

// [↑]ボタンを押下したときの処理
void HostListDialog::onClick_pushButton_Up() {
  hostcontext_t hc = d_->ui.treeView_HostList->currentHostContext();
  if (hc) {
    ffftp_hostcontext_up(hc);
    d_->ui.treeView_HostList->update();
    d_->ui.treeView_HostList->setCurrentIndex(hc);
    updateEnabled();
  }
}

// [↓]ボタンを押下したときの処理
void HostListDialog::onClick_pushButton_Down() {
  hostcontext_t hc = d_->ui.treeView_HostList->currentHostContext();
  if (hc) {
    ffftp_hostcontext_down(hc);
    d_->ui.treeView_HostList->update();
    d_->ui.treeView_HostList->setCurrentIndex(hc);
    updateEnabled();
  }
}

// [既定の設定]ボタンを押下したときの処理
void HostListDialog::onClick_pushButton_Default() {
  hostdata hdata;
  ffftp_hostdata_initialize(&hdata);
  ffftp_hostcontext_hostdata_default(&hdata);
  if (showSettingDialog(hdata)) {
    ffftp_hostcontext_setdefault(&hdata);
  }
  ffftp_hostdata_finalize(&hdata);
}

// [ヘルプ]ボタンを押下したときの処理
void HostListDialog::onClick_pushButton_Help() {
  ffftp_showhelp(kHelpTopicHostList);
}

// ホストリストビューの項目をクリックしたときの処理
void HostListDialog::onClick_treeView_HostList(QModelIndex index) {
  Q_UNUSED(index);
  updateEnabled();
}

// 引数in_out_dataを初期データとして[ホストの設定]ダイアログを表示する
// 編集結果はそのまま引数in_out_dataに返る
bool HostListDialog::showSettingDialog(hostdata& in_out_data) /* const */ {
  bool ret = false;
  HostSettingsDialog setting_dlg(
      in_out_data,
      this);  // 関数のおしりにconst付けるとthisもconst型になり型不一致でエラー
  if (setting_dlg.exec() == QDialog::Accepted) {
    setting_dlg.hostData(in_out_data);
    ret = true;
  }
  return ret;
}

// 状態に応じてUI部品のEnableを切り替える
void HostListDialog::updateEnabled() {
  hostcontext_t current_hc = d_->ui.treeView_HostList->currentHostContext();
  UI_SETENABLED(d_->ui.pushButton_Mod, true);
  UI_SETENABLED(d_->ui.pushButton_Copy, true);
  UI_SETENABLED(d_->ui.pushButton_Del, true);
  UI_SETENABLED(d_->ui.pushButton_Up, true);
  UI_SETENABLED(d_->ui.pushButton_Down, true);
  UI_SETENABLED(d_->ui.pushButton_Connect, true);
  if (!current_hc) {
    UI_SETENABLED(d_->ui.pushButton_Mod, false);
    UI_SETENABLED(d_->ui.pushButton_Copy, false);
    UI_SETENABLED(d_->ui.pushButton_Del, false);
    UI_SETENABLED(d_->ui.pushButton_Up, false);
    UI_SETENABLED(d_->ui.pushButton_Down, false);
    UI_SETENABLED(d_->ui.pushButton_Connect, false);
  } else if (ffftp_hostcontext_isgroup(current_hc)) {
    UI_SETENABLED(d_->ui.pushButton_Copy, false);
    UI_SETENABLED(d_->ui.pushButton_Connect, false);
  }
}

// グループ名を訪ねるダイアログを表示する
bool HostListDialog::askGroupName(QString& group_name, const QString& title) {
  bool ok = false;
  group_name = QInputDialog::getText(this, title, kStringGroupNameAccess,
                                     QLineEdit::Normal, kEmptyString, &ok);
  return ok;
}
