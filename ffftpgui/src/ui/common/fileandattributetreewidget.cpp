#include "fileandattributetreewidget.hpp"

#include "ui/common/fileandattributesettingdialog.hpp"

class FileAndAttributeTreeWidget::Private {
 public:
  Private();
  ~Private();
};
FileAndAttributeTreeWidget::Private::Private() {}
FileAndAttributeTreeWidget::Private::~Private() {}

FileAndAttributeTreeWidget::FileAndAttributeTreeWidget(QWidget* parent)
    : AddableTreeWidget(parent), d_(new Private()) {
}
FileAndAttributeTreeWidget::~FileAndAttributeTreeWidget() {}

bool FileAndAttributeTreeWidget::askRowData(std::vector<std::wstring>& row_data) const {
  bool ok = false;
  row_data.clear();
  FileAndAttributeSettingDialog dialog{parentWidget()};
  if (dialog.exec() == QDialog::Accepted) {
    ok = true;
    QString fname{};
    int attr{0};
    dialog.fileAndAttribute(fname, attr);
    row_data.push_back(fname.toStdWString());
    row_data.push_back(QString("%1").arg(attr, 3, 10, QChar('0')).toStdWString());
  }
  return ok;
}
