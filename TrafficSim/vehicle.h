#pragma once
#include "Com_use.h"

using namespace std;

//circles
class vehicle
{
public:
	vehicle(QVector<QLineF*>route,int road,float speed);
	virtual ~vehicle();

	bool still_in() {
		return this->in_wind;
	}
	bool impact(vehicle * veh) {
		QLineF* dis = new QLineF(this->position, veh->position);
		if (dis->length() < this->diameter*1.5) {
			delete dis;
			return true;
		}
		delete dis;
		return false;
	}
	bool ord_out_wind() {
		if (position.x() <= -15 || position.x() >= 1306 || position.y() <= 15 || position.y() >= 868)
			return true;
		return false;
	}
	bool cfi_out_wind() {
		if (position.x() <= -15 || position.x() >= 1287 || position.y() <= 15 || position.y() >= 860)
			return true;
		return false;
	}
	bool ord_conflict() {
		if (this->position.x() > 563 && this->position.x() < 727 && this->position.y() < 521 && this->position.y() > 358)
			return true;
		return false;
	}
	bool cfi_conflict() {
		if (this->position.x() > 158 && this->position.x() < 237 && this->position.y() < 460 && this->position.y() > 399)
			return true;
		if (this->position.x() > 556 && this->position.x() < 722 && this->position.y() < 527 && this->position.y() > 356)
			return true;
		if (this->position.x() > 1043 && this->position.x() < 1114 && this->position.y() < 482 && this->position.y() > 419)
			return true;
		return false;
	}

	bool is_waiting() {
		return this->wait_;
	}
	void wait() {
		this->wait_ = true;
	}
	QPointF get_position() {
		return this->position;
	}
	void setPos(QPointF pos) {
		this->position = pos;
	}
	void setX(float x) {
		this->position.setX(x);
	}
	void setY(float y) {
		this->position.setY(y);
	}

	//time slot and signal control and pre-car position(can be null)
	void move(float time, vehicle* preveh);
	void move(float time);
	void move();
	void move_back() {
		this->speed = 0;
		position = lastpos;
	}

	void draw(QPainter &painter);

//public:
	bool wait_;
	float min_dis;
	//length to go
	float go_len;
	//size in pixmap
	float diameter;
	//color
	//int color;
	//drive route
	vector<QLineF*> route;
	//cur position
	QPointF position;
	QPointF lastpos;
	//speed in real world   m/s
	float speed;
	float maxspeed;
	//acceleration m/s2
	float acc;
	//Car-following model parameters 
	float lambda;
	//line index
	int cur_route;
	//road 0-8
	int cur_road;
	//still in the window
	bool in_wind;
};

