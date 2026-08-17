/********************************************************************************
** Form generated from reading UI file 'filemanagerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEMANAGERDIALOG_H
#define UI_FILEMANAGERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FileManagerDialog
{
public:
    QListWidget *fileList;
    QPushButton *deleteButton;
    QPushButton *closeButton;

    void setupUi(QDialog *FileManagerDialog)
    {
        if (FileManagerDialog->objectName().isEmpty())
            FileManagerDialog->setObjectName("FileManagerDialog");
        FileManagerDialog->resize(646, 557);
        fileList = new QListWidget(FileManagerDialog);
        fileList->setObjectName("fileList");
        fileList->setGeometry(QRect(290, 30, 331, 491));
        deleteButton = new QPushButton(FileManagerDialog);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setGeometry(QRect(170, 410, 90, 29));
        QFont font;
        font.setBold(true);
        deleteButton->setFont(font);
        closeButton = new QPushButton(FileManagerDialog);
        closeButton->setObjectName("closeButton");
        closeButton->setGeometry(QRect(170, 370, 90, 29));
        closeButton->setFont(font);

        retranslateUi(FileManagerDialog);

        QMetaObject::connectSlotsByName(FileManagerDialog);
    } // setupUi

    void retranslateUi(QDialog *FileManagerDialog)
    {
        FileManagerDialog->setWindowTitle(QCoreApplication::translate("FileManagerDialog", "Dialog", nullptr));
        deleteButton->setText(QCoreApplication::translate("FileManagerDialog", "\316\224\316\271\316\261\316\263\317\201\316\261\317\206\316\256 ", nullptr));
        closeButton->setText(QCoreApplication::translate("FileManagerDialog", "\316\232\316\273\316\265\316\257\317\203\316\271\316\274\316\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileManagerDialog: public Ui_FileManagerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEMANAGERDIALOG_H
