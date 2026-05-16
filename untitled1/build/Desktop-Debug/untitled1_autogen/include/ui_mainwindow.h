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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLineEdit *lineEditName;
    QLabel *label_2;
    QLineEdit *lineEditDescription;
    QSpinBox *spinBoxLegs;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *spinBoxHandles;
    QLabel *label_5;
    QSpinBox *spinBoxDrawers;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBoxCost;
    QPushButton *saveButton;
    QPushButton *loadFromTxtButton;
    QPushButton *clearButton;
    QLabel *label_7;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(410, 319);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 30, 61, 16));
        lineEditName = new QLineEdit(centralwidget);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setGeometry(QRect(90, 30, 113, 22));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 60, 61, 16));
        lineEditDescription = new QLineEdit(centralwidget);
        lineEditDescription->setObjectName("lineEditDescription");
        lineEditDescription->setGeometry(QRect(90, 60, 113, 22));
        spinBoxLegs = new QSpinBox(centralwidget);
        spinBoxLegs->setObjectName("spinBoxLegs");
        spinBoxLegs->setGeometry(QRect(110, 90, 42, 22));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 90, 81, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 120, 81, 16));
        spinBoxHandles = new QSpinBox(centralwidget);
        spinBoxHandles->setObjectName("spinBoxHandles");
        spinBoxHandles->setGeometry(QRect(110, 120, 42, 22));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 150, 91, 16));
        spinBoxDrawers = new QSpinBox(centralwidget);
        spinBoxDrawers->setObjectName("spinBoxDrawers");
        spinBoxDrawers->setGeometry(QRect(120, 150, 42, 22));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 180, 61, 16));
        doubleSpinBoxCost = new QDoubleSpinBox(centralwidget);
        doubleSpinBoxCost->setObjectName("doubleSpinBoxCost");
        doubleSpinBoxCost->setGeometry(QRect(90, 180, 62, 22));
        doubleSpinBoxCost->setMaximum(999990000.000000000000000);
        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName("saveButton");
        saveButton->setGeometry(QRect(20, 210, 111, 24));
        loadFromTxtButton = new QPushButton(centralwidget);
        loadFromTxtButton->setObjectName("loadFromTxtButton");
        loadFromTxtButton->setGeometry(QRect(150, 210, 101, 24));
        clearButton = new QPushButton(centralwidget);
        clearButton->setObjectName("clearButton");
        clearButton->setGeometry(QRect(270, 210, 75, 24));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 0, 81, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 410, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273-\320\262\320\276 \320\275\320\276\320\266\320\265\320\272", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273-\320\262\320\276 \321\200\321\203\321\207\320\265\320\272", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273-\320\262\320\276 \321\217\321\211\320\270\320\272\320\276\320\262", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\270\320\274\320\276\321\201\321\202\321\214", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\262 JSON", nullptr));
        loadFromTxtButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\270\320\267 TXT", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\262\321\213\320\271 \320\276\320\261\321\212\320\265\320\272\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
