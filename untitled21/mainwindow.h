#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include <QTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>

#include "graph.h"
#include "graphwidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadMap();
    void onSimulateTraffic();
    void onBuildPath();
    void onSavePath();
    void onShowAdjacencyList();
    void onVertexDoubleClicked(const QString& name);

private:
    void setupUI();
    void initGraph();
    void updateLists();
    void syncLists();
    void recalculatePath();

    Graph *graph;
    GraphWidget *graphWidget;

    QPushButton *btnLoadMap;
    QPushButton *btnSimulate;
    QPushButton *btnBuild;
    QPushButton *btnSave;
    QPushButton *btnAdjacency;

    QListWidget *listStart;
    QListWidget *listEnd;
    QTextEdit *textPath;

    QString selectedStart;
    QString selectedEnd;
    QVector<QString> currentPath;

    QString hiddenInStart;
    QString hiddenInEnd;
};

#endif // MAINWINDOW_H
