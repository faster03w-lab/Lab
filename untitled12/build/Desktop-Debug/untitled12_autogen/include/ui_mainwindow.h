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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLineEdit *lineEditTicket;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditDate;
    QLineEdit *lineEditPrize;
    QLabel *label_4;
    QLineEdit *lineEditName;
    QLabel *label_5;
    QRadioButton *radioWin;
    QRadioButton *radioLose;
    QLabel *label_6;
    QCheckBox *checkPresence;
    QCheckBox *checkLegal;
    QCheckBox *checkGift;
    QPushButton *btnReset;
    QPushButton *btnSave;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(414, 484);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 80, 61, 16));
        lineEditTicket = new QLineEdit(centralwidget);
        lineEditTicket->setObjectName("lineEditTicket");
        lineEditTicket->setGeometry(QRect(140, 80, 131, 24));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(70, 110, 31, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(70, 140, 31, 16));
        lineEditDate = new QLineEdit(centralwidget);
        lineEditDate->setObjectName("lineEditDate");
        lineEditDate->setGeometry(QRect(120, 110, 113, 24));
        lineEditPrize = new QLineEdit(centralwidget);
        lineEditPrize->setObjectName("lineEditPrize");
        lineEditPrize->setGeometry(QRect(110, 140, 91, 24));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(70, 170, 91, 16));
        lineEditName = new QLineEdit(centralwidget);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setGeometry(QRect(170, 170, 91, 24));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(70, 200, 61, 16));
        radioWin = new QRadioButton(centralwidget);
        radioWin->setObjectName("radioWin");
        radioWin->setGeometry(QRect(130, 200, 71, 21));
        radioLose = new QRadioButton(centralwidget);
        radioLose->setObjectName("radioLose");
        radioLose->setGeometry(QRect(210, 200, 91, 21));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(70, 230, 51, 16));
        checkPresence = new QCheckBox(centralwidget);
        checkPresence->setObjectName("checkPresence");
        checkPresence->setGeometry(QRect(130, 230, 131, 21));
        checkLegal = new QCheckBox(centralwidget);
        checkLegal->setObjectName("checkLegal");
        checkLegal->setGeometry(QRect(130, 250, 111, 21));
        checkGift = new QCheckBox(centralwidget);
        checkGift->setObjectName("checkGift");
        checkGift->setGeometry(QRect(130, 270, 71, 21));
        btnReset = new QPushButton(centralwidget);
        btnReset->setObjectName("btnReset");
        btnReset->setGeometry(QRect(90, 310, 81, 31));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Light, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Light, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Light, brush);
        btnReset->setPalette(palette);
        btnSave = new QPushButton(centralwidget);
        btnSave->setObjectName("btnSave");
        btnSave->setGeometry(QRect(240, 310, 81, 31));
        QPalette palette1;
        QBrush brush1(QColor(0, 170, 0, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        btnSave->setPalette(palette1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 414, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\241\321\207\320\260\321\201\321\202\320\273\320\270\320\262\321\213\320\271 \320\261\320\270\320\273\320\265\321\202", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\342\204\226 \320\261\320\270\320\273\320\265\321\202\320\260", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\267", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217 \320\277\320\276\320\272\321\203\320\277\320\260\321\202\320\265\320\273\321\217", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202", nullptr));
        radioWin->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\261\320\265\320\264\320\260", nullptr));
        radioLose->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\243\321\201\320\273\320\276\320\262\320\270\321\217", nullptr));
        checkPresence->setText(QCoreApplication::translate("MainWindow", "\320\233\320\270\321\207\320\275\320\276\320\265 \320\277\321\200\320\270\321\201\321\203\321\202\321\201\320\262\320\270\320\265", nullptr));
        checkLegal->setText(QCoreApplication::translate("MainWindow", "\320\242\320\276\320\273\321\214\320\272\320\276 \321\216\321\200.\320\273\320\270\321\206\320\260", nullptr));
        checkGift->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\320\260\321\200\320\276\320\272", nullptr));
        btnReset->setText(QCoreApplication::translate("MainWindow", "\320\241\320\261\321\200\320\276\321\201", nullptr));
        btnSave->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
