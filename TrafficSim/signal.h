#pragma once
#include <Com_use.h>

class signal
{
public:
	signal(int x,int y,int dir);
	~signal();
	void setstate(bool isgreen);
	bool isgreen();
	void draw(QPainter &paint);
	int getdir() {
		return this->dir;
	}
	QPointF getPos() {
		return this->position;
	}

private:
	int dir;
	QSizeF size;
	SignalState state;
	QPointF position;
};

