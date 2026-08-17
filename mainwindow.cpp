#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLineSeries>
#include <QChart>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include "filemanagerdialog.h"
#include <QHeaderView>
#include <QPieSeries>
#include <QPieSlice>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    networkManager=new QNetworkAccessManager(this);
    connect(networkManager,&QNetworkAccessManager::finished, this,&MainWindow::onNetworkReply);
    // --- ΔΙΜΙΟΥΡΓΙΑ & ΡΥΘΜΙΣΗ ΠΙΝΑΚΑ ---
    tableModel= new QStandardItemModel(this);
    tableModel->setColumnCount(3);
    tableModel->setHorizontalHeaderLabels({"Ημερομηνία","Κατηγορία" ,"Ποσό (€)"});
    ui->expenseTable->setModel(tableModel); //ΣΗΜΑΝΤΙΚΗ ΓΡΑΜΜΗ
    proxyModel=new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(tableModel);
    proxyModel->setFilterKeyColumn(1);// 2. Ορίζουμε ότι το φίλτρο θα ψάχνει στη Στήλη 1 (Κατηγορία)
    ui->expenseTable->setModel(proxyModel);//Ο πίνακας πλέον βλέπει το proxyModel
    connect(ui->filterCombo, &QComboBox::currentTextChanged,this,&MainWindow::onFilterCategoryChanged);
    // Όταν ο χρήστης αλλάζει τύπο γραφήματος, ξανασχεδιάζεται το γράφημα!
    connect(ui->chartTypeCombo, &QComboBox::currentIndexChanged, this, &MainWindow::updateStatsAndChart);
    // --- ΔΕΞΙ ΚΛΙΚ (CONTEXT MENU) ---
    connect(ui->expenseTable, &QTableView::customContextMenuRequested,this,&MainWindow::showContextMenu);
    ui->expenseTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->expenseTable->setContextMenuPolicy(Qt::CustomContextMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    double inputAmount = ui->amountSpinBox->value(); // Το ποσό που έγραψε ο χρήστης
    if (inputAmount <= 0) return;

    QString dateStr = ui->dateEdit->date().toString("dd/MM/yyyy");
    // Παίρνουμε την κατηγορία
    QString categoryStr = ui->categoryCombo->currentText();
    // Υπολογίζουμε την εσωτερική βασική τιμή σε Ευρώ
    double baseEur = inputAmount / currentRate;
    QStandardItem *dateItem=new QStandardItem(dateStr);
    QStandardItem *categoryItem = new QStandardItem(categoryStr);
    QString amountText = QString("%1 %2").arg(inputAmount, 0, 'f', 2).arg(currentSymbol);
    QStandardItem *amountItem= new QStandardItem(amountText);
    amountItem->setData(baseEur, Qt::UserRole);
    tableModel->appendRow({dateItem,categoryItem,amountItem});
    ui->amountSpinBox->setValue(0.0);
    updateStatsAndChart();
}
void MainWindow::updateStatsAndChart()
{
    int totalRows = tableModel->rowCount();
    if (totalRows == 0) {
        ui->statsLabel->setText("Ο Πίνακας είναι άδειος!");
        return;
    }

    double total = 0.0;
    double maxAmount = 0.0;
    QLineSeries *series = new QLineSeries();
    QMap<QString, double> categoryTotals;
    for (int i = 0; i < totalRows; ++i) {
        QStandardItem *dateItem =tableModel->item(i,0);
        QStandardItem *categoryItem=tableModel->item(i,1);
        QStandardItem *amountItem=tableModel->item(i,2);
        if(!dateItem || !categoryItem || !amountItem) continue;
        // Διαβάζουμε το EUR από το UserRole και το προσαρμόζουμε στο τρέχον νόμισμα
        double baseEur= amountItem->data(Qt::UserRole).toDouble();
        double displayVal= baseEur*currentRate;
        if (displayVal > maxAmount) {
            maxAmount = displayVal;
        }
        total += displayVal;
        QDateTime date =QDateTime::fromString(dateItem->text().trimmed(),"dd/MM/yyyy");
        series->append(date.toMSecsSinceEpoch(),displayVal);
        QString catName=categoryItem->text();
        categoryTotals[catName]+=displayVal;
    }

    // Υπολογισμός ΦΠΑ
    QString taxMessage = " (Χωρίς ΦΠΑ)";
    if (ui->taxCheckBox && ui->taxCheckBox->isChecked()) {
        total *= 1.24;
        taxMessage = " (Με ΦΠΑ 24%)";
    }

    double average = total / totalRows;

    // Ενημέρωση του Stats Label με το ΤΡΕΧΟΝ σύμβολο ($, €, £, κλπ)
    QString resultText = QString(
      "Σύνολο εξόδων: %1 %2%4\n"
      "Μέσος Όρος: %3 %2\n"
      "Ακριβότερο έξοδο: %5 %2")
     .arg(total, 0, 'f', 2)
     .arg(currentSymbol)
     .arg(average, 0, 'f', 2)
     .arg(taxMessage)
     .arg(maxAmount, 0, 'f', 2);

    ui->statsLabel->setText(resultText);

    // Δημιουργία & Ενημέρωση του Γραφήματος (Chart)
    QChart *chart = new QChart();
    if (ui->chartTypeCombo->currentIndex()==0){
        chart->addSeries(series);
        chart->setTitle("Διακύμανση Εξόδων");

        QDateTimeAxis *axisX= new QDateTimeAxis;
        axisX->setFormat("dd/MM/yyyy");
        axisX->setTitleText("Ημερομηνία");
        axisX->setTickCount(totalRows);
        chart->addAxis(axisX,Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY=new QValueAxis;
        axisY->setTitleText(QString("Ποσό (%1)").arg(currentSymbol));
        chart->addAxis(axisY,Qt::AlignLeft);
        series->attachAxis(axisY);
        chart->legend()->hide();
    }
    else{
        QPieSeries *pieSeries= new QPieSeries;
        for (auto it = categoryTotals.begin(); it !=categoryTotals.end(); ++it){
            QString cat = it.key();
            double val= it.value();
            QPieSlice *slice=pieSeries->append(cat,val);
            slice->setLabelVisible(true);
            slice->setLabelPosition(QPieSlice::LabelOutside);
            slice->setLabel(QString("%1: \n%2 %3").arg(cat).arg(val, 0, 'f', 2).arg(currentSymbol));
        }
        chart->addSeries(pieSeries);
        chart->setTitle("Κατανομή Εξόδων ανά Κατηγορία");
        chart->legend()->setAlignment(Qt::AlignBottom);
    }
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);
}
void MainWindow::on_analyzeButton_clicked()
{
    updateStatsAndChart();
}


