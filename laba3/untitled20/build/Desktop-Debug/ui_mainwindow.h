/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Menu
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEditResult;
    QPushButton *btnLoadFile;
    QPushButton *btnPreOrder;
    QPushButton *btnHeight;
    QPushButton *btnSave;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Menu)
    {
        if (Menu->objectName().isEmpty())
            Menu->setObjectName("Menu");
        Menu->resize(1159, 600);
        centralwidget = new QWidget(Menu);
        centralwidget->setObjectName("centralwidget");
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(10, 60, 671, 341));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(730, 60, 258, 314));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        textEditResult = new QTextEdit(widget);
        textEditResult->setObjectName("textEditResult");

        verticalLayout->addWidget(textEditResult);

        btnLoadFile = new QPushButton(widget);
        btnLoadFile->setObjectName("btnLoadFile");

        verticalLayout->addWidget(btnLoadFile);

        btnPreOrder = new QPushButton(widget);
        btnPreOrder->setObjectName("btnPreOrder");

        verticalLayout->addWidget(btnPreOrder);

        btnHeight = new QPushButton(widget);
        btnHeight->setObjectName("btnHeight");

        verticalLayout->addWidget(btnHeight);

        btnSave = new QPushButton(widget);
        btnSave->setObjectName("btnSave");

        verticalLayout->addWidget(btnSave);

        Menu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Menu);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1159, 21));
        Menu->setMenuBar(menubar);
        statusbar = new QStatusBar(Menu);
        statusbar->setObjectName("statusbar");
        Menu->setStatusBar(statusbar);

        retranslateUi(Menu);

        QMetaObject::connectSlotsByName(Menu);
    } // setupUi

    void retranslateUi(QMainWindow *Menu)
    {
        Menu->setWindowTitle(QCoreApplication::translate("Menu", "MainWindow", nullptr));
        btnLoadFile->setText(QCoreApplication::translate("Menu", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        btnPreOrder->setText(QCoreApplication::translate("Menu", "\320\236\320\261\321\205\320\276\320\264 (\320\243\320\233\320\237)", nullptr));
        btnHeight->setText(QCoreApplication::translate("Menu", "\320\222\321\213\321\201\320\276\321\202\320\260 \320\264\320\265\321\200\320\265\320\262\320\260", nullptr));
        btnSave->setText(QCoreApplication::translate("Menu", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Menu: public Ui_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
