#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Программа 1: Создание мебели");
}

MainWindow::~MainWindow()
{
    delete ui;
}

Furniture MainWindow::getFurnitureFromForm()
{
    QString name = ui->lineEditName->text();
    QString description = ui->lineEditDescription->text();
    int legs = ui->spinBoxLegs->value();
    int handles = ui->spinBoxHandles->value();
    int drawers = ui->spinBoxDrawers->value();
    float cost = ui->doubleSpinBoxCost->value();

    return Furniture(name, description, legs, handles, drawers, cost);
}

void MainWindow::fillFormFromFurniture(const Furniture& f)
{
    ui->lineEditName->setText(f.getName());
    ui->lineEditDescription->setText(f.getDescription());
    ui->spinBoxLegs->setValue(f.getLegs());
    ui->spinBoxHandles->setValue(f.getHandles());
    ui->spinBoxDrawers->setValue(f.getDrawers());
    ui->doubleSpinBoxCost->setValue(f.getCost());
}

void MainWindow::saveToJsonFile(const QString& filename)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    Furniture newFurniture = getFurnitureFromForm();

    // Проверяем, не битый ли объект
    if (newFurniture.isBroken()) {
        QMessageBox::warning(this, "Ошибка", "Объект битый! Заполните все поля корректно.");
        return;
    }

    QFile file(filename);
    QJsonArray furnitureArray;

    // Если файл существует, читаем старые данные
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isArray()) {
            furnitureArray = doc.array();
        }
    }

    // Добавляем новый объект
    furnitureArray.append(newFurniture.toJson());

    // Сохраняем обратно
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument saveDoc(furnitureArray);
        file.write(saveDoc.toJson());
        file.close();
        QMessageBox::information(this, "Успех", "Объект сохранен в JSON файл!");
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл!");
    }
}

void MainWindow::loadFromTxtFile(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть TXT файл!");
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine().trimmed();

    if (line.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Файл пуст!");
        return;
    }

    // Разделяем по разделителю "/"
    QStringList parts = line.split('/');

    if (parts.size() != 6) {
        QMessageBox::warning(this, "Ошибка",
                             QString("Неправильный формат! Ожидается 6 полей, получено %1")
                             .arg(parts.size()));
        return;
    }

    // Заполняем форму
    ui->lineEditName->setText(parts[0]);
    ui->lineEditDescription->setText(parts[1]);

    bool legsOk, handlesOk, drawersOk, costOk;
    int legs = parts[2].toInt(&legsOk);
    int handles = parts[3].toInt(&handlesOk);
    int drawers = parts[4].toInt(&drawersOk);
    float cost = parts[5].toFloat(&costOk);

    if (legsOk) ui->spinBoxLegs->setValue(legs);
    else ui->spinBoxLegs->setValue(0);

    if (handlesOk) ui->spinBoxHandles->setValue(handles);
    else ui->spinBoxHandles->setValue(0);

    if (drawersOk) ui->spinBoxDrawers->setValue(drawers);
    else ui->spinBoxDrawers->setValue(0);

    if (costOk) ui->doubleSpinBoxCost->setValue(cost);
    else ui->doubleSpinBoxCost->setValue(0);

    file.close();
    QMessageBox::information(this, "Успех", "Данные из TXT загружены в форму!");
}

void MainWindow::on_saveButton_clicked()
{
    // Выбираем JSON файл для сохранения
    QString filename = QFileDialog::getSaveFileName(this,
                                                    "Сохранить в JSON",
                                                    "",
                                                    "JSON файлы (*.json)");
    if (filename.isEmpty()) return;

    // Если файл не кончается на .json, добавляем
    if (!filename.endsWith(".json", Qt::CaseInsensitive)) {
        filename += ".json";
    }

    saveToJsonFile(filename);
}

void MainWindow::on_clearButton_clicked()
{
    ui->lineEditName->clear();
    ui->lineEditDescription->clear();
    ui->spinBoxLegs->setValue(0);
    ui->spinBoxHandles->setValue(0);
    ui->spinBoxDrawers->setValue(0);
    ui->doubleSpinBoxCost->setValue(0);
}

void MainWindow::on_loadFromTxtButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    "Загрузить из TXT",
                                                    "",
                                                    "Текстовые файлы (*.txt)");
    if (filename.isEmpty()) return;
    loadFromTxtFile(filename);
}
