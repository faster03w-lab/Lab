#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupValidators();

    // Цвет кнопок
    ui->btnReset->setStyleSheet("background-color: red; color: black;");
    ui->btnSave->setStyleSheet("background-color: green; color: black;");

    // Подключение кнопки Сохранить
    connect(ui->btnSave, &QPushButton::clicked, this, &MainWindow::onSave_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupValidators()
{
    // 1. Номер билета: строго формат "1-12345"
    QRegExp ticketRegExp("^\\d-\\d{5}$");
    ui->lineEditTicket->setValidator(new QRegExpValidator(ticketRegExp, this));

    // 2. Дата: строго формат дд.мм.гггг
    QRegExp dateRegExp("^([0-2]\\d|3[01])\\.(0\\d|1[0-2])\\.\\d{4}$");
    ui->lineEditDate->setValidator(new QRegExpValidator(dateRegExp, this));

    // 3. Приз: АНГЛ+РУС, первая заглавная, остальные строчные
    QRegExp prizeRegExp("^[А-ЯA-Z][а-яa-z]+$");
    ui->lineEditPrize->setValidator(new QRegExpValidator(prizeRegExp, this));

    // 4. Имя: ТОЛЬКО РУС, первая заглавная, остальные строчные
    QRegExp nameRegExp("^[А-Я][а-я]+$");
    ui->lineEditName->setValidator(new QRegExpValidator(nameRegExp, this));
}

void MainWindow::on_btnReset_clicked()
{
    // Очистка текстовых полей
    ui->lineEditTicket->clear();
    ui->lineEditDate->clear();
    ui->lineEditPrize->clear();
    ui->lineEditName->clear();

    // ?? ТРЮК: временно снимаем эксклюзивность для полного сброса
    ui->radioWin->setAutoExclusive(false);
    ui->radioLose->setAutoExclusive(false);
    ui->radioWin->setChecked(false);
    ui->radioLose->setChecked(false);
    ui->radioWin->setAutoExclusive(true);
    ui->radioLose->setAutoExclusive(true);

    // Сброс чекбоксов
    ui->checkPresence->setChecked(false);
    ui->checkLegal->setChecked(false);
    ui->checkGift->setChecked(false);
}

void MainWindow::onSave_clicked()
{
    // Проверка обязательных полей на пустоту
    // (формат уже проверяется валидаторами при вводе)

    if (ui->lineEditTicket->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Поле '№ билета' обязательно!");
        ui->lineEditTicket->setFocus();
        return;
    }

    if (ui->lineEditDate->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Поле 'Дата' обязательно!");
        ui->lineEditDate->setFocus();
        return;
    }

    if (ui->lineEditPrize->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Поле 'Приз' обязательно!");
        ui->lineEditPrize->setFocus();
        return;
    }

    if (ui->lineEditName->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Поле 'Имя покупателя' обязательно!");
        ui->lineEditName->setFocus();
        return;
    }

    // Проверка радио-кнопок
    if (!ui->radioWin->isChecked() && !ui->radioLose->isChecked()) {
        QMessageBox::warning(this, "Ошибка", "Выберите результат: Победа или Поражение!");
        return;
    }

    // Всё ок — сохраняем
    saveToFile();
}

void MainWindow::saveToFile()
{
    QFile file("result.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл для записи!");
        return;
    }

    QTextStream out(&file);

    // ?? Кодировка для нормального отображения в Блокноте Windows
    out.setCodec("CP1251");

    out << "=== СЧАСТЛИВЫЙ БИЛЕТ ===\n";
    out << "№ билета: " << ui->lineEditTicket->text() << "\n";
    out << "Дата: " << ui->lineEditDate->text() << "\n";
    out << "Приз: " << ui->lineEditPrize->text() << "\n";
    out << "Имя покупателя: " << ui->lineEditName->text() << "\n";

    if (ui->radioWin->isChecked())
        out << "Результат: Победа\n";
    else if (ui->radioLose->isChecked())
        out << "Результат: Поражение\n";
    else
        out << "Результат: не выбран\n";

    out << "Условия:\n";
    if (ui->checkPresence->isChecked())
        out << "  - Личное присутствие\n";
    if (ui->checkLegal->isChecked())
        out << "  - Только юр. лица\n";
    if (ui->checkGift->isChecked())
        out << "  - Подарок\n";

    file.close();
    QMessageBox::information(this, "Успех", "Данные сохранены в result.txt");
}
