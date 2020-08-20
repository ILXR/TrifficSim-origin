#include "Simulation_Configure.h"



Simulation_Configure::Simulation_Configure(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//connect signal and slots
	//click ok
	QObject::connect(this->ui.OK,&QPushButton::clicked,this, &Simulation_Configure::click_ok);
	//check max_speed
	QObject::connect(this->ui.MaxSpeed, &QAbstractButton::clicked,this,&Simulation_Configure::change_text_state );
	//click cancel
	QObject::connect(this->ui.Cancel, &QPushButton::clicked, this, &QMainWindow::hide);

	//Restricted input...int and float
	QRegExp intnum("[0-9]+"), floatnum("[0-9][0-9]+(.)?[0-9]+");
	QRegExpValidator *intval = new QRegExpValidator(intnum, this);
	QRegExpValidator *floatval = new QRegExpValidator(floatnum, this);
	this->ui.Period->setValidator(intval);
	this->ui.Resolution->setValidator(intval);
	this->ui.Speed->setValidator(intval);
}

Simulation_Configure::~Simulation_Configure()
{
}


