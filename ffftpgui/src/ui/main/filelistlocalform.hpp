#ifndef FFFTPGUI_UI_MAIN_FILELISTLOCALFORM_HPP_
#define FFFTPGUI_UI_MAIN_FILELISTLOCALFORM_HPP_

#include <QString>
#include <QDateTime>

#include "filelistform.hpp"

class FileListLocalForm : public FileListForm {
  Q_OBJECT;

 public:
  struct FileInfo : public FileListForm::FileInfo {
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
  struct Data : public FileListForm::Data {
    Data();
    Data(const QString& path, const FileInfo& afile);
  };
  explicit FileListLocalForm(QWidget* parent = Q_NULLPTR);
  virtual ~FileListLocalForm();

 protected:
  void setRawData(const BaseForm::Data& data) override;
  void updateUi(const BaseForm::Data& data) override;
  void updateData(BaseForm::Data& data) const override;
  const QVector<FileListForm::FileInfo>& fileList(const QString& path) const override;
  bool challengeChangingPath(const QString& path) const override;
  bool openDir(QString& path) const;

 private:
  class Private;
  std::unique_ptr<Private> d_;
  Q_DISABLE_COPY_MOVE(FileListLocalForm);
};

Q_DECLARE_METATYPE(FileListLocalForm::FileInfo);

#endif  // FFFTPGUI_UI_MAIN_FILELISTLOCALFORM_HPP_
