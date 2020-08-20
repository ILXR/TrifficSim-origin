/********************************************************************************
** Form generated from reading UI file 'Circle_Timing.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CIRCLE_TIMING_H
#define UI_CIRCLE_TIMING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Circle_TimingClass
{
public:
    QGridLayout *gridLayout;
    QTextEdit *Result;

    void setupUi(QWidget *Circle_TimingClass)
    {
        if (Circle_TimingClass->objectName().isEmpty())
            Circle_TimingClass->setObjectName(QString::fromUtf8("Circle_TimingClass"));
        Circle_TimingClass->resize(460, 772);
        Circle_TimingClass->setMinimumSize(QSize(460, 430));
        Circle_TimingClass->setMaximumSize(QSize(1000, 1300));
        gridLayout = new QGridLayout(Circle_TimingClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Result = new QTextEdit(Circle_TimingClass);
        Result->setObjectName(QString::fromUtf8("Result"));
        Result->setMinimumSize(QSize(400, 380));
        Result->setMaximumSize(QSize(1000, 1300));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(9);
        Result->setFont(font);
        Result->setReadOnly(true);

        gridLayout->addWidget(Result, 0, 0, 1, 1);


        retranslateUi(Circle_TimingClass);

        QMetaObject::connectSlotsByName(Circle_TimingClass);
    } // setupUi

    void retranslateUi(QWidget *Circle_TimingClass)
    {
        Circle_TimingClass->setWindowTitle(QApplication::translate("Circle_TimingClass", "\350\275\246\351\201\223\351\205\215\346\227\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Circle_TimingClass: public Ui_Circle_TimingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CIRCLE_TIMING_H
