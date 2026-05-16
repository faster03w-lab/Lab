#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Программа 2: Просмотр мебели");

    ui->tableWidgetValid->setColumnCount(6);
    ui->tableWidgetValid->setHorizontalHeaderLabels(
        QStringList() << "Название" << "Описание" << "Ножки"
                      << "Ручки" << "Ящики" << "Стоимость");

    ui->tableWidgetBroken->setColumnCount(6);
    ui->tableWidgetBroken->setHorizontalHeaderLabels(
        QStringList() << "Название" << "Описание" << "Ножки"
                      << "Ручки" << "Ящики" << "Стоимость");

    ui->tableWidgetValid->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetBroken->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFromJsonFile(const QString& filename)
{
    validFurniture.clear();
    brokenFurniture.clear();

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть JSON файл!");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        QMessageBox::warning(this, "Ошибка", "JSON файл должен содержать массив объектов!");
        return;
    }

    QJsonArray furnitureArray = doc.array();

    for (const QJsonValue& value : furnitureArray) {
        if (!value.isObject()) {
            Furniture broken;
            brokenFurniture.push_back(broken);
            continue;
        }

        QJsonObject obj = value.toObject();
        Furniture f = Furniture::fromJson(obj);

        if (f.isBroken()) {
            brokenFurniture.push_back(f);
        } else {
            validFurniture.push_back(f);
        }
    }

    std::sort(validFurniture.begin(), validFurniture.end());

    QString brokenFilename = filename;
    brokenFilename.replace(".json", "_broken.json");
    saveBrokenToFile(brokenFilename);

    displayTables();

    QMessageBox::information(this, "Готово",
                             QString("Загружено: %1 корректных, %2 битых объектов\n"
                                     "Битые сохранены в: %3")
                                 .arg(validFurniture.size())
                                 .arg(brokenFurniture.size())
                                 .arg(brokenFilename));
}

void MainWindow::saveBrokenToFile(const QString& filename)
{
    QFile file(filename);

    if (brokenFurniture.empty()) {
        // Создаём пустой файл (0 байт)
        if (file.open(QIODevice::WriteOnly)) {
            file.close();
        }
        return;
    }

    QJsonArray brokenArray;
    for (const Furniture& f : brokenFurniture) {
        brokenArray.append(f.toJson());
    }

    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(brokenArray);
        file.write(doc.toJson());
        file.close();
    }
}

void MainWindow::displayTables()
{
    ui->tableWidgetValid->setRowCount(validFurniture.size());

    for (size_t i = 0; i < validFurniture.size(); i++) {
        Furniture& f = validFurniture[i];

        ui->tableWidgetValid->setItem(i, 0, new QTableWidgetItem(f.getName()));
        ui->tableWidgetValid->setItem(i, 1, new QTableWidgetItem(f.getDescription()));
        ui->tableWidgetValid->setItem(i, 2, new QTableWidgetItem(QString::number(f.getLegs())));
        ui->tableWidgetValid->setItem(i, 3, new QTableWidgetItem(QString::number(f.getHandles())));
        ui->tableWidgetValid->setItem(i, 4, new QTableWidgetItem(QString::number(f.getDrawers())));
        ui->tableWidgetValid->setItem(i, 5, new QTableWidgetItem(QString::number(f.getCost())));
    }

    ui->tableWidgetBroken->setRowCount(brokenFurniture.size());

    for (size_t i = 0; i < brokenFurniture.size(); i++) {
        Furniture& f = brokenFurniture[i];

        QString name = f.getName().isEmpty() ? "(пусто)" : f.getName();
        QString description = f.getDescription();
        QString legs = (f.getLegs() < 0) ? "(не указано)" : QString::number(f.getLegs());
        QString handles = (f.getHandles() < 0) ? "(не указано)" : QString::number(f.getHandles());
        QString drawers = (f.getDrawers() < 0) ? "(не указано)" : QString::number(f.getDrawers());
        QString cost = (f.getCost() < 0) ? "(не указано)" : QString::number(f.getCost());

        ui->tableWidgetBroken->setItem(i, 0, new QTableWidgetItem(name));
        ui->tableWidgetBroken->setItem(i, 1, new QTableWidgetItem(description));
        ui->tableWidgetBroken->setItem(i, 2, new QTableWidgetItem(legs));
        ui->tableWidgetBroken->setItem(i, 3, new QTableWidgetItem(handles));
        ui->tableWidgetBroken->setItem(i, 4, new QTableWidgetItem(drawers));
        ui->tableWidgetBroken->setItem(i, 5, new QTableWidgetItem(cost));
    }

    ui->tableWidgetValid->resizeColumnsToContents();
    ui->tableWidgetBroken->resizeColumnsToContents();
}

void MainWindow::on_loadButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    "Выберите JSON файл",
                                                    "",
                                                    "JSON файлы (*.json)");
    if (filename.isEmpty()) return;
    loadFromJsonFile(filename);
}
