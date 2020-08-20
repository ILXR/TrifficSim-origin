#include "CFI_Vehicles_Inputs.h"



CFI_Vehicles_Inputs::CFI_Vehicles_Inputs(QWidget *parent)
	: QMainWindow(parent)
{
	//time random init
	srand(int(time(0)));
	//ui
	ui.setupUi(this);
	//connect
	//click ok
	QObject::connect(this->ui.OK, &QPushButton::clicked, this, &CFI_Vehicles_Inputs::click_ok);
	//click cancel
	QObject::connect(this->ui.Cancel, &QPushButton::clicked, this, &QMainWindow::hide);
	//click min
	QObject::connect(this->ui.Min, &QPushButton::clicked, this, &CFI_Vehicles_Inputs::click_min);
	//click max
	QObject::connect(this->ui.Max, &QPushButton::clicked, this, &CFI_Vehicles_Inputs::click_max);
	//click max
	QObject::connect(this->ui.Random, &QPushButton::clicked, this, &CFI_Vehicles_Inputs::click_random);
	//click min
	QObject::connect(this->ui.Min, &QPushButton::clicked, this, &CFI_Vehicles_Inputs::click_min);
	//click get ord veh
	QObject::connect(this->ui.get_same_veh,&QPushButton::clicked,this, &CFI_Vehicles_Inputs::get_same_veh);
	//Restricted input...int and float
	QRegExp intnum("[0-9]+"), floatnum("[0-9][0-9]+(.)?[0-9]+");
	QRegExpValidator *intval = new QRegExpValidator(intnum, this);
	QRegExpValidator *floatval = new QRegExpValidator(floatnum, this);
	this->ui.L1->setValidator(intval);
	this->ui.L2->setValidator(intval);
	this->ui.L3->setValidator(intval);
	this->ui.L4->setValidator(intval);
	this->ui.L5->setValidator(intval);
	this->ui.L6->setValidator(intval);
	this->ui.L7->setValidator(intval);
	this->ui.L8->setValidator(intval);
}


CFI_Vehicles_Inputs::~CFI_Vehicles_Inputs()
{
}
