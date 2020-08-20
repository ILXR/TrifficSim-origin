/********************************************************************************
** Form generated from reading UI file 'Simulation_Configure.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATION_CONFIGURE_H
#define UI_SIMULATION_CONFIGURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Simulation_ConfigureClass
{
public:
    QWidget *centralwidget;
    QFrame *line_2;
    QPushButton *OK;
    QPushButton *Cancel;
    QCheckBox *MaxSpeed;
    QSplitter *splitter;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSplitter *splitter_2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QSplitter *splitter_3;
    QLineEdit *Period;
    QLineEdit *Resolution;
    QLineEdit *Speed;

    void setupUi(QMainWindow *Simulation_ConfigureClass)
    {
        if (Simulation_ConfigureClass->objectName().isEmpty())
            Simulation_ConfigureClass->setObjectName(QString::fromUtf8("Simulation_ConfigureClass"));
        Simulation_ConfigureClass->resize(500, 250);
        Simulation_ConfigureClass->setMinimumSize(QSize(500, 250));
        Simulation_ConfigureClass->setMaximumSize(QSize(500, 250));
        centralwidget = new QWidget(Simulation_ConfigureClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(0, 180, 501, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        OK = new QPushButton(centralwidget);
        OK->setObjectName(QString::fromUtf8("OK"));
        OK->setGeometry(QRect(270, 200, 93, 28));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(11);
        OK->setFont(font);
        Cancel = new QPushButton(centralwidget);
        Cancel->setObjectName(QString::fromUtf8("Cancel"));
        Cancel->setGeometry(QRect(390, 200, 93, 28));
        Cancel->setFont(font);
        MaxSpeed = new QCheckBox(centralwidget);
        MaxSpeed->setObjectName(QString::fromUtf8("MaxSpeed"));
        MaxSpeed->setGeometry(QRect(200, 140, 100, 25));
        MaxSpeed->setMinimumSize(QSize(100, 25));
        MaxSpeed->setMaximumSize(QSize(100, 25));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(9);
        MaxSpeed->setFont(font1);
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(40, 50, 150, 87));
        QFont font2;
        font2.setPointSize(9);
        splitter->setFont(font2);
        splitter->setOrientation(Qt::Vertical);
        label = new QLabel(splitter);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(150, 25));
        label->setMaximumSize(QSize(150, 25));
        label->setFont(font1);
        splitter->addWidget(label);
        label_2 = new QLabel(splitter);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(150, 25));
        label_2->setMaximumSize(QSize(150, 25));
        label_2->setFont(font1);
        splitter->addWidget(label_2);
        label_3 = new QLabel(splitter);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(150, 25));
        label_3->setMaximumSize(QSize(150, 25));
        label_3->setFont(font1);
        splitter->addWidget(label_3);
        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setGeometry(QRect(340, 50, 200, 87));
        splitter_2->setOrientation(Qt::Vertical);
        label_4 = new QLabel(splitter_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(200, 25));
        label_4->setMaximumSize(QSize(200, 25));
        label_4->setFont(font1);
        splitter_2->addWidget(label_4);
        label_5 = new QLabel(splitter_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(200, 25));
        label_5->setMaximumSize(QSize(200, 25));
        label_5->setFont(font1);
        splitter_2->addWidget(label_5);
        label_6 = new QLabel(splitter_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(200, 25));
        label_6->setMaximumSize(QSize(200, 25));
        label_6->setFont(font1);
        splitter_2->addWidget(label_6);
        splitter_3 = new QSplitter(centralwidget);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setGeometry(QRect(200, 50, 131, 81));
        splitter_3->setMinimumSize(QSize(131, 23));
        splitter_3->setMaximumSize(QSize(131, 81));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial"));
        font3.setPointSize(8);
        splitter_3->setFont(font3);
        splitter_3->setFocusPolicy(Qt::StrongFocus);
        splitter_3->setOrientation(Qt::Vertical);
        Period = new QLineEdit(splitter_3);
        Period->setObjectName(QString::fromUtf8("Period"));
        Period->setMinimumSize(QSize(131, 23));
        Period->setMaximumSize(QSize(131, 23));
        Period->setFont(font3);
        Period->setFocusPolicy(Qt::StrongFocus);
        splitter_3->addWidget(Period);
        Resolution = new QLineEdit(splitter_3);
        Resolution->setObjectName(QString::fromUtf8("Resolution"));
        Resolution->setMinimumSize(QSize(131, 23));
        Resolution->setMaximumSize(QSize(131, 23));
        Resolution->setFont(font3);
        Resolution->setFocusPolicy(Qt::StrongFocus);
        splitter_3->addWidget(Resolution);
        Speed = new QLineEdit(splitter_3);
        Speed->setObjectName(QString::fromUtf8("Speed"));
        Speed->setMinimumSize(QSize(131, 23));
        Speed->setMaximumSize(QSize(131, 23));
        Speed->setFont(font3);
        Speed->setFocusPolicy(Qt::StrongFocus);
        splitter_3->addWidget(Speed);
        Simulation_ConfigureClass->setCentralWidget(centralwidget);

        retranslateUi(Simulation_ConfigureClass);

        QMetaObject::connectSlotsByName(Simulation_ConfigureClass);
    } // setupUi

    void retranslateUi(QMainWindow *Simulation_ConfigureClass)
    {
        Simulation_ConfigureClass->setWindowTitle(QApplication::translate("Simulation_ConfigureClass", "\344\273\277\347\234\237\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        OK->setText(QApplication::translate("Simulation_ConfigureClass", "\347\241\256\350\256\244", nullptr));
        Cancel->setText(QApplication::translate("Simulation_ConfigureClass", "\345\217\226\346\266\210", nullptr));
        MaxSpeed->setText(QApplication::translate("Simulation_ConfigureClass", "\346\234\200\345\244\247\351\200\237\345\272\246", nullptr));
        label->setText(QApplication::translate("Simulation_ConfigureClass", "\344\273\277\347\234\237\346\227\266\351\225\277\357\274\232", nullptr));
        label_2->setText(QApplication::translate("Simulation_ConfigureClass", "\344\273\277\347\234\237\347\262\276\345\272\246\357\274\232", nullptr));
        label_3->setText(QApplication::translate("Simulation_ConfigureClass", "\344\273\277\347\234\237\351\200\237\345\272\246\357\274\232", nullptr));
        label_4->setText(QApplication::translate("Simulation_ConfigureClass", "\344\273\277\347\234\237\347\247\222", nullptr));
        label_5->setText(QApplication::translate("Simulation_ConfigureClass", "\344\273\277\347\234\237\346\255\245\346\225\260/\344\273\277\347\234\237\347\247\222", nullptr));
        label_6->setText(QApplication::translate("Simulation_ConfigureClass", "\344\273\277\347\234\237\347\247\222/\347\247\222", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Simulation_ConfigureClass: public Ui_Simulation_ConfigureClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATION_CONFIGURE_H
