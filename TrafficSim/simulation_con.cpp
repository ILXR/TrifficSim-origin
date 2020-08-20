#include "simulation_con.h"



simulation_con::simulation_con(TrafficSim* parrent)
{
	//qDebug() << "create simcon";
	this->ui.setupUi(this);
	this->parrent = parrent;
	this->road_line = new Road_Line();
	this->all_time = 0;
	this->cur_time = 0;
	this->sim_running = false;
	memset(this->vehicles_toin, 0, sizeof(this->vehicles_toin));
	for (int i = 0; i < 8; i++) {
		this->ord_signals.append(new signal(Ord_Signals[i][0], Ord_Signals[i][1], Ord_Signals[i][2]));
	}
	for (int i = 0; i < 14; i++) {
		this->cfi_signals.append(new signal(CFI_Signals[i][0], CFI_Signals[i][1], CFI_Signals[i][2]));
	}

}

simulation_con::~simulation_con()
{
}

void simulation_con::start_sim() {
	this->show();
	this->ui.Result->clear();
	if (this->sim_running) return;
	this->cur_time = 0;
	this->sim_running = true;
	this->all_time = 0;
	this->cycles = 0;
	this->all_cyc = 0;
	memset(this->vehicles_toin, 0, sizeof(this->vehicles_toin));

	if (parrent->curroad == Ordinary_ && parrent->cursignal == Fixed) {
		ord_fixed = new Ordinary();
		this->ui.Result->append(QString(QStringLiteral("普通路口固定配时\n")));
	}
	else if (parrent->curroad == CFI && parrent->cursignal == Fixed) {
		cfi_fixed = new Left();
		this->ui.Result->append(QString(QStringLiteral("移位左转固定配时\n")));
	}
	else if (parrent->curroad == Ordinary_ && parrent->cursignal == Adaptive) {
		this->ui.Result->append(QString(QStringLiteral("普通路口自适应配时\n")));
		for (int i = 0; i < 2; i++) {
			normal[i] = new Ordinary();
		}
	}
	else {
		this->ui.Result->append(QString(QStringLiteral("移位左转自适应配时\n")));
		for (int i = 0; i < 2; i++) {
			left[i] = new Left();
		}
	}

	memset(ord_record_veh, 0, sizeof(ord_record_veh));
	memset(cfi_record_veh, 0, sizeof(cfi_record_veh));
	memset(ord_veh_num, 0, sizeof(ord_veh_num));
	memset(cfi_veh_num, 0, sizeof(cfi_veh_num));
	srand(int(time(0)));
	for (int i = 0; i < 8; i++) {
		this->vehicles_inputs[i].clear();
	}
	this->all_time = this->parrent->resolution*this->parrent->period;
	//sim sec / sim step
	this->time_slots = 1.0/this->parrent->resolution;
	//get generate provavility
	int maxnum = this->parrent->period;
	for (int i = 0; i < 8; i++) {
		/*if (this->parrent->curroad == Ordinary_)
			this->probability[i] = (float)(this->parrent->ord_vehicles[i] <= maxnum ? this->parrent->ord_vehicles[i] : maxnum) / maxnum;
		else {
			this->probability[i] = (float)(this->parrent->cfi_vehicles[i] <= maxnum ? this->parrent->cfi_vehicles[i] : maxnum) / maxnum;
		}*/
		int leftmax = maxnum * 11 / 90 + maxnum / 18;
		if (this->parrent->curroad == Ordinary_) {
			if (i == 3 || i == 7)
				this->probability[i] = (this->parrent->ord_vehicles[i] <= leftmax ? this->parrent->ord_vehicles[i] : leftmax);
			else
				this->probability[i] = (this->parrent->ord_vehicles[i] <= maxnum ? this->parrent->ord_vehicles[i] : maxnum);
		}
		else {
			if (i == 3 || i == 7)
				this->probability[i] = (this->parrent->cfi_vehicles[i] <= leftmax ? this->parrent->cfi_vehicles[i] : leftmax);
			else
				this->probability[i] = (this->parrent->cfi_vehicles[i] <= maxnum ? this->parrent->cfi_vehicles[i] : maxnum);
		}
	}
}
void simulation_con::single_step_sim(QPainter &paint) {

	if (this->parrent->curroad == Ordinary_) {
		for (int j = 0; j < this->ord_signals.size(); j++) {
			this->ord_signals[j]->draw(paint);
		}
	}
	if (this->parrent->curroad == CFI) {
		for (int j = 0; j < this->cfi_signals.size(); j++) {
			this->cfi_signals[j]->draw(paint);
		}
	}
	int maxnum = this->parrent->period;
	if (cur_time%parrent->resolution == 0){
		for (int i = 0; i < 8; i++) {
			float chance = (float)(rand() % maxnum);
			if (chance <= this->probability[i]) {
				if (this->parrent->curroad == Ordinary_) {
					if (vehicles_inputs[i].size() > 0 && vehicles_inputs[i].back()->ord_out_wind()) {
						vehicles_toin[i]++;
						continue;
					}
					this->vehicles_inputs[i].append(new vehicle(this->road_line->Ord_Line_pix[i], i, SPEED));
				}
				else {//CFI
					if (vehicles_inputs[i].size() > 0 && vehicles_inputs[i].back()->cfi_out_wind()) {
						vehicles_toin[i]++;
						continue;
					}
					this->vehicles_inputs[i].append(new vehicle(this->road_line->CFI_Line_pix[i], i, SPEED));
				}
			}
			else {
				if (vehicles_toin[i] == 0)
					continue;
				if (this->parrent->curroad == Ordinary_) {
					if (vehicles_inputs[i].size() == 0) {
						this->vehicles_inputs[i].append(new vehicle(this->road_line->Ord_Line_pix[i], i, SPEED));
						vehicles_toin[i]--;
						continue;
					}
					if (vehicles_inputs[i].size() > 0 && !vehicles_inputs[i].back()->ord_out_wind()) {
						this->vehicles_inputs[i].append(new vehicle(this->road_line->Ord_Line_pix[i], i, SPEED));
						vehicles_toin[i]--;
					}
				}
				else {//CFI
					if (vehicles_inputs[i].size() == 0) {
						this->vehicles_inputs[i].append(new vehicle(this->road_line->CFI_Line_pix[i], i, SPEED));
						vehicles_toin[i]--;
						continue;
					}
					if (vehicles_inputs[i].size() > 0 && !vehicles_inputs[i].back()->cfi_out_wind()) {
						this->vehicles_inputs[i].append(new vehicle(this->road_line->CFI_Line_pix[i], i, SPEED));
						vehicles_toin[i]--;
					}
				}
			}
		}
	}
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < this->vehicles_inputs[i].size(); j++) {
			//append if in conflict area
			if (this->parrent->curroad == Ordinary_ && vehicles_inputs[i].at(j)->ord_conflict() && !ROAD_conflict_veh[i].contains(vehicles_inputs[i][j]))
				ROAD_conflict_veh[i].append(vehicles_inputs[i][j]);
			if (this->parrent->curroad == CFI && vehicles_inputs[i].at(j)->cfi_conflict() && !ROAD_conflict_veh[i].contains(vehicles_inputs[i][j]))
				ROAD_conflict_veh[i].append(vehicles_inputs[i][j]);
			//move
			if (j == 0)
				this->vehicles_inputs[i][j]->move(this->time_slots);
			else {
				this->vehicles_inputs[i][j]->move(this->time_slots, this->vehicles_inputs[i][j - 1]);
			}
			//car impact
			if (this->parrent->curroad == Ordinary_ && Ord_check_impact(vehicles_inputs[i][j]))
				vehicles_inputs[i][j]->move_back();
			if(this->parrent->curroad == CFI && CFI_check_impact(vehicles_inputs[i][j]))
				vehicles_inputs[i][j]->move_back();
			//signal check
			if (this->parrent->curroad == Ordinary_)
				Ord_check_signal(vehicles_inputs[i][j]);
			if (this->parrent->curroad == CFI)
				CFI_check_signal(vehicles_inputs[i][j]);
			//draw
			this->vehicles_inputs[i][j]->draw(paint);
			//remove if not in conflict area
			if (this->parrent->curroad == Ordinary_ && !vehicles_inputs[i][j]->ord_conflict() && ROAD_conflict_veh[i].contains(vehicles_inputs[i][j]))
				ROAD_conflict_veh[i].removeOne(vehicles_inputs[i][j]);
			if (this->parrent->curroad == CFI && !vehicles_inputs[i][j]->cfi_conflict() && ROAD_conflict_veh[i].contains(vehicles_inputs[i][j]))
				ROAD_conflict_veh[i].removeOne(vehicles_inputs[i][j]);
		}
		//remove if not in window
		while (this->vehicles_inputs[i].size() > 0 && !this->vehicles_inputs[i].front()->still_in()) {
			//qDebug() << "delete" << i;
			delete this->vehicles_inputs[i].takeFirst();
		}
	}

	int time = cur_time / parrent->resolution;
	int cur_t = time - all_cyc;

	if (parrent->curroad == Ordinary_ && parrent->cursignal == Fixed) {
		if (cur_time%parrent->resolution == 0) {
			bool * tem_ctr = ord_fixed->judge(cur_t);
			int temp_veh[8];
			//set signal states
			for (int j = 0; j < 8; j++) {
				this->ord_signals[j]->setstate(tem_ctr[j]);
			}
			if (cur_t == ord_fixed->cycle) {
				int* road_t = ord_fixed->get_t();
				QString ss = QString(QStringLiteral("当前周期:%1\n").arg(cycles));
				ss.append(QStringLiteral("绿灯时长:\n"));
				for (int j = 0; j < 8; j++) {
					ss.append(QString("%1  ").arg(road_t[j]));
				}
				ss.append(QStringLiteral("\n通行车辆:\n"));
				for (int j = 0; j < 8; j++) { //veh num this cycle
					temp_veh[j] = ord_veh_num[j] - ord_record_veh[j];
					ord_record_veh[j] += temp_veh[j];
					ss.append(QString("%1  ").arg(temp_veh[j]));
				}
				ss.append("\n");
				this->ui.Result->append(ss);
				ord_fixed->fixed_next();
				cycles++;
				all_cyc = time;
			}
			//delete tem_ctr;
		}
		if (this->cur_time == this->all_time - 1 && cur_t != ord_fixed->cycle) {
			ord_fixed->get_last(cur_t);
		}
	}
	else if (parrent->curroad == CFI && parrent->cursignal == Fixed) {
		if (cur_time%parrent->resolution == 0) {
			int temp_veh[14] = { 0 };
			for (int j = 0; j < 14; j++) { //veh num this cycle
				temp_veh[j] = cfi_veh_num[j] - cfi_record_veh[j];
			}
			bool tem_ctr[12];
			memset(tem_ctr,false,sizeof(tem_ctr));
			int num2 = cfi_veh_num[1] - cfi_veh_num[10];
			int num3 = cfi_veh_num[2] - cfi_veh_num[13];
			int num6 = cfi_veh_num[5] - cfi_veh_num[12];
			int num7 = cfi_veh_num[6] - cfi_veh_num[11];
			int num9 = cfi_veh_num[8] - cfi_veh_num[3];
			int num10 = cfi_veh_num[9] - cfi_veh_num[7];
			cfi_fixed->judge(cur_t, temp_veh,num2,num3,num6,num7, num9, num10, tem_ctr);
			for (int j = 0; j < 10; j++) {
				this->cfi_signals[j]->setstate(tem_ctr[j]);
			}
			this->cfi_signals[10]->setstate(tem_ctr[10]);
			this->cfi_signals[11]->setstate(tem_ctr[10]);
			this->cfi_signals[12]->setstate(tem_ctr[11]);
			this->cfi_signals[13]->setstate(tem_ctr[11]);
			if (cur_t == cfi_fixed->cycle) {
				int* road_t = cfi_fixed->get_t();
				QString ss = QString(QStringLiteral("当前周期:%1\n").arg(cycles));
				ss.append(QStringLiteral("绿灯时长:\n"));
				for (int j = 0; j < 10; j++) {
					ss.append(QString("%1  ").arg(road_t[j]));
				}
				ss.append(QStringLiteral("\n通行车辆:\n"));
				for (int j = 0; j < 10; j++) { //veh num this cycle
					temp_veh[j] = cfi_veh_num[j] - cfi_record_veh[j];
					cfi_record_veh[j] += temp_veh[j];
					ss.append(QString("%1  ").arg(temp_veh[j]));
				}
				ss.append("\n");
				this->ui.Result->append(ss);
				cfi_fixed->fixed_next();
				cycles++;
				all_cyc = time;
			}
		}
		if (this->cur_time == this->all_time - 1 && cur_t != cfi_fixed->cycle) {
			cfi_fixed->get_last(cur_t);
		}

	}
	else if (parrent->curroad == Ordinary_ && parrent->cursignal == Adaptive) {
		bool * tem_ctr = normal[cycles % 2]->judge(cur_t);
		int temp_veh[8];
		if (cur_time%parrent->resolution == 0) {
			for (int j = 0; j < 8; j++) {
				this->ord_signals[j]->setstate(tem_ctr[j]);
			}
			if (cur_t == normal[cycles % 2]->cycle) {
				int* road_t = normal[cycles % 2]->get_t();
				QString ss = QString(QStringLiteral("当前周期:%1\n").arg(cycles));
				ss.append(QStringLiteral("绿灯时长:\n"));
				for (int j = 0; j < 8; j++) {
					ss.append(QString("%1  ").arg(road_t[j]));
				}
				ss.append(QStringLiteral("\n通行车辆:\n"));
				for (int j = 0; j < 8; j++) { //veh num this cycle
					temp_veh[j] = ord_veh_num[j] - ord_record_veh[j];
					ord_record_veh[j] += temp_veh[j];
					ss.append(QString("%1  ").arg(temp_veh[j]));
				}
				ss.append("\n");
				this->ui.Result->append(ss);
				normal[cycles % 2]->next(temp_veh);
				cycles++;
				all_cyc = time;
			}
		}
		if (this->cur_time == this->all_time - 1 && cur_t != ord_fixed->cycle) {
			normal[cycles % 2]->get_last(cur_t);
		}
		//delete tem_ctr;
	}
	else {
		//CFI Adapative
		if (cur_time%parrent->resolution == 0) {
			int temp_veh[14] = { 0 };
			for (int j = 0; j < 14; j++) { //veh num this cycle
				temp_veh[j] = cfi_veh_num[j] - cfi_record_veh[j];
			}
			bool tem_ctr[12];
			memset(tem_ctr, false, sizeof(tem_ctr));
			int num2 = cfi_veh_num[1] - cfi_veh_num[10];
			int num3 = cfi_veh_num[2] - cfi_veh_num[13];
			int num6 = cfi_veh_num[5] - cfi_veh_num[12];
			int num7 = cfi_veh_num[6] - cfi_veh_num[11];
			int num9 = cfi_veh_num[8] - cfi_veh_num[3];
			int num10 = cfi_veh_num[9] - cfi_veh_num[7];
			left[cycles % 2] ->judge(cur_t, temp_veh, num2, num3, num6, num7, num9, num10, tem_ctr);
			for (int j = 0; j < 10; j++) {
				this->cfi_signals[j]->setstate(tem_ctr[j]);
			}
			this->cfi_signals[10]->setstate(tem_ctr[10]);
			this->cfi_signals[11]->setstate(tem_ctr[10]);
			this->cfi_signals[12]->setstate(tem_ctr[11]);
			this->cfi_signals[13]->setstate(tem_ctr[11]);
			if (cur_t == left[cycles % 2]->cycle) {
				int* road_t = left[cycles % 2]->get_t();
				QString ss = QString(QStringLiteral("当前周期:%1\n").arg(cycles));
				ss.append(QStringLiteral("绿灯时长:\n"));
				for (int j = 0; j < 10; j++) {
					ss.append(QString("%1  ").arg(road_t[j]));
				}
				ss.append(QStringLiteral("\n通行车辆:\n"));
				for (int j = 0; j < 14; j++) { //veh num this cycle
					temp_veh[j] = cfi_veh_num[j] - cfi_record_veh[j];
					cfi_record_veh[j] += temp_veh[j];
					if (j < 10) {
						ss.append(QString("%1  ").arg(temp_veh[j]));
					}
				}
				ss.append("\n");
				this->ui.Result->append(ss);
				left[cycles % 2]->next(temp_veh);
				cycles++;
				all_cyc = time;
			}
		}
		if (this->cur_time == this->all_time - 1 && cur_t != left[cycles % 2]->cycle) {
			left[cycles % 2]->get_last(cur_t);
		}
	}

	if (this->cur_time == this->all_time - 1) {
		stop_sim();
		if (this->parrent->curroad == Ordinary_)
			emit sim_finished(ord_veh_num);
		else
			emit sim_finished(cfi_veh_num);
	}
	this->cur_time++;
}
void simulation_con::single_step_draw(QPainter &paint) {
	if (this->sim_running) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < this->vehicles_inputs[i].size(); j++) {
				this->vehicles_inputs[i][j]->draw(paint);
			}
		}
		if (this->parrent->curroad == Ordinary_) {
			for (int j = 0; j < this->ord_signals.size(); j++) {
				this->ord_signals[j]->draw(paint);
			}
		}
		else {
			for (int j = 0; j < this->cfi_signals.size(); j++) {
				this->cfi_signals[j]->draw(paint);
			}
		}
	}
}

