#include "mainwindow.h"
#include <QDebug>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    graph(new Graph())
{
    setWindowTitle("Лабораторная работа №4");
    resize(1000, 700);

    setupUI();
    initGraph();
    updateLists();

    QString mapPath = "map.png";
    if (QFile::exists(mapPath)) {
        graphWidget->setMapImage(mapPath);
        qDebug() << "Карта загружена автоматически:" << mapPath;
    } else {
        qDebug() << "Файл карты не найден:" << mapPath;
    }
}

MainWindow::~MainWindow() {
    delete graph;
}

void MainWindow::setupUI() {
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QHBoxLayout *mainLayout = new QHBoxLayout(central);

    QVBoxLayout *controlLayout = new QVBoxLayout();
    controlLayout->setAlignment(Qt::AlignTop);

    btnLoadMap = new QPushButton("Загрузить карту", this);
    btnSimulate = new QPushButton("Имитация загруженности", this);
    btnBuild = new QPushButton("Вперёд! (Построить маршрут)", this);
    btnSave = new QPushButton("Сохранить маршрут", this);
    btnAdjacency = new QPushButton("Показать список смежности", this);

    btnBuild->setStyleSheet("font-weight: bold; font-size: 14px; padding: 10px;");

    controlLayout->addWidget(btnLoadMap);
    controlLayout->addWidget(btnSimulate);
    controlLayout->addWidget(btnAdjacency);
    controlLayout->addSpacing(20);

    QGroupBox *groupPath = new QGroupBox("Маршрут", this);
    QVBoxLayout *pathLayout = new QVBoxLayout(groupPath);

    QHBoxLayout *pointsLayout = new QHBoxLayout();

    QVBoxLayout *startLayout = new QVBoxLayout();
    startLayout->addWidget(new QLabel("Точка 1", this));
    listStart = new QListWidget(this);
    listStart->setMaximumHeight(150);
    startLayout->addWidget(listStart);
    pointsLayout->addLayout(startLayout);

    QVBoxLayout *endLayout = new QVBoxLayout();
    endLayout->addWidget(new QLabel("Точка 2", this));
    listEnd = new QListWidget(this);
    listEnd->setMaximumHeight(150);
    endLayout->addWidget(listEnd);
    pointsLayout->addLayout(endLayout);

    pathLayout->addLayout(pointsLayout);
    pathLayout->addWidget(btnBuild);
    controlLayout->addWidget(groupPath);

    textPath = new QTextEdit(this);
    textPath->setReadOnly(true);
    textPath->setMaximumHeight(80);
    textPath->setStyleSheet("font-size: 16px; font-weight: bold;");
    controlLayout->addWidget(textPath);

    controlLayout->addWidget(btnSave);
    controlLayout->addStretch();

    mainLayout->addLayout(controlLayout, 1);

    graphWidget = new GraphWidget(this);
    graphWidget->setGraph(graph);
    mainLayout->addWidget(graphWidget, 3);

    connect(btnLoadMap, &QPushButton::clicked, this, &MainWindow::onLoadMap);
    connect(btnSimulate, &QPushButton::clicked, this, &MainWindow::onSimulateTraffic);
    connect(btnBuild, &QPushButton::clicked, this, &MainWindow::onBuildPath);
    connect(btnSave, &QPushButton::clicked, this, &MainWindow::onSavePath);
    connect(btnAdjacency, &QPushButton::clicked, this, &MainWindow::onShowAdjacencyList);
    connect(graphWidget, &GraphWidget::vertexDoubleClicked,
            this, &MainWindow::onVertexDoubleClicked);
}

