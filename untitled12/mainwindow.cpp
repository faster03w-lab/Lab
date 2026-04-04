#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QStringConverter>

static const QStringList VALID_NAMES = {
    "Иван", "Мария", "Анна", "Дмитрий", "Елена", "Александр",
    "Ольга", "Сергей", "Наталья", "Андрей", "Екатерина", "Михаил",
    "Анастасия", "Владимир", "София", "Пётр", "Виктория", "Николай",
    "Полина", "Артём", "Юлия", "Максим", "Татьяна", "Алексей",
    "Дарья", "Константин", "Вера", "Роман", "Любовь", "Василий"
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupValidators();

    ui->btnReset->setStyleSheet("background-color: red; color: black; border-radius: 0px; border: 1px solid #333;");
    ui->btnSave->setStyleSheet("background-color: green; color: black; border-radius: 0px; border: 1px solid #333;");

    connect(ui->btnSave, &QPushButton::clicked, this, &MainWindow::onSave_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupValidators()
{

    QRegularExpression ticketRegExp(R"(^\d-\d{5}$)");
    ui->lineEditTicket->setValidator(new QRegularExpressionValidator(ticketRegExp, this));

    QRegularExpression dateRegExp(R"(^([0-2]\d|3[01])\.(0\d|1[0-2])\.([1-6]\d{3}|7000)$)");
    ui->lineEditDate->setValidator(new QRegularExpressionValidator(dateRegExp, this));

    QRegularExpression prizeRegExp(R"(^[А-ЯA-Z][а-яa-z\s]+$)");
    ui->lineEditPrize->setValidator(new QRegularExpressionValidator(prizeRegExp, this));

    QRegularExpression nameRegExp(R"(^[А-Я][а-я]+$)");
    ui->lineEditName->setValidator(new QRegularExpressionValidator(nameRegExp, this));
}

void MainWindow::on_btnReset_clicked()
{
    ui->lineEditTicket->clear();
    ui->lineEditDate->clear();
    ui->lineEditPrize->clear();
    ui->lineEditName->clear();

    ui->radioWin->setAutoExclusive(false);
    ui->radioLose->setAutoExclusive(false);
    ui->radioWin->setChecked(false);
    ui->radioLose->setChecked(false);
    ui->radioWin->setAutoExclusive(true);
    ui->radioLose->setAutoExclusive(true);

    if (ui->checkPresence) ui->checkPresence->setChecked(false);
    if (ui->checkLegal)    ui->checkLegal->setChecked(false);
    if (ui->checkGift)     ui->checkGift->setChecked(false);
}

void MainWindow::onSave_clicked()
{
    QRegularExpression ticketPattern(R"(^\d-\d{5}$)");
    if (!ticketPattern.match(ui->lineEditTicket->text()).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "№ билета должен быть в формате X-XXXXX!");
        ui->lineEditTicket->setFocus();
        return;
    }

    QRegularExpression datePattern(R"(^([0-2]\d|3[01])\.(0\d|1[0-2])\.([1-6]\d{3}|7000)$)");
    if (!datePattern.match(ui->lineEditDate->text()).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Дата должна быть в формате ДД.ММ.ГГГГ!");
        ui->lineEditDate->setFocus();
        return;
    }

    QRegularExpression prizeFormatPattern(R"(^[А-ЯA-Z][а-яa-z\s]+$)");
    if (!prizeFormatPattern.match(ui->lineEditPrize->text().trimmed()).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Приз должен начинаться с заглавной буквы и содержать только буквы и пробелы!");
        ui->lineEditPrize->setFocus();
        return;
    }

    QString prize = ui->lineEditPrize->text().trimmed();
    QRegularExpression prizeLengthPattern(R"(^.{2,50}$)");
    if (!prizeLengthPattern.match(prize).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Название приза должно содержать от 2 до 50 символов!");
        ui->lineEditPrize->setFocus();
        return;
    }

    QRegularExpression namePattern(R"(^[А-Я][а-я]+$)");
    if (!namePattern.match(ui->lineEditName->text().trimmed()).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Имя должно начинаться с заглавной буквы и содержать только строчные буквы!");
        ui->lineEditName->setFocus();
        return;
    }

    QString name = ui->lineEditName->text().trimmed();
    if (!VALID_NAMES.contains(name)) {
        QMessageBox::warning(this, "Ошибка", "Введите корректное имя из списка допустимых!");
        ui->lineEditName->setFocus();
        ui->lineEditName->selectAll();
        return;
    }

    if (!ui->radioWin->isChecked() && !ui->radioLose->isChecked()) {
        QMessageBox::warning(this, "Ошибка", "Необходимо выбрать результат: Победа или Поражение!");
        return;
    }

    if (!ui->checkPresence->isChecked() && !ui->checkLegal->isChecked() && !ui->checkGift->isChecked()) {
        QMessageBox::warning(this, "Ошибка", "Необходимо выбрать хотя бы одно условие!");
        return;
    }

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
    out.setEncoding(QStringConverter::Utf8);

    out << "=== Счастливый билет ===\n";
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
    if (ui->checkPresence && ui->checkPresence->isChecked())
        out << "  - Личное присутствие \n";
    if (ui->checkLegal && ui->checkLegal->isChecked())
        out << "  - Только юр.лица\n";
    if (ui->checkGift && ui->checkGift->isChecked())
        out << "  - Подарок\n";

    file.close();
    QMessageBox::information(this, "Успех", "Данные сохранены в result.txt");
}