void simulation_con::stop_sim() {
	memset(this->vehicles_toin, 0, sizeof(this->vehicles_toin));
	for (int i = 0; i < 8; i++) {
		this->ROAD_conflict_veh[i].clear();
		while (this->vehicles_inputs[i].size() > 0) {
			delete this->vehicles_inputs[i].takeFirst();
		}
	}
	if (parrent->curroad == Ordinary_ && parrent->cursignal == Fixed)
		delete ord_fixed;
	else if (parrent->curroad == CFI && parrent->cursignal == Fixed)
		delete cfi_fixed;
	else if (parrent->curroad == Ordinary_ && parrent->cursignal == Adaptive) {
		for (int i = 0; i < 2; i++) {
			delete normal[i];
		}
	}
	else {
		for (int i = 0; i < 2; i++) {
			delete left[i];
		}
	}
	this->sim_running = false;
	this->cur_time = 0;

}

void simulation_con::CFI_check_signal(vehicle* veh) {
	int curr = veh->cur_road;
	for (int i = 0; i < 2; i++) {
		int cur_s = CFI_R_S[curr][i];
		if (cur_s == 0) continue;
		signal* cursig = this->cfi_signals[cur_s-1];
		if (cursig->getdir() == 0)//-----
		{
			if (veh->lastpos.y() - cursig->getPos().y() >= 2 * PROPOTION && veh->position.y() - cursig->getPos().y() < 2 * PROPOTION) {
				if (cursig->isgreen()) {
					cfi_veh_num[cur_s - 1]++;
				}
				else {
					veh->move_back();
					veh->position.setY(cursig->getPos().y() + 2 * PROPOTION);
				}
				return;
			}
			if (veh->lastpos.y() - cursig->getPos().y() <= (-2)*PROPOTION && veh->position.y() - cursig->getPos().y() > (-2)*PROPOTION) {
				if (cursig->isgreen()) {
					cfi_veh_num[cur_s - 1]++;
				}
				else {
					veh->move_back();
					veh->position.setY(cursig->getPos().y() - 2 * PROPOTION);
				}
				return;
			}
		}
		if (cursig->getdir() == 1)//|||||
		{
			if (veh->lastpos.x() - cursig->getPos().x() >= 2 * PROPOTION && veh->position.x() - cursig->getPos().x() < 2 * PROPOTION) {
				if (cursig->isgreen()) {
					cfi_veh_num[cur_s - 1]++;
				}
				else {
					veh->move_back();
					veh->position.setX(cursig->getPos().x() + 2 * PROPOTION);
				}
				return;
			}
			if (veh->lastpos.x() - cursig->getPos().x() <= (-2)*PROPOTION && veh->position.x() - cursig->getPos().x() > (-2)*PROPOTION) {
				if (cursig->isgreen()) {
					cfi_veh_num[cur_s - 1]++;
				}
				else {
					veh->move_back();
					veh->position.setX(cursig->getPos().x() - 2 * PROPOTION);
				}
				return;
			}
		}
	}
}

