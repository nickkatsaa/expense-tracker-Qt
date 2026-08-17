#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardItemModel>
#include <QMenu>
#include <QAction>
#include <QSortFilterProxyModel>
#include <QPieSeries>
#include <QPieSlice>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_addButton_clicked();
    void on_analyzeButton_clicked();
    void on_saveButton_clicked();
    void on_loadButton_clicked();
    void on_themeButton_clicked();
    void on_manageFilesButton_clicked();
    void on_convertButton_clicked();
    void onNetworkReply(QNetworkReply *reply);
    void onCurrencyChanged();
    void showContextMenu(const QPoint &pos);
    void onFilterCategoryChanged(const QString &category);
    void on_exportCsvButton_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;
    void updateStatsAndChart();
    double currentRate = 1.0;
    QString currentSymbol = "€";
    QStandardItemModel *tableModel;
    QString currentFilePath ="";
    QSortFilterProxyModel *proxyModel;
};
#endif // MAINWINDOW_H
