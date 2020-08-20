/********************************************************************************
** Form generated from reading UI file 'TrafficSim.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRAFFICSIM_H
#define UI_TRAFFICSIM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrafficSimClass
{
public:
    QAction *scence_Ordinary;
    QAction *scence_CFI;
    QAction *signal_Fixed;
    QAction *signal_Adaptive;
    QAction *simulation_Configuration;
    QAction *action_Run;
    QAction *action_Stop;
    QAction *action_SingleStep;
    QAction *vehicles_Ordinary;
    QAction *vehicles_CFI;
    QAction *OpenFile;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menuSiginal_Contral;
    QMenu *menuSimunilation;
    QMenu *menuVehicles;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TrafficSimClass)
    {
        if (TrafficSimClass->objectName().isEmpty())
            TrafficSimClass->setObjectName(QString::fromUtf8("TrafficSimClass"));
        TrafficSimClass->resize(1068, 813);
        scence_Ordinary = new QAction(TrafficSimClass);
        scence_Ordinary->setObjectName(QString::fromUtf8("scence_Ordinary"));
        scence_Ordinary->setCheckable(true);
        scence_CFI = new QAction(TrafficSimClass);
        scence_CFI->setObjectName(QString::fromUtf8("scence_CFI"));
        scence_CFI->setCheckable(true);
        signal_Fixed = new QAction(TrafficSimClass);
        signal_Fixed->setObjectName(QString::fromUtf8("signal_Fixed"));
        signal_Fixed->setCheckable(true);
        signal_Adaptive = new QAction(TrafficSimClass);
        signal_Adaptive->setObjectName(QString::fromUtf8("signal_Adaptive"));
        signal_Adaptive->setCheckable(true);
        simulation_Configuration = new QAction(TrafficSimClass);
        simulation_Configuration->setObjectName(QString::fromUtf8("simulation_Configuration"));
        action_Run = new QAction(TrafficSimClass);
        action_Run->setObjectName(QString::fromUtf8("action_Run"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/TrafficSim/images/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Run->setIcon(icon);
        action_Stop = new QAction(TrafficSimClass);
        action_Stop->setObjectName(QString::fromUtf8("action_Stop"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/TrafficSim/images/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Stop->setIcon(icon1);
        action_SingleStep = new QAction(TrafficSimClass);
        action_SingleStep->setObjectName(QString::fromUtf8("action_SingleStep"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/TrafficSim/images/single.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_SingleStep->setIcon(icon2);
        vehicles_Ordinary = new QAction(TrafficSimClass);
        vehicles_Ordinary->setObjectName(QString::fromUtf8("vehicles_Ordinary"));
        vehicles_CFI = new QAction(TrafficSimClass);
        vehicles_CFI->setObjectName(QString::fromUtf8("vehicles_CFI"));
        OpenFile = new QAction(TrafficSimClass);
        OpenFile->setObjectName(QString::fromUtf8("OpenFile"));
        centralWidget = new QWidget(TrafficSimClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        TrafficSimClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TrafficSimClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1068, 30));
        menuBar->setMinimumSize(QSize(0, 30));
        menuBar->setMaximumSize(QSize(16777215, 30));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu->setMinimumSize(QSize(0, 0));
        menu->setMaximumSize(QSize(16777215, 16777215));
        menuSiginal_Contral = new QMenu(menuBar);
        menuSiginal_Contral->setObjectName(QString::fromUtf8("menuSiginal_Contral"));
        menuSimunilation = new QMenu(menuBar);
        menuSimunilation->setObjectName(QString::fromUtf8("menuSimunilation"));
        menuVehicles = new QMenu(menuBar);
        menuVehicles->setObjectName(QString::fromUtf8("menuVehicles"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        TrafficSimClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TrafficSimClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setIconSize(QSize(20, 20));
        TrafficSimClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TrafficSimClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TrafficSimClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuSiginal_Contral->menuAction());
        menuBar->addAction(menuVehicles->menuAction());
        menuBar->addAction(menuSimunilation->menuAction());
        menuBar->addAction(menuFile->menuAction());
        menu->addSeparator();
        menu->addAction(scence_Ordinary);
        menu->addSeparator();
        menu->addAction(scence_CFI);
        menuSiginal_Contral->addSeparator();
        menuSiginal_Contral->addAction(signal_Fixed);
        menuSiginal_Contral->addSeparator();
        menuSiginal_Contral->addAction(signal_Adaptive);
        menuSimunilation->addSeparator();
        menuSimunilation->addAction(simulation_Configuration);
        menuVehicles->addSeparator();
        menuVehicles->addAction(vehicles_Ordinary);
        menuVehicles->addSeparator();
        menuVehicles->addAction(vehicles_CFI);
        menuFile->addAction(OpenFile);
        mainToolBar->addAction(action_Run);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_Stop);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_SingleStep);
        mainToolBar->addSeparator();

        retranslateUi(TrafficSimClass);
        QObject::connect(signal_Fixed, SIGNAL(toggled(bool)), signal_Adaptive, SLOT(setDisabled(bool)));
        QObject::connect(signal_Adaptive, SIGNAL(toggled(bool)), signal_Fixed, SLOT(setDisabled(bool)));
        QObject::connect(scence_Ordinary, SIGNAL(toggled(bool)), scence_CFI, SLOT(setDisabled(bool)));
        QObject::connect(scence_CFI, SIGNAL(toggled(bool)), scence_Ordinary, SLOT(setDisabled(bool)));

        QMetaObject::connectSlotsByName(TrafficSimClass);
    } // setupUi

    void retranslateUi(QMainWindow *TrafficSimClass)
    {
        TrafficSimClass->setWindowTitle(QApplication::translate("TrafficSimClass", "TrafficSim\344\272\244\351\200\232\344\273\277\347\234\237\350\275\257\344\273\266", nullptr));
        scence_Ordinary->setText(QApplication::translate("TrafficSimClass", "\346\231\256\351\200\232\350\267\257\345\217\243", nullptr));
        scence_CFI->setText(QApplication::translate("TrafficSimClass", "\347\247\273\344\275\215\345\267\246\350\275\254", nullptr));
        signal_Fixed->setText(QApplication::translate("TrafficSimClass", "\345\233\272\345\256\232\351\205\215\346\227\266", nullptr));
        signal_Adaptive->setText(QApplication::translate("TrafficSimClass", "\350\207\252\351\200\202\345\272\224\351\205\215\346\227\266", nullptr));
        simulation_Configuration->setText(QApplication::translate("TrafficSimClass", "\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        action_Run->setText(QApplication::translate("TrafficSimClass", "Run", nullptr));
#ifndef QT_NO_TOOLTIP
        action_Run->setToolTip(QApplication::translate("TrafficSimClass", "Run Simulation", nullptr));
#endif // QT_NO_TOOLTIP
        action_Stop->setText(QApplication::translate("TrafficSimClass", "Stop", nullptr));
#ifndef QT_NO_TOOLTIP
        action_Stop->setToolTip(QApplication::translate("TrafficSimClass", "Stop simulation", nullptr));
#endif // QT_NO_TOOLTIP
        action_SingleStep->setText(QApplication::translate("TrafficSimClass", "SingleStep", nullptr));
#ifndef QT_NO_TOOLTIP
        action_SingleStep->setToolTip(QApplication::translate("TrafficSimClass", "Run simulation with single step", nullptr));
#endif // QT_NO_TOOLTIP
        vehicles_Ordinary->setText(QApplication::translate("TrafficSimClass", "\346\231\256\351\200\232\350\267\257\345\217\243", nullptr));
        vehicles_CFI->setText(QApplication::translate("TrafficSimClass", "\347\247\273\344\275\215\345\267\246\350\275\254", nullptr));
        OpenFile->setText(QApplication::translate("TrafficSimClass", "\346\211\223\345\274\200\350\276\223\345\205\245\346\226\207\344\273\266", nullptr));
        menu->setTitle(QApplication::translate("TrafficSimClass", "\350\267\257\345\217\243\347\261\273\345\236\213", nullptr));
        menuSiginal_Contral->setTitle(QApplication::translate("TrafficSimClass", "\351\205\215\346\227\266\346\226\271\346\241\210", nullptr));
        menuSimunilation->setTitle(QApplication::translate("TrafficSimClass", "\344\273\277\347\234\237\350\256\276\347\275\256", nullptr));
        menuVehicles->setTitle(QApplication::translate("TrafficSimClass", "\350\275\246\350\276\206\350\276\223\345\205\245", nullptr));
        menuFile->setTitle(QApplication::translate("TrafficSimClass", "\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TrafficSimClass: public Ui_TrafficSimClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRAFFICSIM_H
