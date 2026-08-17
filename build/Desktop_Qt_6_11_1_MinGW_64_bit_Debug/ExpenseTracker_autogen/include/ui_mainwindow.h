/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QChartView *chartView;
    QLabel *statsLabel;
    QPushButton *themeButton;
    QLabel *label;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QLabel *label_3;
    QComboBox *filterCombo;
    QPushButton *exportCsvButton;
    QWidget *layoutWidget1;
    QFormLayout *formLayout;
    QPushButton *analyzeButton;
    QCheckBox *taxCheckBox;
    QPushButton *manageFilesButton;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *currencyCombo;
    QPushButton *convertButton;
    QTableView *expenseTable;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    QPushButton *addButton;
    QLabel *currencyLabel;
    QComboBox *categoryCombo;
    QDoubleSpinBox *amountSpinBox;
    QDateEdit *dateEdit;
    QLabel *label_2;
    QComboBox *chartTypeCombo;
    QLabel *ChartTypeLabel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(816, 658);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(22, 66, 66);\n"
"color: rgb(236, 236, 236);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        chartView = new QChartView(centralwidget);
        chartView->setObjectName("chartView");
        chartView->setGeometry(QRect(390, 120, 411, 341));
        QFont font;
        font.setFamilies({QString::fromUtf8("Roboto")});
        font.setPointSize(10);
        chartView->setFont(font);
        statsLabel = new QLabel(centralwidget);
        statsLabel->setObjectName("statsLabel");
        statsLabel->setGeometry(QRect(250, 490, 381, 121));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe UI Black")});
        font1.setPointSize(12);
        font1.setBold(true);
        statsLabel->setFont(font1);
        themeButton = new QPushButton(centralwidget);
        themeButton->setObjectName("themeButton");
        themeButton->setGeometry(QRect(620, 0, 111, 41));
        QFont font2;
        font2.setBold(true);
        themeButton->setFont(font2);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(280, 10, 191, 20));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Microsoft YaHei Light")});
        font3.setBold(true);
        label->setFont(font3);
        label->setAutoFillBackground(false);
        label->setFrameShadow(QFrame::Shadow::Plain);
        label->setLineWidth(1);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(640, 470, 171, 175));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        loadButton = new QPushButton(layoutWidget);
        loadButton->setObjectName("loadButton");
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Segoe UI Semibold")});
        font4.setPointSize(11);
        font4.setBold(false);
        font4.setItalic(false);
        font4.setStrikeOut(false);
        loadButton->setFont(font4);

        verticalLayout->addWidget(loadButton);

        saveButton = new QPushButton(layoutWidget);
        saveButton->setObjectName("saveButton");
        saveButton->setFont(font4);

        verticalLayout->addWidget(saveButton);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");
        QFont font5;
        font5.setPointSize(10);
        label_3->setFont(font5);

        verticalLayout->addWidget(label_3);

        filterCombo = new QComboBox(layoutWidget);
        filterCombo->addItem(QString());
        filterCombo->addItem(QString());
        filterCombo->addItem(QString());
        filterCombo->addItem(QString());
        filterCombo->addItem(QString());
        filterCombo->addItem(QString());
        filterCombo->setObjectName("filterCombo");

        verticalLayout->addWidget(filterCombo);

        exportCsvButton = new QPushButton(layoutWidget);
        exportCsvButton->setObjectName("exportCsvButton");

        verticalLayout->addWidget(exportCsvButton);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(0, 470, 236, 161));
        formLayout = new QFormLayout(layoutWidget1);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        analyzeButton = new QPushButton(layoutWidget1);
        analyzeButton->setObjectName("analyzeButton");
        analyzeButton->setFont(font);

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, analyzeButton);

        taxCheckBox = new QCheckBox(layoutWidget1);
        taxCheckBox->setObjectName("taxCheckBox");
        taxCheckBox->setFont(font);

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, taxCheckBox);

        manageFilesButton = new QPushButton(layoutWidget1);
        manageFilesButton->setObjectName("manageFilesButton");
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Segoe UI Semibold")});
        font6.setPointSize(11);
        font6.setBold(false);
        manageFilesButton->setFont(font6);

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, manageFilesButton);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        currencyCombo = new QComboBox(layoutWidget1);
        currencyCombo->addItem(QString());
        currencyCombo->addItem(QString());
        currencyCombo->addItem(QString());
        currencyCombo->addItem(QString());
        currencyCombo->addItem(QString());
        currencyCombo->setObjectName("currencyCombo");

        horizontalLayout_3->addWidget(currencyCombo);

        convertButton = new QPushButton(layoutWidget1);
        convertButton->setObjectName("convertButton");

        horizontalLayout_3->addWidget(convertButton);


        formLayout->setLayout(3, QFormLayout::ItemRole::LabelRole, horizontalLayout_3);

        expenseTable = new QTableView(centralwidget);
        expenseTable->setObjectName("expenseTable");
        expenseTable->setGeometry(QRect(0, 120, 381, 341));
        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(10, 90, 553, 31));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        addButton = new QPushButton(layoutWidget2);
        addButton->setObjectName("addButton");
        addButton->setFont(font);

        gridLayout->addWidget(addButton, 0, 4, 1, 1);

        currencyLabel = new QLabel(layoutWidget2);
        currencyLabel->setObjectName("currencyLabel");
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Roboto")});
        font7.setPointSize(14);
        currencyLabel->setFont(font7);

        gridLayout->addWidget(currencyLabel, 0, 2, 1, 1);

        categoryCombo = new QComboBox(layoutWidget2);
        categoryCombo->addItem(QString());
        categoryCombo->addItem(QString());
        categoryCombo->addItem(QString());
        categoryCombo->addItem(QString());
        categoryCombo->addItem(QString());
        categoryCombo->setObjectName("categoryCombo");

        gridLayout->addWidget(categoryCombo, 0, 0, 1, 1);

        amountSpinBox = new QDoubleSpinBox(layoutWidget2);
        amountSpinBox->setObjectName("amountSpinBox");
        amountSpinBox->setFont(font);
        amountSpinBox->setMaximum(999999.989999999990687);

        gridLayout->addWidget(amountSpinBox, 0, 1, 1, 1);

        dateEdit = new QDateEdit(layoutWidget2);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setFont(font);

        gridLayout->addWidget(dateEdit, 0, 3, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 70, 551, 20));
        chartTypeCombo = new QComboBox(centralwidget);
        chartTypeCombo->addItem(QString());
        chartTypeCombo->addItem(QString());
        chartTypeCombo->setObjectName("chartTypeCombo");
        chartTypeCombo->setGeometry(QRect(611, 90, 201, 28));
        ChartTypeLabel = new QLabel(centralwidget);
        ChartTypeLabel->setObjectName("ChartTypeLabel");
        ChartTypeLabel->setGeometry(QRect(610, 70, 81, 20));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        statsLabel->setText(QCoreApplication::translate("MainWindow", "\316\221\316\240\316\237\316\244\316\225\316\233\316\225\316\243\316\234\316\221\316\244\316\221: ", nullptr));
        themeButton->setText(QCoreApplication::translate("MainWindow", "Dark Mode \360\237\214\231", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:11pt;\"> EXPENCE TRACKER </span></p></body></html>", nullptr));
        loadButton->setText(QCoreApplication::translate("MainWindow", "\316\246\317\214\317\201\317\204\317\211\317\203\316\267", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "\316\221\317\200\316\277\316\270\316\256\316\272\316\265\317\205\317\203\316\267", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Filter Results:", nullptr));
        filterCombo->setItemText(0, QCoreApplication::translate("MainWindow", "\316\214\316\273\316\265\317\202 \316\277\316\271 \316\232\316\261\317\204\316\267\316\263\316\277\317\201\316\257\316\265\317\202", nullptr));
        filterCombo->setItemText(1, QCoreApplication::translate("MainWindow", "\360\237\233\222 \316\246\316\261\316\263\316\267\317\204\317\214", nullptr));
        filterCombo->setItemText(2, QCoreApplication::translate("MainWindow", "\360\237\222\241 \316\233\316\277\316\263\316\261\317\201\316\271\316\261\317\203\316\274\316\277\316\257", nullptr));
        filterCombo->setItemText(3, QCoreApplication::translate("MainWindow", "\360\237\232\227 \316\234\316\265\317\204\316\261\317\206\316\277\317\201\316\255\317\202", nullptr));
        filterCombo->setItemText(4, QCoreApplication::translate("MainWindow", "\360\237\216\254 \316\250\317\205\317\207\316\261\316\263\317\211\316\263\316\257\316\261", nullptr));
        filterCombo->setItemText(5, QCoreApplication::translate("MainWindow", "\360\237\223\246 \316\206\316\273\316\273\316\277", nullptr));

        exportCsvButton->setText(QCoreApplication::translate("MainWindow", "\316\225\316\276\316\261\316\263\317\211\316\263\316\256 \317\203\316\265 CSV", nullptr));
        analyzeButton->setText(QCoreApplication::translate("MainWindow", "\316\245\317\200\316\277\316\273\316\277\316\263\316\271\317\203\316\274\317\214\317\202 \316\243\317\204\316\261\317\204\316\271\317\203\317\204\316\271\316\272\317\216\316\275!", nullptr));
        taxCheckBox->setText(QCoreApplication::translate("MainWindow", "\316\240\317\201\316\277\317\203\316\270\316\256\316\272\316\267 \316\246\317\214\317\201\316\277\317\205 (24%)", nullptr));
        manageFilesButton->setText(QCoreApplication::translate("MainWindow", "\316\224\316\271\316\261\317\207\316\265\316\257\317\201\316\271\317\203\316\267 \316\221\317\201\317\207\316\265\316\257\317\211\316\275 \360\237\227\202\357\270\217", nullptr));
        currencyCombo->setItemText(0, QCoreApplication::translate("MainWindow", "EUR (\342\202\254)", nullptr));
        currencyCombo->setItemText(1, QCoreApplication::translate("MainWindow", "USD ($)", nullptr));
        currencyCombo->setItemText(2, QCoreApplication::translate("MainWindow", "GBP (\302\243)", nullptr));
        currencyCombo->setItemText(3, QCoreApplication::translate("MainWindow", "JPY (\302\245)", nullptr));
        currencyCombo->setItemText(4, QCoreApplication::translate("MainWindow", "CHF (Fr)", nullptr));

        convertButton->setText(QCoreApplication::translate("MainWindow", "\316\234\316\265\317\204\316\261\317\204\317\201\316\277\317\200\316\256", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "\316\240\317\201\316\277\317\203\316\270\316\256\316\272\316\267", nullptr));
        currencyLabel->setText(QCoreApplication::translate("MainWindow", "\342\202\254", nullptr));
        categoryCombo->setItemText(0, QCoreApplication::translate("MainWindow", "\360\237\233\222 \316\246\316\261\316\263\316\267\317\204\317\214", nullptr));
        categoryCombo->setItemText(1, QCoreApplication::translate("MainWindow", "\360\237\222\241 \316\233\316\277\316\263\316\261\317\201\316\271\316\261\317\203\316\274\316\277\316\257", nullptr));
        categoryCombo->setItemText(2, QCoreApplication::translate("MainWindow", "\360\237\232\227 \316\234\316\265\317\204\316\261\317\206\316\277\317\201\316\255\317\202", nullptr));
        categoryCombo->setItemText(3, QCoreApplication::translate("MainWindow", "\360\237\216\254 \316\250\317\205\317\207\316\261\316\263\317\211\316\263\316\257\316\261", nullptr));
        categoryCombo->setItemText(4, QCoreApplication::translate("MainWindow", "\360\237\223\246 \316\206\316\273\316\273\316\277", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "  Category:                          Amount:                                        Date:", nullptr));
        chartTypeCombo->setItemText(0, QCoreApplication::translate("MainWindow", "\360\237\223\210 \316\224\316\271\316\261\316\272\317\215\316\274\316\261\316\275\317\203\316\267 \316\247\317\201\317\214\316\275\316\277\317\205", nullptr));
        chartTypeCombo->setItemText(1, QCoreApplication::translate("MainWindow", "\360\237\223\212 \316\232\316\261\317\204\316\261\316\275\316\277\316\274\316\256 \316\232\316\261\317\204\316\267\316\263\316\277\317\201\316\271\317\216\316\275", nullptr));

        ChartTypeLabel->setText(QCoreApplication::translate("MainWindow", "Chart Type:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