void simulation_con::Ord_check_signal(vehicle* veh) {
	int curr = veh->cur_road;
	signal* cursig = this->ord_signals[curr];
	if (cursig->getdir() == 0)//-----
	{
		if (veh->lastpos.y() - cursig->getPos().y() >= 2*PROPOTION && veh->position.y() - cursig->getPos().y() < 2*PROPOTION) {
			if (cursig->isgreen()) {
				ord_veh_num[curr]++;
			}
			else {
				veh->move_back();
				veh->position.setY(cursig->getPos().y() + 2 * PROPOTION);
			}
			return;

		}
		if (veh->lastpos.y() - cursig->getPos().y() <= (-2)*PROPOTION && veh->position.y() - cursig->getPos().y() > (-2)*PROPOTION) {
			if (cursig->isgreen()) {
				ord_veh_num[curr]++;
			}
			else {
				veh->move_back();
				veh->position.setY(cursig->getPos().y() - 2 * PROPOTION);
			}
			return;
		}
	}
	if (cursig->getdir() == 1)//|||||
	{
		if (veh->lastpos.x() - cursig->getPos().x() >= 2 * PROPOTION && veh->position.x() - cursig->getPos().x() < 2 * PROPOTION) {
			if (cursig->isgreen()) {
				ord_veh_num[curr]++;
			}
			else {
				veh->move_back();
				veh->position.setX(cursig->getPos().x() + 2 * PROPOTION);
			}
			return;
		}
		if (veh->lastpos.x() - cursig->getPos().x() <= (-2)*PROPOTION && veh->position.x() - cursig->getPos().x() > (-2)*PROPOTION) {
			if (cursig->isgreen()) {
				ord_veh_num[curr]++;
			}
			else {
				veh->move_back();
				veh->position.setX(cursig->getPos().x() - 2 * PROPOTION);
			}
			return;
		}
	}
}