// --- ΑΠΟΘΗΚΕΥΣΗ (Σώζει ΠΑΝΤΑ σε Ευρώ) ---
void MainWindow::on_saveButton_clicked()
{
    // Ανοίγει παράθυρο για επιλογή αρχείου αποθήκευσης

    // Αν δεν υπάρχει ήδη ανοιχτό αρχείο, ζητάμε από τον χρήστη να επιλέξει πού θα αποθηκεύσει
    if (currentFilePath.isEmpty()) {
        currentFilePath = QFileDialog::getSaveFileName(this, "Αποθήκευση Εξόδων", "SavedExpences/expenses.txt", "Text Files (*.txt)");
        if (currentFilePath.isEmpty()) return; // Ο χρήστης πάτησε Cancel
    }

    QFile file(currentFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Σφάλμα", "Δεν ήταν δυνατή η πρόσβαση στο αρχείο!");
        return;
    }
    QTextStream out(&file);

    for (int i = 0; i < tableModel->rowCount(); ++i) {
        QStandardItem *dateItem = tableModel->item(i,0);
        QStandardItem *categoryItem = tableModel->item(i, 1); // Προαιρετικά αν θέλεις να σώσεις κατηγορία
        QStandardItem *amountItem = tableModel->item(i,2);
        // Παίρνουμε ΠΑΝΤΑ την αρχική τιμή σε Ευρώ από το UserRole
        if (dateItem && categoryItem && amountItem) {
            QString dateStr = dateItem->text();
            QString categoryStr=categoryItem->text();
            double baseEur = amountItem->data(Qt::UserRole).toDouble();
        // Γράφουμε στο αρχείο πάντα σε μορφή Ευρώ: "dd/MM/yyyy -> XX.XX €"
        out << dateStr << " | " << categoryStr<<" | "<< QString::number(baseEur, 'f', 2) << " €\n";

        }
    }
    file.close();
    QMessageBox::information(this, "Επιτυχία", "Τα έξοδα αποθηκεύτηκαν με ασφάλεια σε Ευρώ!");
}
// --- ΦΟΡΤΩΣΗ (Διαβάζει Ευρώ & μετατρέπει στο τρέχον νόμισμα) ---
void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Φόρτωση Εξόδων", "SavedExpences", "Text Files (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Σφάλμα", "Δεν ήταν δυνατή η άνοιγμα του αρχείου για ανάγνωση!");
        return;
    }
    // Καθαρίζουμε όλες τις υπάρχουσες γραμμές του πίνακα
    tableModel->removeRows(0,tableModel->rowCount());
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.isEmpty()) continue;
        QString dateStr;
        QString categoryStr = "📦 Άλλο"; // Προεπιλογή αν φορτώσουμε παλιό αρχείο
        double baseEur = 0.0;
        // 1. Νέα μορφή (με 3 πεδία χωρισμένα με '|')
        if (line.contains("|")) {
            QStringList parts = line.split("|");
            if (parts.size() == 3) {
                dateStr = parts[0].trimmed();
                categoryStr = parts[1].trimmed();

                QString amtStr = parts[2].trimmed();
                amtStr.remove("€").remove("$").remove("£").remove("¥").remove("Fr");
                baseEur = amtStr.trimmed().toDouble();
            }
        }
        // 2. Παλιά μορφή (με 2 πεδία χωρισμένα με '->') για συμβατότητα
        else if (line.contains("->")) {
            QStringList parts = line.split("->");
            if (parts.size() == 2) {
                dateStr = parts[0].trimmed();

                QString amtStr = parts[1].trimmed();
                amtStr.remove("€").remove("$").remove("£").remove("¥").remove("Fr");
                baseEur = amtStr.trimmed().toDouble();
            }
        }

        // Δημιουργία των 3 αντικειμένων για τον πίνακα
        if (!dateStr.isEmpty()) {
            double displayVal = baseEur * currentRate;

            QStandardItem *dateItem = new QStandardItem(dateStr);
            QStandardItem *categoryItem = new QStandardItem(categoryStr);

            QString amountText = QString("%1 %2").arg(displayVal, 0, 'f', 2).arg(currentSymbol);
            QStandardItem *amountItem = new QStandardItem(amountText);
            amountItem->setData(baseEur, Qt::UserRole);

            // Προσθήκη και των 3 στη σειρά
            tableModel->appendRow({dateItem, categoryItem, amountItem});
        }
    }

    file.close();

    currentFilePath = fileName;
    updateStatsAndChart();
}
void MainWindow::on_themeButton_clicked()
{
    static int themeState = 0;
    themeState = (themeState + 1) % 3;

    if (themeState == 0)
    {
        // 1. CIEL MODE
        this->setStyleSheet(
            "QMainWindow { background-color: #1a3d3d; }"
            "QLabel, QCheckBox { color: #ffffff; font-weight: bold; }"
            "QPushButton { background-color: #265c5c; color: white; border-radius: 5px; padding: 6px; border: 1px solid #388080; }"
            "QPushButton:hover { background-color: #317575; }"
            "QListWidget { background-color: #143030; color: #ffffff; border: 1px solid #265c5c; border-radius: 4px; }"
            "QDoubleSpinBox, QDateEdit { background-color: #143030; color: #ffffff; border: 1px solid #265c5c; }"
            "QChartView { border: none; background: transparent; }" // <-- ΧΩΡΙΣ BORDER
            );

        ui->themeButton->setText("Dark Mode 🌙");
    }
    else if (themeState == 1)
    {
        // 2. DARK MODE
        this->setStyleSheet(
            "QMainWindow { background-color: #121212; }"
            "QLabel, QCheckBox { color: #ffffff; font-weight: bold; }"
            "QPushButton { background-color: #1f1f1f; color: #00adb5; border-radius: 5px; padding: 6px; border: 1px solid #00adb5; }"
            "QPushButton:hover { background-color: #00adb5; color: #121212; }"
            "QListWidget { background-color: #1e1e1e; color: #ffffff; border: 1px solid #333333; border-radius: 4px; }"
            "QDoubleSpinBox, QDateEdit { background-color: #1e1e1e; color: #ffffff; border: 1px solid #333333; }"
            "QChartView { border: none; background: transparent; }" // <-- ΧΩΡΙΣ BORDER
            // Κανόνες για τα Message Boxes στο Dark Mode
            "QMessageBox { background-color: #2c3e50; }"
            "QMessageBox QLabel { color: #ffffff; font-size: 13px; }"
            "QMessageBox QPushButton { background-color: #1abc9c; color: white; border-radius: 5px; padding: 5px 15px; }"
            );

        ui->themeButton->setText("Light Mode ☀");
    }
    else if (themeState == 2)
    {
        // 3. LIGHT MODE
        this->setStyleSheet(
            "QMainWindow { background-color: #f4f6f9; }"
            "QLabel, QCheckBox { color: #222222; font-weight: bold; }"
            "QPushButton { background-color: #0d6efd; color: white; border-radius: 5px; padding: 6px; border: none; }"
            "QPushButton:hover { background-color: #0b5ed7; }"
            "QListWidget { background-color: #ffffff; color: #222222; border: 1px solid #cccccc; border-radius: 4px; }"
            "QDoubleSpinBox, QDateEdit { background-color: #ffffff; color: #222222; border: 1px solid #cccccc; }"
            "QChartView { border: none; background: transparent; }" // <-- ΧΩΡΙΣ BORDER
            // Κανόνες για τα Message Boxes στο Light Mode
            "QMessageBox { background-color: #ffffff; }"
            "QMessageBox QLabel { color: #2c3e50; font-size: 13px; }"
            "QMessageBox QPushButton { background-color: #007bff; color: white; border-radius: 5px; padding: 5px 15px; }"
            );

        ui->themeButton->setText("Ciel Mode 🌊");
    }
}

