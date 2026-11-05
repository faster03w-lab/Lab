#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTextEdit>
#include <QPushButton>
#include <QList>
#include <QString>
#include <QStringList>

// структура узла дерева
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadFile();
    void doPreOrder();
    void doHeight();
    void saveResult();

private:
    TreeNode* root;
    QGraphicsScene* scene;
    QGraphicsView* graphicsView;
    QTextEdit* textEditResult;
    QString lastTraversalResult;

    // вспомогательные методы
    void clearTree(TreeNode* node);
    TreeNode* buildTree(const QStringList& tokens);
    void drawTree();
    void drawNode(TreeNode* node, qreal x, qreal y, qreal xOffset);
    int getHeight(TreeNode* node);
    void preOrder(TreeNode* node, QString& result);
};

#endif // MAINWINDOW_H
