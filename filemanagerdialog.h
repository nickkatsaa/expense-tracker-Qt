#ifndef FILEMANAGERDIALOG_H
#define FILEMANAGERDIALOG_H

#include <QDialog>
#include <QDir>
#include <QFile>
#include <QMessageBox>

namespace Ui {
class FileManagerDialog;
}

class FileManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileManagerDialog(QWidget *parent = nullptr);
    ~FileManagerDialog();

private slots:
    void on_deleteButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::FileManagerDialog *ui;
    void refreshFileList();
};

#endif // FILEMANAGERDIALOG_H
