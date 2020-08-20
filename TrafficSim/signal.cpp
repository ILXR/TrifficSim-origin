#include "signal.h"


signal::signal(int x, int y, int dir)
{
	this->position.setX(x);
	this->position.setY(y);
	this->dir = dir;
	if (dir == 0) {
		this->size.setWidth(3*PROPOTION);
		this->size.setHeight(1* PROPOTION);
	}
	else {
		this->size.setWidth(1 * PROPOTION);
		this->size.setHeight(3 * PROPOTION);
	}
	this->state = Green;
}


signal::~signal()
{
}

void signal::setstate(bool isgreen)
{
	if (isgreen)
		this->state = Green;
	else
		this->state = Red;
}

bool signal::isgreen()
{
	if (this->state == Green)
		return true;
	else
		return false;
}

void signal::draw(QPainter & paint)
{
	if (this->state == Red)
		paint.setBrush(QBrush(Qt::red));
	else if (this->state == Green)
		paint.setBrush(QBrush(Qt::green));
	paint.drawRect(this->position.x()-this->size.width()*0.5,this->position.y() - this->size.height()*0.5,this->size.width(),this->size.height());
}