void MainWindow::on_manageFilesButton_clicked()
{
    FileManagerDialog dialog(this);
    dialog.exec();
}

void MainWindow::on_convertButton_clicked()
{
    QUrl url("https://open.er-api.com/v6/latest/EUR");
    QNetworkRequest request(url);
    networkManager->get(request);
}
// 3. ΑΠΑΝΤΗΣΗ ΑΠΟ ΤΟ ΙΝΤΕΡΝΕΤ (Μετατροπή Νόμισματος)
void MainWindow::onNetworkReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        QMessageBox::critical(this, "Σφάλμα Δικτύου", "Δεν ήταν δυνατή η σύνδεση στο ίντερνετ!");
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject rootObj = jsonDoc.object();

    if (rootObj.contains("rates") && rootObj["rates"].isObject()) {
        QJsonObject ratesObj = rootObj["rates"].toObject();

        // 1. Βρίσκουμε τον κωδικό και το σύμβολο του νομίσματος
        QString selectedText = ui->currencyCombo->currentText();
        QString currCode = selectedText.left(3);
        currentSymbol = selectedText.section('(', 1).section(')', 0, 0);

        // 2. Υπολογίζουμε την ισοτιμία
        currentRate = 1.0;
        if (currCode != "EUR") {
            currentRate = ratesObj[currCode].toDouble();
        }

        if (ui->currencyLabel) {
            ui->currencyLabel->setText(currentSymbol);
        }

        // 3. Ενημερώνουμε τον τίτλο της στήλης 1 του πίνακα
        tableModel->setHeaderData(2, Qt::Horizontal, QString("Ποσό (%1)").arg(currentSymbol));

        // 4. Ενημερώνουμε τις τιμές σε κάθε γραμμή του tableModel
        for (int i = 0; i < tableModel->rowCount(); ++i) {
            QStandardItem *amountItem = tableModel->item(i, 2); // Στήλη 2: Ποσό
            if (amountItem) {
                // Διαβάζουμε την καθαρή τιμή Ευρώ από το UserRole
                double baseEur = amountItem->data(Qt::UserRole).toDouble();
                double convertedVal = baseEur * currentRate;

                // Ενημερώνουμε το κείμενο του κελιού με το νέο νόμισμα
                amountItem->setText(QString("%1 %2").arg(convertedVal, 0, 'f', 2).arg(currentSymbol));
            }
        }

        // 5. Αυτόματη ενημέρωση Στατιστικών ΚΑΙ Γραφήματος!
        updateStatsAndChart();
    }

    reply->deleteLater();
}
void MainWindow::onCurrencyChanged()
{
    // 1. Ενημέρωση του τίτλου της στήλης 1 με το νέο σύμβολο
    tableModel->setHeaderData(1, Qt::Horizontal, QString("Ποσό (%1)").arg(currentSymbol));

    // 2. Ενημέρωση των τιμών σε κάθε γραμμή του πίνακα
    for (int i = 0; i < tableModel->rowCount(); ++i) {
        QStandardItem *amountItem = tableModel->item(i, 1);
        if (amountItem) {
            double baseEur = amountItem->data(Qt::UserRole).toDouble();
            double displayVal = baseEur * currentRate;

            amountItem->setText(QString("%1 %2").arg(displayVal, 0, 'f', 2).arg(currentSymbol));
        }
    }

    // 3. Ενημέρωση των στατιστικών
    updateStatsAndChart();
}
void MainWindow::showContextMenu(const QPoint &pos)
{
    // 1. Βρίσκουμε ποιο κελί πατήθηκε στον πίνακα
    QModelIndex proxyIndex = ui->expenseTable->indexAt(pos);
    if (!proxyIndex.isValid()) return; // Αν πατήθηκε κενό σημείο, σταματάμε

    // 2. Δημιουργούμε το μενού
    QMenu contextMenu(this);
    QAction *deleteAction = contextMenu.addAction("🗑️ Διαγραφή Εγγραφής");

    // 3. Εμφανίζουμε το μενού
    QAction *selectedAction = contextMenu.exec(ui->expenseTable->viewport()->mapToGlobal(pos));

    // 4. Αν πατήθηκε η Διαγραφή
    if (selectedAction == deleteAction) {
        // ✅ Διαγράφουμε τη γραμμή ΑΠΕΥΘΕΙΑΣ από το proxyModel!
        // Το proxyModel θα τη διαγράψει αυτόματα και από το tableModel!
        proxyModel->removeRow(proxyIndex.row());

        // Ενημερώνουμε Στατιστικά & Γράφημα
        updateStatsAndChart();
    }
}

