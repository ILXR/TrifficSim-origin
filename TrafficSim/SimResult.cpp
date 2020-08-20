#include "SimResult.h"



SimResult::SimResult(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QObject::connect(this->ui.OK, &QPushButton::clicked, this, &SimResult::click_ok);
}


SimResult::~SimResult()
{
}