bool simulation_con::Ord_check_impact(vehicle* veh) {
	//0~7
	if (!veh->ord_conflict()) return false;
	int road = veh->cur_road;
	for (int i = 0; i < 4; i++) {
		int cur = ROAD_conflict[road][i] - 1;
		if (cur < 0) continue;
		if (this->ord_signals[cur]->isgreen()) continue;
		for (int j = 0; j < this->ROAD_conflict_veh[cur].size(); j++) {
			if (veh->impact(ROAD_conflict_veh[cur].at(j)) && !ROAD_conflict_veh[cur].at(j)->is_waiting()) {
			//if (veh->impact(ROAD_conflict_veh[cur].at(j))) {
				veh->wait();
				return true;
			}
		}
	}
	return false;
}

bool simulation_con::CFI_check_impact(vehicle* veh) {
	//0~7
	if (!veh->cfi_conflict()) return false;
	int road = veh->cur_road;
	for (int i = 0; i < 4; i++) {
		int cur = ROAD_conflict[road][i] - 1;
		if (cur < 0) continue;
		if (veh->position.x() <= 237) {
			if (cur == 2 && this->cfi_signals[13]->isgreen()) continue;
			if (cur == 5 && this->cfi_signals[12]->isgreen()) continue;
			if (cur == 7 && this->cfi_signals[9]->isgreen()) continue;
		}
		else if (veh->position.x() >= 1043) {
			if (cur == 1 && this->cfi_signals[10]->isgreen()) continue;
			if (cur == 6 && this->cfi_signals[11]->isgreen()) continue;
			if (cur == 3 && this->cfi_signals[8]->isgreen()) continue;
		}
		else {//in the middle area
			if (veh->cur_road == 6 && cur == 3) continue;//4 and 6
			if (veh->cur_road == 3 && cur == 6) continue;
			if (veh->cur_road == 2 && cur == 7) continue;//3 and 8
			if (veh->cur_road == 7 && cur == 2) continue;
			if (cur == 3 && this->cfi_signals[8]->isgreen()) continue;
			if (cur == 7 && this->cfi_signals[9]->isgreen()) continue;
			if (cur != 3 && cur != 7 && this->cfi_signals[cur]->isgreen()) continue;
		}
		for (int j = 0; j < this->ROAD_conflict_veh[cur].size(); j++) {
			if (veh->impact(ROAD_conflict_veh[cur].at(j)) && !ROAD_conflict_veh[cur].at(j)->is_waiting()) {
			//if (veh->impact(ROAD_conflict_veh[cur].at(j))) {
				veh->wait();
				return true;
			}
		}
	}
	return false;
}