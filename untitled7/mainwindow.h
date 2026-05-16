#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "Furniture.h"

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
    void on_loadButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<Furniture> validFurniture;
    std::vector<Furniture> brokenFurniture;

    void loadFromJsonFile(const QString& filename);
    void displayTables();
    void saveBrokenToFile(const QString& filename);
};

#endif // MAINWINDOW_H