void MainWindow::onFilterCategoryChanged(const QString &category)
{
    if (category== "Όλες οι Κατηγορίες"){
        proxyModel->setFilterFixedString("");
    }else{
        proxyModel->setFilterFixedString(category);
    }
}

void MainWindow::on_exportCsvButton_clicked()
{
    QString fileName=QFileDialog::getSaveFileName(this,"Εξαγωγή σε CSV","expences.csv","CSV files (*.csv)");
    if(fileName.isEmpty()) return;

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(this,"Σφάλμα","");
        return;
    }
    //UTF-8 BOM
    file.write("\xEF\xBB\xBF");
    QTextStream out(&file);
    out<<"Ημερομηνία;Κατηγορία;Πόσο\n";
    for (int i=0 ; i<proxyModel->rowCount(); ++i){
        //(έτσι αν ο χρήστης έχει βάλει Φίλτρο, θα εξαχθούν ΜΟΝΟ τα φιλτραρισμένα
        QString dateStr=proxyModel->data(proxyModel->index(i,0)).toString();
        QString categoryStr=proxyModel->data(proxyModel->index(i,1)).toString();
        QString amountStr=proxyModel->data(proxyModel->index(i,2)).toString();
        categoryStr.replace(";",",");
        out<<dateStr<<";"<<categoryStr<<";"<<amountStr<<"\n";
    }
    file.close();
    QMessageBox::information(this,"Επιτυχία","Η εξαγωγή σε CSV ολοκληρώθηκε με επιτυχία!");
}