void MainWindow::initGraph() {
    // верхний ряд
    graph->addVertex("А",  25,  55);
    graph->addVertex("Б", 105,  45);
    graph->addVertex("В", 185,  45);
    graph->addVertex("Г", 285,  50);
    graph->addVertex("Д", 385,  65);
    graph->addVertex("Е", 465,  95);
    graph->addVertex("Ж", 535, 115);
    graph->addVertex("З", 585, 135);

    // средняя левая группа
    graph->addVertex("И",  65, 135);
    graph->addVertex("К", 125, 135);
    graph->addVertex("Л", 165, 175);

    // центральная горизонталь
    graph->addVertex("М",  65, 265);
    graph->addVertex("Н", 285, 270);
    graph->addVertex("О", 365, 290);
    graph->addVertex("П", 405, 290);
    graph->addVertex("Р", 465, 310);

    // левая вертикаль
    graph->addVertex("С",  55, 225);
    graph->addVertex("Т",  65, 265);

    // Нижний ряд
    graph->addVertex("У",  95, 370);
    graph->addVertex("Ф", 465, 370);

// ребра
    // Верхняя горизонталь
    graph->addEdge("А", "Б", 2);
    graph->addEdge("Б", "В", 2);
    graph->addEdge("В", "Г", 3);
    graph->addEdge("Г", "Д", 3);
    graph->addEdge("Д", "Е", 2);
    graph->addEdge("Е", "Ж", 2);
    graph->addEdge("Ж", "З", 2);

    // левая ветвь
    graph->addEdge("А", "И", 2);
    graph->addEdge("И", "К", 1);
    graph->addEdge("К", "Л", 1);
    graph->addEdge("Л", "С", 2);
    graph->addEdge("С", "Т", 1);

    // Диагонали
    graph->addEdge("В", "К", 3);
    graph->addEdge("Б", "К", 2);
    graph->addEdge("А", "С", 3);


    graph->addEdge("Т", "М", 2);

    // центральная горизонталь
    graph->addEdge("М", "Н", 5);
    graph->addEdge("Н", "О", 1);
    graph->addEdge("О", "П", 1);
    graph->addEdge("П", "Р", 2);

    // вертикали
    graph->addEdge("Г", "Н", 5);
    graph->addEdge("Е", "О", 4);
    graph->addEdge("Ж", "Р", 4);
    graph->addEdge("З", "Р", 5);

    // нижняя часть
    graph->addEdge("Т", "У", 3);
    graph->addEdge("У", "Ф", 7);
    graph->addEdge("Ф", "Р", 4);

    qDebug() << "Граф инициализирован:" << graph->getVertices().size() << "вершин,"
             << graph->getAllEdges().size() << "рёбер";
}

void MainWindow::updateLists() {
    QString oldStart = selectedStart;
    QString oldEnd = selectedEnd;

    listStart->clear();
    listEnd->clear();

    for (const Vertex& v : graph->getVertices()) {
        listStart->addItem(v.name);
        listEnd->addItem(v.name);
    }

    selectedStart = oldStart;
    selectedEnd = oldEnd;

    syncLists();

    static bool connected = false;
    if (!connected) {
        connect(listStart, &QListWidget::itemClicked, this, [this](QListWidgetItem* item) {
            selectedStart = item->text();
            syncLists();
        });
        connect(listEnd, &QListWidget::itemClicked, this, [this](QListWidgetItem* item) {
            selectedEnd = item->text();
            syncLists();
        });
        connected = true;
    }
}

void MainWindow::syncLists() {
    QString curStart = selectedStart;
    QString curEnd = selectedEnd;

    listStart->clear();
    listEnd->clear();

    for (const Vertex& v : graph->getVertices()) {
        if (v.name != curEnd) {
            listStart->addItem(v.name);
        }
        if (v.name != curStart) {
            listEnd->addItem(v.name);
        }
    }

    if (!curStart.isEmpty()) {
        for (int i = 0; i < listStart->count(); i++) {
            if (listStart->item(i)->text() == curStart) {
                listStart->setCurrentRow(i);
                break;
            }
        }
    }
    if (!curEnd.isEmpty()) {
        for (int i = 0; i < listEnd->count(); i++) {
            if (listEnd->item(i)->text() == curEnd) {
                listEnd->setCurrentRow(i);
                break;
            }
        }
    }
}

