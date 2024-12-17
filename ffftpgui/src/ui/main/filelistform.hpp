#ifndef FFFTPGUI_UI_MAIN_FILELISTFORM_HPP_
#define FFFTPGUI_UI_MAIN_FILELISTFORM_HPP_

#include <QFileInfo>
#include <QStandardItemModel>

#include "ui/base/baseform.hpp"

#include "ui_filelistform.h"

class FileListForm : public BaseForm {
  Q_OBJECT;

 public:
  struct FileInfo {
    QString basepath;
    QString fullpath;
    QString filename;
    QDateTime date;
    qint64 size;
    QString ext;
    bool is_dir;
    FileInfo();
    FileInfo(
      const QString& basepath,
      const QString& fullpath,
      const QString& filename,
      const QDateTime& date,
      qint64 size,
      const QString& ext,
      bool is_dir);
  };
  struct Data : public BaseForm::Data {
    QString path;
    FileInfo afile;
    Data();
    Data(const QString& path, const FileInfo& afile);
  };
  explicit FileListForm(Data* data, QWidget* parent = Q_NULLPTR);
  virtual ~FileListForm();
  int helpID() const override;
  void setPath(const std::wstring& path);
  void setPath(const QString& path);

protected:
  const Ui::FileListForm& ui() const;
  Ui::FileListForm& ui();
  const QStandardItemModel& model() const;
  QStandardItemModel& model();
  void saveColumnsWidth() const;
  void restoreColumnsWidth() const;
  virtual const QVector<FileInfo>& fileList(const QString& path) const = 0;
  virtual bool challengeChangingPath(const QString& path) const = 0;
  virtual bool openDir(QString& path) const = 0;

 private:
  void updateHistory(const QString& path) const;

 private Q_SLOTS:
  void onClick_toolButton_Up();
  void onClick_toolButton_Open();
  void onCurrentIndexChange_comboBox_DirHist(int);
  void onTextActivate_comboBox_DirHist(QString);
  void onDoubleClick_treeView_DirView(QModelIndex);

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(FileListForm);
};

Q_DECLARE_METATYPE(FileListForm::FileInfo);

#endif  // FFFTPGUI_UI_MAIN_FILELISTFORM_HPP_
