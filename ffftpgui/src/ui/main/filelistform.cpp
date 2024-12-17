#include "filelistform.hpp"

#include <QDir>

#include "ui_filelistform.h"

#include "ui/uicommon.h"

NEED_CASTDATA(FileListForm);

class FileListForm::Private {
 public:
  Private();
  ~Private();
  Ui::FileListForm ui;
  QStandardItemModel* model;
  QVector<int> columns_width;
  QStringList path_history;
  bool ignore_signals;
};
FileListForm::Private::Private()
    : ui{}, model{nullptr}, columns_width{}, path_history{}, ignore_signals{} {}
FileListForm::Private::~Private() {}

FileListForm::FileInfo::FileInfo()
    : basepath{},
      fullpath{},
      filename{},
      date{},
      size{0},
      ext{},
      is_dir{false} {}

FileListForm::FileInfo::FileInfo(
  const QString& basepath,
  const QString& fullpath,
  const QString& filename,
  const QDateTime& date,
  qint64 size,
  const QString& ext,
  bool is_dir)
    : basepath{basepath},
      fullpath{fullpath},
      filename{filename},
      date{date},
      size{size},
      ext{ext},
      is_dir{is_dir} {}

FileListForm::Data::Data() : path{}, afile{} {}
FileListForm::Data::Data(const QString& path, const FileInfo& afile)
    : path{path}, afile{afile} {}

FileListForm::FileListForm(Data* data, QWidget* parent)
    : BaseForm{data, parent}, d_{new Private{}} {
  d_->ui.setupUi(this);
  d_->model = new QStandardItemModel(parent);
  d_->ui.treeView_DirView->setModel(d_->model);
  d_->ui.treeView_DirView->setSortingEnabled(true);
//  d_->ui.listView_DirView->setModel(d_->model);
  d_->ui.listView_DirView->setVisible(false);
}
FileListForm::~FileListForm() { delete d_->model; }

int FileListForm::helpID() const { return -1; }

void FileListForm::setPath(const std::wstring& path) {
  setPath(QString(path));
}

void FileListForm::setPath(const QString& path) {
  if (challengeChangingPath(path)) {
    Data& data = castData(*data_);
    data.path = path;
    setData(data);
    updateHistory(path);
  }
}

const Ui::FileListForm& FileListForm::ui() const {
  return d_->ui;
}

Ui::FileListForm& FileListForm::ui() {
  return d_->ui;
}

const QStandardItemModel& FileListForm::model() const {
  return *d_->model;
}

QStandardItemModel& FileListForm::model() {
  return *d_->model;
}

void FileListForm::saveColumnsWidth() const {
  int cc = model().columnCount();
  d_->columns_width.clear();
  d_->columns_width.reserve(cc);
  for (int i = 0; i < cc; ++i) {
    d_->columns_width.push_back(ui().treeView_DirView->columnWidth(i));
  }
}

void FileListForm::restoreColumnsWidth() const {
  for (int i = 0; const auto& w : d_->columns_width) {
    ui().treeView_DirView->setColumnWidth(i++, w);
  }
}

void FileListForm::updateHistory(const QString& path) const {
  QString cpath{QDir::cleanPath(path)};
  QStringList& sl = d_->path_history;
  QComboBox& cb = *ui().comboBox_DirHist;
  if (std::find(sl.begin(), sl.end(), cpath) == sl.end()) {
    sl.push_back(cpath);
    std::sort(sl.begin(), sl.end());
  }
  // テキスト入力がEnterで決定されるとQComboBox内部で勝手に追加されるのでif分の外で再構築する必要がある
  const QSignalBlocker sblocker(cb);  // 一時的にシグナルの発信を抑制する（これがないと無限ループに陥る）
  cb.clear();
  cb.addItems(sl);
  cb.setCurrentIndex(cb.findText(cpath));
}

void FileListForm::onClick_toolButton_Up() {
  Data& data = castData(*data_);
  QDir dir{data.path};
  dir.cdUp();
  setPath(dir.path());
}
void FileListForm::onClick_toolButton_Open() {
  if (QString& path = castData(*data_).path; openDir(path)) {
    setPath(path);
  }
}
void FileListForm::onCurrentIndexChange_comboBox_DirHist(int index) {
  if (index >= 0) {
    setPath(ui().comboBox_DirHist->itemText(index));
  }
}
void FileListForm::onTextActivate_comboBox_DirHist(QString text) {
  if (!text.isEmpty()) { setPath(text); }
}
void FileListForm::onDoubleClick_treeView_DirView(QModelIndex index) {
  const FileInfo& finfo = *static_cast<const FileInfo*>(index.data(kUserRole).value<const void*>());
  if (finfo.is_dir) {
    setPath(finfo.basepath + '/' + finfo.filename);
  }
}
