#include "mainwindow.h"
#include <QFile>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QQueue>
#include <QPen>
#include <QBrush>
#include <QGraphicsTextItem>
#include <QRegularExpression>
#include <QResizeEvent>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), root(nullptr)
{


    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // гафическая сцена и вид
    scene = new QGraphicsScene(this);
    graphicsView = new QGraphicsView(scene);
    graphicsView->setRenderHint(QPainter::Antialiasing);

    // текстовое поле для вывода
    textEditResult = new QTextEdit();
    textEditResult->setReadOnly(true);

    // кнопки
    QPushButton* btnLoadFile = new QPushButton("Загрузить файл");
    QPushButton* btnPreOrder = new QPushButton("Обход (УЛП)");
    QPushButton* btnHeight = new QPushButton("Высота дерева");
    QPushButton* btnSave = new QPushButton("Сохранить результат");

    // соединяем кнопки со слотами
    connect(btnLoadFile, &QPushButton::clicked, this, &MainWindow::loadFile);
    connect(btnPreOrder, &QPushButton::clicked, this, &MainWindow::doPreOrder);
    connect(btnHeight, &QPushButton::clicked, this, &MainWindow::doHeight);
    connect(btnSave, &QPushButton::clicked, this, &MainWindow::saveResult);

    //компоновка
    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->addWidget(textEditResult);
    rightLayout->addWidget(btnLoadFile);
    rightLayout->addWidget(btnPreOrder);
    rightLayout->addWidget(btnHeight);
    rightLayout->addWidget(btnSave);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->addWidget(graphicsView, 2); // Графика занимает
    mainLayout->addLayout(rightLayout, 1);  // Кнопки

    resize(900, 600);
    setWindowTitle("Лабораторная работа №3. Бинарные деревья");

    // создаем тестовый файл tree при первом запуске
    QFile file("tree.txt");
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << "1\n4 3\n2 - 9 7\n"; // данные из задания
            file.close();
        }
    }
}

MainWindow::~MainWindow()
{
    clearTree(root);
}




void MainWindow::clearTree(TreeNode* node) {
    if (!node) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

void MainWindow::loadFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Text Files (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    // разбиваем текст на числа и прочерки
    QStringList tokens = content.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    if (tokens.isEmpty()) return;

    clearTree(root);
    root = buildTree(tokens);

    drawTree();
    textEditResult->clear();
}


TreeNode* MainWindow::buildTree(const QStringList& tokens) {
    if (tokens.isEmpty()) return nullptr;

    TreeNode* newRoot = new TreeNode(tokens[0].toInt());
    QQueue<TreeNode*> queue;
    queue.enqueue(newRoot);

    int i = 1;
    while (i < tokens.size() && !queue.isEmpty()) {
        TreeNode* curr = queue.dequeue();

        //левый ребенок
        if (i < tokens.size()) {
            if (tokens[i] != "-") { // если это не прочерк, создаем узел
                curr->left = new TreeNode(tokens[i].toInt());
                queue.enqueue(curr->left);
            }
            i++;
        }

        //правый ребенок
        if (i < tokens.size()) {
            if (tokens[i] != "-") {
                curr->right = new TreeNode(tokens[i].toInt());
                queue.enqueue(curr->right);
            }
            i++;
        }
    }
    return newRoot;
}

void MainWindow::preOrder(TreeNode* node, QString& result) {
    if (!node) return;
    result += QString::number(node->value) + " ";
    preOrder(node->left, result);
    preOrder(node->right, result);
}

int MainWindow::getHeight(TreeNode* node) {
    if (!node) return 0;
    return 1 + qMax(getHeight(node->left), getHeight(node->right));
}

// отрисовка

void MainWindow::drawTree() {
    scene->clear();
    if (!root) return;

    //дерево
    drawNode(root, 0, 0, 200);

    //масштабируем и центрируем
    graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void MainWindow::drawNode(TreeNode* node, qreal x, qreal y, qreal xOffset) {
    if (!node) return;
    qreal radius = 20;

    // круг узла
    scene->addEllipse(x - radius, y - radius, radius * 2, radius * 2, QPen(Qt::black), QBrush(Qt::white));

    // текст внутри
    QGraphicsTextItem* text = scene->addText(QString::number(node->value));
    text->setPos(x - text->boundingRect().width()/2, y - text->boundingRect().height()/2);

    qreal childY = y + 70;
    qreal leftX = x - xOffset;
    qreal rightX = x + xOffset;

    if (node->left) {
        scene->addLine(x, y + radius, leftX, childY - radius, QPen(Qt::black));
        drawNode(node->left, leftX, childY, xOffset / 1.8);
    }
    if (node->right) {
        scene->addLine(x, y + radius, rightX, childY - radius, QPen(Qt::black));
        drawNode(node->right, rightX, childY, xOffset / 1.8);
    }
}


void MainWindow::doPreOrder() {
    if (!root) {
        QMessageBox::information(this, "Info", "Дерево пустое. Загрузите файл.");
        return;
    }
    QString result;
    preOrder(root, result);
    lastTraversalResult = result;
    textEditResult->setText("Префиксный обход (УЛП):\n" + result);
}

void MainWindow::doHeight() {
    if (!root) {
        QMessageBox::information(this, "Info", "Дерево пустое. Загрузите файл.");
        return;
    }
    int h = getHeight(root);
    textEditResult->append("\nВысота дерева: " + QString::number(h));
}

void MainWindow::saveResult() {
    if (lastTraversalResult.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сначала выполните обход, чтобы было что сохранять!");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить результат", "result.txt", "Text Files (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << lastTraversalResult;
        file.close();
        QMessageBox::information(this, "Успех", "Результат успешно сохранен в файл!");
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл.");
    }
}
