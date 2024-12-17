#include "filelistlocalform.hpp"

#include <QDir>
#include <QFileDialog>

#include "stdafx.h"
#include "ui/uicommon.h"

NEED_CASTDATA(FileListLocalForm);

class FileListLocalForm::Private {
 public:
  Private();
  ~Private();
};
FileListLocalForm::Private::Private() {}
FileListLocalForm::Private::~Private() {}

FileListLocalForm::FileInfo::FileInfo()
    : FileListForm::FileInfo() {}
FileListLocalForm::FileInfo::FileInfo(
  const QString& basepath,
  const QString& fullpath,
  const QString& filename,
  const QDateTime& date,
  qint64 size,
  const QString& ext,
  bool is_dir)
    : FileListForm::FileInfo(basepath, fullpath, filename, date, size, ext, is_dir) {}

FileListLocalForm::Data::Data()
    : FileListForm::Data() {}
FileListLocalForm::Data::Data(const QString& path, const FileInfo& afile)
    : FileListForm::Data(path, afile) {}

FileListLocalForm::FileListLocalForm(QWidget* parent)
    : FileListForm{new Data{}, parent}, d_{new Private{}} {
}
FileListLocalForm::~FileListLocalForm() {}

void FileListLocalForm::setRawData(const BaseForm::Data& data) {
  castData(*data_) = castData(data);
}

void FileListLocalForm::updateUi(const BaseForm::Data& data) {
  const ThisData& data_in = castData(data);
  static QVector<FileListForm::FileInfo> filelist{};
  filelist = fileList(data_in.path);
  saveColumnsWidth();
  model().clear();
  model().setHorizontalHeaderLabels({kStringName, kStringDate, kStringSize, kStringExtension});
  restoreColumnsWidth();
  for (const auto& _i : filelist) {
    const FileListLocalForm::FileInfo& fi = static_cast<const FileListLocalForm::FileInfo&>(_i);
    QVector<QStandardItem*> items{{
      fi.is_dir ?
        new QStandardItem(QIcon(kResImage_closedfolder16x16), fi.filename) :
        new QStandardItem(QIcon(kResImage_cleanfile16x16), fi.filename),
      new QStandardItem(fi.date.toString(tr("yyyy/MM/dd hh:mm"))),
      new QStandardItem(fi.is_dir ? tr("<DIR>") : QString::number(fi.size)),
      new QStandardItem(fi.ext),
    }};
    for (auto& i : items){
      i->setData(QVariant::fromValue(static_cast<const void*>(&fi)));
      i->setEditable(false);
    }
    model().appendRow(items);
  }
}

void FileListLocalForm::updateData(BaseForm::Data& data) const {
  ThisData& data_out = castData(data);
}

const QVector<FileListForm::FileInfo>& FileListLocalForm::fileList(const QString& path) const {
  static QVector<FileListForm::FileInfo> filelist;
  QVector<FileListForm::FileInfo> filelist_files;
  QVector<FileListForm::FileInfo> filelist_dirs;

  QDir dir{path};
  QFileInfoList qfilelist = dir.entryInfoList();

  filelist.clear();
  filelist.reserve(qfilelist.size());
  for (const auto& fi : qfilelist) {
    if (fi.isDir() && (fi.fileName() == "." || fi.fileName() == "..")) { continue; }
    QVector<FileListForm::FileInfo>& cur_list = fi.isDir() ? filelist_dirs : filelist_files;
    cur_list.push_back(FileListLocalForm::FileInfo{
      fi.absolutePath(),
      fi.absoluteFilePath(),
      fi.fileName(),
      fi.lastModified(),
      fi.size(),
      fi.suffix(),
      fi.isDir(),
    });
  }

  return filelist = filelist_dirs + filelist_files;
}

bool FileListLocalForm::challengeChangingPath(const QString & path) const {
  // TODO: FTPプロトコルの結果を受けて処理を変える
  return true;
}

bool FileListLocalForm::openDir(QString& path) const {
  QString _path = QFileDialog::getExistingDirectory(parentWidget(), QString(), path);
  bool ok = !_path.isEmpty();
  if (ok) { path = _path; }
  return ok;
}
