/********************************************************************************
** Form generated from reading UI file 'Simulation_Result.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATION_RESULT_H
#define UI_SIMULATION_RESULT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Simulation_ResultClass
{
public:
    QWidget *centralwidget;
    QPushButton *OK;
    QTextBrowser *result_test;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *road_text;
    QLineEdit *signal_text;

    void setupUi(QMainWindow *Simulation_ResultClass)
    {
        if (Simulation_ResultClass->objectName().isEmpty())
            Simulation_ResultClass->setObjectName(QString::fromUtf8("Simulation_ResultClass"));
        Simulation_ResultClass->resize(300, 480);
        Simulation_ResultClass->setMinimumSize(QSize(300, 480));
        Simulation_ResultClass->setMaximumSize(QSize(300, 480));
        centralwidget = new QWidget(Simulation_ResultClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        OK = new QPushButton(centralwidget);
        OK->setObjectName(QString::fromUtf8("OK"));
        OK->setGeometry(QRect(100, 430, 93, 28));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(11);
        OK->setFont(font);
        result_test = new QTextBrowser(centralwidget);
        result_test->setObjectName(QString::fromUtf8("result_test"));
        result_test->setGeometry(QRect(20, 150, 256, 251));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(10);
        result_test->setFont(font1);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 40, 90, 30));
        label->setMinimumSize(QSize(90, 30));
        label->setMaximumSize(QSize(90, 30));
        label->setFont(font1);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 90, 90, 30));
        label_2->setMinimumSize(QSize(90, 30));
        label_2->setMaximumSize(QSize(90, 30));
        label_2->setFont(font1);
        road_text = new QLineEdit(centralwidget);
        road_text->setObjectName(QString::fromUtf8("road_text"));
        road_text->setGeometry(QRect(140, 40, 113, 30));
        road_text->setMinimumSize(QSize(0, 30));
        road_text->setMaximumSize(QSize(16777215, 30));
        road_text->setFont(font1);
        road_text->setReadOnly(true);
        signal_text = new QLineEdit(centralwidget);
        signal_text->setObjectName(QString::fromUtf8("signal_text"));
        signal_text->setGeometry(QRect(140, 90, 113, 30));
        signal_text->setMinimumSize(QSize(0, 30));
        signal_text->setMaximumSize(QSize(16777215, 30));
        signal_text->setFont(font1);
        signal_text->setReadOnly(true);
        Simulation_ResultClass->setCentralWidget(centralwidget);

        retranslateUi(Simulation_ResultClass);

        QMetaObject::connectSlotsByName(Simulation_ResultClass);
    } // setupUi

    void retranslateUi(QMainWindow *Simulation_ResultClass)
    {
        Simulation_ResultClass->setWindowTitle(QApplication::translate("Simulation_ResultClass", "\344\273\277\347\234\237\347\273\223\346\236\234", nullptr));
        OK->setText(QApplication::translate("Simulation_ResultClass", "\347\241\256\350\256\244", nullptr));
        label->setText(QApplication::translate("Simulation_ResultClass", "\350\267\257\345\217\243\347\261\273\345\236\213\357\274\232", nullptr));
        label_2->setText(QApplication::translate("Simulation_ResultClass", "\351\205\215\346\227\266\346\226\271\346\241\210\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Simulation_ResultClass: public Ui_Simulation_ResultClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATION_RESULT_H
