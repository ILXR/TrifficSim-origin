#include "vehicle.h"



vehicle::vehicle(QVector<QLineF*> route, int road, float speed)
{
	this->route.clear();
	 
	for (int i = 0; i < route.size(); i++) {
		this->route.push_back(route[i]);
	}
	this->wait_ = false;
	this->cur_route = 0;
	this->cur_road = road;
	this->speed = speed;
	this->maxspeed = speed;
	this->acc = 0;
	this->lambda = 0.368;
	this->diameter = 3*PROPOTION;
	this->position.setX(this->route[0]->x1());
	this->position.setY(this->route[0]->y1());
	this->lastpos.setX(this->route[0]->x1());
	this->lastpos.setY(this->route[0]->y1());
	this->in_wind = true;
	this->min_dis = PROPOTION * MINDISTANCE + this->diameter;
	//this->color = rand() % 6;
}

vehicle::~vehicle()
{
}

void vehicle::move(float time) {
	//Head cart move
	float go_length;
	if (this->speed < this->maxspeed) {
		this->acc = 5;
		float newspeed = this->speed + this->acc*time;
		newspeed = newspeed > this->maxspeed ? this->maxspeed : newspeed;
		go_length = time * PROPOTION * (this->speed + newspeed) / 2;
		this->speed = newspeed;
	}
	else {
		go_length = time * PROPOTION * this->speed;
	}
	this->wait_ = false;
	lastpos = position;
	QPointF endpoint = this->route.at(this->cur_route)->p2();
	//tem road remaining length
	QLineF* tem_dis = new QLineF(this->position, endpoint);
	float road_len = tem_dis->length();
	if (go_length < road_len) { //still in cur route
		tem_dis->setLength(go_length);
		this->position.setX(tem_dis->x2());
		this->position.setY(tem_dis->y2());
	}
	else {
		while (go_length >= road_len && this->cur_route < this->route.size() - 1) {
			this->position.setX(endpoint.x());
			this->position.setY(endpoint.y());
			go_length -= road_len;
			this->cur_route++;
			endpoint = this->route.at(this->cur_route)->p2();
			delete tem_dis;
			tem_dis = new QLineF(this->position, endpoint);
			road_len = tem_dis->length();
		}
		if (go_length >= road_len && this->cur_route == this->route.size()-1) {//last route
			this->in_wind = false;
			delete tem_dis;
			return;
		}
		else {
			delete tem_dis;
			tem_dis = new QLineF(this->position, endpoint);
			tem_dis->setLength(go_length);
			endpoint = tem_dis->p2();
			this->position.setX(endpoint.x());
			this->position.setY(endpoint.y());
		}
	}
	delete tem_dis;
}

void vehicle::move() {
	//Driving according to route and calculated length 
	lastpos = position;
	QPointF endpoint = this->route.at(this->cur_route)->p2();
	//tem road remaining length
	QLineF* tem_dis = new QLineF(this->position, endpoint);
	float road_len = tem_dis->length();
	if (this->go_len < road_len) { //still in cur route
		tem_dis->setLength(this->go_len);
		this->position.setX(tem_dis->x2());
		this->position.setY(tem_dis->y2());
	}
	else {
		while (this->go_len >= road_len && this->cur_route < this->route.size() - 1) {
			this->position.setX(endpoint.x());
			this->position.setY(endpoint.y());
			this->go_len -= road_len;
			this->cur_route++;
			endpoint = this->route.at(this->cur_route)->p2();
			delete tem_dis;
			tem_dis = new QLineF(this->position, endpoint);
			road_len = tem_dis->length();
		}
		if (this->go_len >= road_len && this->cur_route == this->route.size() - 1) {//last route
			this->in_wind = false;
			delete tem_dis;
			return;
		}
		else {
			delete tem_dis;
			tem_dis = new QLineF(this->position, endpoint);
			tem_dis->setLength(this->go_len);
			endpoint = tem_dis->p2();
			this->position.setX(endpoint.x());
			this->position.setY(endpoint.y());
		}
	}
	delete tem_dis;
}

void vehicle::move(float time, vehicle* preveh) {
	//Move according to the state of the previous car 
	this->wait_ = false;
	lastpos = position;
	QLineF* draw = new QLineF(this->position, preveh->position);
	if (draw->length()<this->min_dis) {
		return;
	}
	if (preveh->still_in()) { //pre car exists and could impact
		QPointF cur_p = this->position;
		int cur_r = this->cur_route;
		float length = 0;
		while (cur_r < preveh->cur_route) {
			QPointF endpoint = this->route.at(this->cur_route)->p2();
			QLineF* cur_l = new QLineF(cur_p, endpoint);
			length += cur_l->length();
			cur_p = cur_l->p2();
			cur_r++;
			delete cur_l;
		}
		QLineF* cur_l = new QLineF(cur_p, preveh->position);
		length += cur_l->length();
		delete cur_l;
		//Calculate driving distance
		float distance = length / PROPOTION;
		if (preveh->speed > this->speed)
			this->acc = this->lambda*this->maxspeed*4*(preveh->speed - this->speed)/(this->speed+this->maxspeed);
		else
			this->acc = (this->lambda*this->speed)*(preveh->speed - this->speed) / (distance*distance);
		float newspeed = this->speed + acc * time;
		newspeed = (newspeed > this->maxspeed) ? this->maxspeed : newspeed;
		newspeed = (newspeed < 0) ? 0 : newspeed;
		this->go_len = time * PROPOTION * (this->speed + newspeed) / 2;
		this->speed = newspeed;
		//pix distance
		if (this->go_len > length - MINDISTANCE * PROPOTION - this->diameter) {
			this->speed = 0;
			this->go_len = length - MINDISTANCE * PROPOTION - this->diameter;
		}
		this->move();
	}
	else
		this->move(time);
	delete draw;
}

void vehicle::draw(QPainter &painter)
{
	if ( this->position.x() < 0 || this->position.y() < 0 || this->position.x() > 1292|| this->position.y() >854)
		return;
	else {
		switch (this->cur_road) {
		case 0: {
			painter.setBrush(QBrush("#FFD700"));
			break;
		}
		case 1: {
			painter.setBrush(QBrush("#FF8800"));
			break;
		}
		case 2: {
			painter.setBrush(QBrush(Qt::white));
			break;
		}
		case 3: {
			painter.setBrush(QBrush(Qt::gray));
			break;
		}
		case 4: {
			painter.setBrush(QBrush("#FF3EFF"));
			break;
		}
		case 5: {
			painter.setBrush(QBrush(Qt::red));
			break;
		}
		case 6: {
			painter.setBrush(QBrush(Qt::green));
			break;
		}
		case 7: {
			painter.setBrush(QBrush("#00BFFF"));
			break;
		}
		}
	}
	
	painter.drawEllipse(this->position.x() - this->diameter / 2, this->position.y() - this->diameter / 2,this->diameter, this->diameter);
}
