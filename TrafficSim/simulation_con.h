#pragma once

#include "TrafficSim.h"
#include "Com_use.h"
#include "signal.h"
#include "Left.h"
#include "Ordinary.h"
#include "ui_Circle_Timing.h"

class TrafficSim;

class simulation_con:public QWidget
{
	Q_OBJECT
private:
	Ui::Circle_TimingClass ui;
	TrafficSim * parrent;
	Road_Line * road_line;

	//control
	Ordinary * normal[2];
	Ordinary* ord_fixed;
	Left * left[2];
	Left * cfi_fixed;

	bool sim_running;

	//time per step   sec_second
	float time_slots;

	//generator probability
	float probability[8];

	//things needed to be draw
	QList<vehicle *> vehicles_inputs[8];
	QList<vehicle *> ROAD_conflict_veh[8];

	int ord_record_veh[8];
	int cfi_record_veh[14];
	int ord_veh_num[8];
	int cfi_veh_num[14];

	//In order to save memory
	int vehicles_toin[8];
	QVector<signal *> ord_signals;
	QVector<signal *> cfi_signals;

public:
	//simulation time  resolution*period  refresh times
	int all_time;
	int cur_time;//current time
	int cycles;//cycle num
	int all_cyc;//recorded time


	simulation_con(TrafficSim* parrent);
	virtual ~simulation_con();

	void start_sim();

	void single_step_sim(QPainter &paint);
	void single_step_draw(QPainter &paint);

	void stop_sim();

	bool is_running() {
		return this->sim_running;
	}
	bool Ord_check_impact(vehicle* veh);
	bool CFI_check_impact(vehicle* veh);
	void Ord_check_signal(vehicle* veh);
	void CFI_check_signal(vehicle* veh);

signals:
	void sim_finished(int all_veh[]);
};

