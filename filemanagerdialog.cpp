#include "filemanagerdialog.h"
#include "ui_filemanagerdialog.h"

FileManagerDialog::FileManagerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FileManagerDialog)
{
    ui->setupUi(this);
    refreshFileList();
}

FileManagerDialog::~FileManagerDialog()
{
    delete ui;
}

void FileManagerDialog::refreshFileList()
{
    ui->fileList->clear();

    QString folderPath = QDir::currentPath() + "/SavedExpences";
    QDir dir(folderPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QStringList filters;
    filters << "*.txt";

    QStringList files = dir.entryList(filters, QDir::Files);

    for (const QString &fileName : files) {
        ui->fileList->addItem(fileName);
    }
}
void FileManagerDialog::on_deleteButton_clicked()
{
    QListWidgetItem *selectedItem= ui->fileList->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Προσοχή", "Παρακαλώ επίλεξε ένα αρχείο για διαγραφή!");
        return;
    }
    QString fileName=selectedItem->text();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Επιβεβαίωση",
    "Είσαι σίγουρος ότι θέλεις να διαγράψεις το αρχείο:\n" + fileName + ";",
    QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QString fullPath = QDir::currentPath() + "/SavedExpences/" + fileName;
        if (QFile::remove(fullPath)) {
            QMessageBox::information(this, "Επιτυχία", "Το αρχείο διαγράφηκε!");
            refreshFileList();
        } else {
            QMessageBox::critical(this, "Σφάλμα", "Δεν ήταν δυνατή η διαγραφή του αρχείου.");
        }
    }
}
void FileManagerDialog::on_closeButton_clicked()
{
    this->close();
}