void MainWindow::recalculatePath() {
    if (selectedStart.isEmpty() || selectedEnd.isEmpty()) return;

    if (selectedStart == selectedEnd) {
        currentPath.clear();
        textPath->setPlainText("Точки должны быть разными!");
        graphWidget->clearPath();
        return;
    }

    QVector<QString> newPath = graph->findShortestPath(selectedStart, selectedEnd);

    if (newPath.isEmpty()) {
        currentPath.clear();
        textPath->setPlainText("Маршрут не найден!");
        graphWidget->clearPath();
        return;
    }

    currentPath = newPath;

    QStringList pathList = QStringList(currentPath.toList());
    QString pathStr = pathList.join(" - ");
    textPath->setPlainText(pathStr);

    double totalLength = 0;
    for (int i = 0; i < currentPath.size() - 1; i++) {
        double len = graph->getEdgeLength(currentPath[i], currentPath[i+1]);
        double k = graph->getEdgeK(currentPath[i], currentPath[i+1]);
        totalLength += len * k;
    }

    graphWidget->setPath(currentPath);
}

void MainWindow::onLoadMap() {
    QString fileName = QFileDialog::getOpenFileName(
        this, "Выберите изображение карты",
        QString(), "Images (*.png *.jpg *.bmp);;All files (*)"
        );

    if (fileName.isEmpty()) return;

    graphWidget->setMapImage(fileName);
    QMessageBox::information(this, "Успех", "Карта загружена");
}

void MainWindow::onSimulateTraffic() {
    graph->simulateTraffic();
    graphWidget->update();

    if (!currentPath.isEmpty()) {
        recalculatePath();
        QMessageBox::information(this, "Загруженность",
                                 "Коэффициенты загруженности дорог изменены.\n"
                                 "Цвета рёбер обновлены.\n"
                                 "Маршрут пересчитан.");
    } else {
        QMessageBox::information(this, "Загруженность",
                                 "Коэффициенты загруженности дорог изменены.\n"
                                 "Цвета рёбер обновлены.");
    }
}

void MainWindow::onBuildPath() {
    if (selectedStart.isEmpty() || selectedEnd.isEmpty()) {
        QMessageBox::warning(this, "Внимание",
                             "Выберите обе точки (1 и 2) в списках или двойным кликом на графе.");
        return;
    }

    if (selectedStart == selectedEnd) {
        QMessageBox::warning(this, "Внимание", "Точки должны быть разными!");
        return;
    }

    recalculatePath();

    if (currentPath.isEmpty()) {
        QMessageBox::warning(this, "Нет маршрута",
                             QString("Маршрут от %1 до %2 не найден!").arg(selectedStart, selectedEnd));
    }
}

void MainWindow::onSavePath() {
    if (currentPath.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Сначала постройте маршрут.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(
        this, "Сохранить маршрут",
        "route.txt", "Text files (*.txt);;All files (*)"
        );

    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "Маршрут: " << selectedStart << " -> " << selectedEnd << "\n";

        QStringList pathList = QStringList(currentPath.toList());
        out << "Путь: " << pathList.join(" - ") << "\n";

        double totalLength = 0;
        out << "\nДетализация:\n";
        for (int i = 0; i < currentPath.size() - 1; i++) {
            double len = graph->getEdgeLength(currentPath[i], currentPath[i+1]);
            double k = graph->getEdgeK(currentPath[i], currentPath[i+1]);
            double w = len * k;
            totalLength += w;
            out << QString("%1 -> %2: длина=%3, k=%4, вес=%5\n")
                       .arg(currentPath[i], currentPath[i+1])
                       .arg(len, 0, 'f', 0)
                       .arg(k, 0, 'f', 1)
                       .arg(w, 0, 'f', 1);
        }
        out << "\nИтого: " << totalLength << " км\n";
        file.close();

        QMessageBox::information(this, "Успех", "Маршрут сохранён в файл:\n" + fileName);
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл.");
    }
}

void MainWindow::onShowAdjacencyList() {
    textPath->setPlainText(graph->getAdjacencyListString());
    QMessageBox::information(this, "Список смежности",
                             "Список смежности выведен в поле результата.");
}

void MainWindow::onVertexDoubleClicked(const QString& name) {
    if (selectedStart.isEmpty()) {
        selectedStart = name;
        syncLists();
    } else if (selectedEnd.isEmpty() && name != selectedStart) {
        selectedEnd = name;
        syncLists();
    } else if (name == selectedStart) {
        QMessageBox::information(this, "Внимание", "Точки должны быть разными!");
    } else {
        selectedStart = name;
        selectedEnd.clear();
        syncLists();
    }
}
