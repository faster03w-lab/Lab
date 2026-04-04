#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnReset_clicked();
    void onSave_clicked();

private:
    Ui::MainWindow *ui;
    void setupValidators();
    void saveToFile();

    bool isValidName(const QString &name);
    bool isValidDate(const QString &dateStr);
};
#endif // MAINWINDOW_H
