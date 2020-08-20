/********************************************************************************
** Form generated from reading UI file 'Ordinary_Vehicles_Inputs.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDINARY_VEHICLES_INPUTS_H
#define UI_ORDINARY_VEHICLES_INPUTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Ordinary_Vehicles_InputsClass
{
public:
    QWidget *centralwidget;
    QPushButton *OK;
    QPushButton *Cancel;
    QFrame *line;
    QPushButton *Random;
    QSplitter *splitter_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *Max;
    QPushButton *Min;
    QSplitter *splitter;
    QLineEdit *L1;
    QLineEdit *L2;
    QLineEdit *L3;
    QLineEdit *L4;
    QLineEdit *L5;
    QLineEdit *L6;
    QLineEdit *L7;
    QLineEdit *L8;

    void setupUi(QMainWindow *Ordinary_Vehicles_InputsClass)
    {
        if (Ordinary_Vehicles_InputsClass->objectName().isEmpty())
            Ordinary_Vehicles_InputsClass->setObjectName(QString::fromUtf8("Ordinary_Vehicles_InputsClass"));
        Ordinary_Vehicles_InputsClass->resize(400, 500);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Ordinary_Vehicles_InputsClass->sizePolicy().hasHeightForWidth());
        Ordinary_Vehicles_InputsClass->setSizePolicy(sizePolicy);
        Ordinary_Vehicles_InputsClass->setMinimumSize(QSize(400, 500));
        Ordinary_Vehicles_InputsClass->setMaximumSize(QSize(400, 500));
        centralwidget = new QWidget(Ordinary_Vehicles_InputsClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        OK = new QPushButton(centralwidget);
        OK->setObjectName(QString::fromUtf8("OK"));
        OK->setGeometry(QRect(190, 460, 90, 28));
        sizePolicy.setHeightForWidth(OK->sizePolicy().hasHeightForWidth());
        OK->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(10);
        OK->setFont(font);
        OK->setCursor(QCursor(Qt::ArrowCursor));
        Cancel = new QPushButton(centralwidget);
        Cancel->setObjectName(QString::fromUtf8("Cancel"));
        Cancel->setGeometry(QRect(300, 460, 90, 28));
        Cancel->setFont(font);
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(10, 440, 378, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        Random = new QPushButton(centralwidget);
        Random->setObjectName(QString::fromUtf8("Random"));
        Random->setGeometry(QRect(150, 360, 93, 28));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(11);
        Random->setFont(font1);
        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setGeometry(QRect(110, 60, 50, 241));
        splitter_2->setOrientation(Qt::Vertical);
        label = new QLabel(splitter_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(50, 25));
        label->setMaximumSize(QSize(50, 25));
        label->setFont(font1);
        splitter_2->addWidget(label);
        label_2 = new QLabel(splitter_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(50, 25));
        label_2->setMaximumSize(QSize(50, 25));
        label_2->setFont(font1);
        splitter_2->addWidget(label_2);
        label_3 = new QLabel(splitter_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(50, 25));
        label_3->setMaximumSize(QSize(50, 25));
        label_3->setFont(font1);
        splitter_2->addWidget(label_3);
        label_4 = new QLabel(splitter_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(50, 25));
        label_4->setMaximumSize(QSize(50, 25));
        label_4->setFont(font1);
        splitter_2->addWidget(label_4);
        label_5 = new QLabel(splitter_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(50, 25));
        label_5->setMaximumSize(QSize(50, 25));
        label_5->setFont(font1);
        splitter_2->addWidget(label_5);
        label_6 = new QLabel(splitter_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(50, 25));
        label_6->setMaximumSize(QSize(50, 25));
        label_6->setFont(font1);
        splitter_2->addWidget(label_6);
        label_7 = new QLabel(splitter_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(50, 25));
        label_7->setMaximumSize(QSize(50, 25));
        label_7->setFont(font1);
        splitter_2->addWidget(label_7);
        label_8 = new QLabel(splitter_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(50, 25));
        label_8->setMaximumSize(QSize(50, 25));
        label_8->setFont(font1);
        splitter_2->addWidget(label_8);
        Max = new QPushButton(centralwidget);
        Max->setObjectName(QString::fromUtf8("Max"));
        Max->setGeometry(QRect(270, 360, 93, 28));
        Max->setFont(font1);
        Min = new QPushButton(centralwidget);
        Min->setObjectName(QString::fromUtf8("Min"));
        Min->setGeometry(QRect(30, 360, 93, 28));
        Min->setFont(font1);
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(190, 60, 80, 241));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(9);
        splitter->setFont(font2);
        splitter->setOrientation(Qt::Vertical);
        L1 = new QLineEdit(splitter);
        L1->setObjectName(QString::fromUtf8("L1"));
        L1->setMinimumSize(QSize(80, 25));
        L1->setMaximumSize(QSize(80, 25));
        L1->setFont(font2);
        splitter->addWidget(L1);
        L2 = new QLineEdit(splitter);
        L2->setObjectName(QString::fromUtf8("L2"));
        L2->setMinimumSize(QSize(80, 25));
        L2->setMaximumSize(QSize(80, 25));
        L2->setFont(font2);
        splitter->addWidget(L2);
        L3 = new QLineEdit(splitter);
        L3->setObjectName(QString::fromUtf8("L3"));
        L3->setMinimumSize(QSize(80, 25));
        L3->setMaximumSize(QSize(80, 25));
        L3->setFont(font2);
        splitter->addWidget(L3);
        L4 = new QLineEdit(splitter);
        L4->setObjectName(QString::fromUtf8("L4"));
        L4->setMinimumSize(QSize(80, 25));
        L4->setMaximumSize(QSize(80, 25));
        L4->setFont(font2);
        splitter->addWidget(L4);
        L5 = new QLineEdit(splitter);
        L5->setObjectName(QString::fromUtf8("L5"));
        L5->setMinimumSize(QSize(80, 25));
        L5->setMaximumSize(QSize(80, 25));
        L5->setFont(font2);
        splitter->addWidget(L5);
        L6 = new QLineEdit(splitter);
        L6->setObjectName(QString::fromUtf8("L6"));
        L6->setMinimumSize(QSize(80, 25));
        L6->setMaximumSize(QSize(80, 25));
        L6->setFont(font2);
        splitter->addWidget(L6);
        L7 = new QLineEdit(splitter);
        L7->setObjectName(QString::fromUtf8("L7"));
        L7->setMinimumSize(QSize(80, 25));
        L7->setMaximumSize(QSize(80, 25));
        L7->setFont(font2);
        splitter->addWidget(L7);
        L8 = new QLineEdit(splitter);
        L8->setObjectName(QString::fromUtf8("L8"));
        L8->setMinimumSize(QSize(80, 25));
        L8->setMaximumSize(QSize(80, 25));
        L8->setFont(font2);
        splitter->addWidget(L8);
        Ordinary_Vehicles_InputsClass->setCentralWidget(centralwidget);

        retranslateUi(Ordinary_Vehicles_InputsClass);

        QMetaObject::connectSlotsByName(Ordinary_Vehicles_InputsClass);
    } // setupUi

    void retranslateUi(QMainWindow *Ordinary_Vehicles_InputsClass)
    {
        Ordinary_Vehicles_InputsClass->setWindowTitle(QApplication::translate("Ordinary_Vehicles_InputsClass", "\346\231\256\351\200\232\350\267\257\345\217\243\350\275\246\350\276\206\350\276\223\345\205\245", nullptr));
        OK->setText(QApplication::translate("Ordinary_Vehicles_InputsClass", "\347\241\256\350\256\244", nullptr));
        Cancel->setText(QApplication::translate("Ordinary_Vehicles_InputsClass", "\345\217\226\346\266\210", nullptr));
        Random->setText(QApplication::translate("Ordinary_Vehicles_InputsClass", "\351\232\217\346\234\272\345\200\274", nullptr));
        label->setText(QApplication::translate("Ordinary_Vehicles_InputsClass", "L1:", nullptr));
        label_2->setText(QApplication::translate("Ordinary_Vehicles_InputsClass", "L2:", nullptr));
        label_3->setText(QApplication::translate("Ordinary_Vehicles_InputsClass", "L3:", nullptr));
        label_4->setText(QApplication::translate("Ordinary_Vehicles_InputsClass", "L4:", nullptr));
        label_5->setText(QApplication::translate("Ordinary_Vehicles_InputsClass", "L5:", nullptr));
        label_6->setText(QApplication::translate("Ordinary_Vehicles_InputsClass", "L6:", nullptr));
        label_7->setText(QApplication::translate("Ordinary_Vehicles_InputsClass", "L7:", nullptr));
        label_8->setText(QApplication::translate("Ordinary_Vehicles_InputsClass", "L8:", nullptr));
        Max->setText(QApplication::translate("Ordinary_Vehicles_InputsClass", "\346\234\200\345\244\247\345\200\274", nullptr));
        Min->setText(QApplication::translate("Ordinary_Vehicles_InputsClass", "\346\234\200\345\260\217\345\200\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Ordinary_Vehicles_InputsClass: public Ui_Ordinary_Vehicles_InputsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDINARY_VEHICLES_INPUTS_H
