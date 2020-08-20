#pragma once

#include "Com_use.h"
#include "ui_TrafficSim.h"
#include "CFI_Vehicles_Inputs.h"
#include "Ordinary_Vehicles_Inputs.h"
#include "Simulation_Configure.h"
#include "simulation_con.h"
#include "SimResult.h"

class simulation_con;


class TrafficSim : public QMainWindow
{
	Q_OBJECT

public:
	TrafficSim(QWidget *parent = Q_NULLPTR);

	//share the data
	friend class simulation_con;

private://private parameters
	//Ui and new windows
	Ui::TrafficSimClass ui;
	Ordinary_Vehicles_Inputs Oinputs = new Ordinary_Vehicles_Inputs(this);
	CFI_Vehicles_Inputs Cinputs = new CFI_Vehicles_Inputs(this);
	Simulation_Configure Simconfig = new Simulation_Configure(this);
	SimResult* Result = new SimResult(this);

	//other paramater
	//simulation state
	bool sim_running;
	bool pause; //single step ,if true, dont refresh
	QTimer * timer; //time out->time func
	simulation_con * simulation;
	//this drawing finished
	bool tonext;

	//simulation configure
	QFile confile;

	//simulation time
	int period;
	//steps per simulation_second
	int resolution;
	//simulation_seconds per seconds
	int sim_speed;
	//max sim speed
	bool max_speed;

	//roadtype and signalcontrol
	RoadType curroad;
	SignalControl cursignal;
	int simstate;//0~4
	bool file_read_error;

	//all num of vehicles needs to be generalize
	int ord_vehicles[8];
	int cfi_vehicles[8];

	//paint
	QPainter painter;
	QPixmap *background;

	//Status bar
	int mouse_x,mouse_y;


private://private func
	//paint event re-write
	void paintEvent(QPaintEvent *);
	void mouseMoveEvent(QMouseEvent *event);
	void read_confile() {
		//qDebug() << simstate;
		if (!confile.isOpen()) return;
		//qDebug() << "change";
		bool needread = false;
		switch (simstate) {
		case 0: {
			needread = true;
			break;
		}
		case 1: {
			simstate = 2;
			curroad = Ordinary_;
			cursignal = Adaptive;
			start_sim();
			break;
		}
		case 2: {
			simstate = 3;
			curroad = CFI;
			cursignal = Fixed;
			start_sim();
			break;
		}
		case 3: {
			simstate = 4;
			curroad = CFI;
			cursignal = Adaptive;
			start_sim();
			break;
		}
		case 4: {
			needread = true;
			break;
		}
		default: {
			simstate = 0;
			break;
		}
		}
		if (needread && !confile.atEnd()) {
			//qDebug() << "read";
			if (simstate == 0 || simstate == 4) {
				QString line = confile.readLine();
				line.trimmed();
				QStringList list = line.split(" ");
				if (list.length() < 9) {
					simstate = 0;
					confile.close();
					file_read_error = true;
					emit file_format_error();
					return;
				}
				bool flag = true;
				int period = list.at(0).toInt(&flag);
				if (!flag) {
					simstate = 0;
					confile.close();
					file_read_error = true;
					emit file_format_error();
					return;
				}
				this->period = period;
				for (int i = 0; i < 8; i++) {
					int num = list.at(i + 1).toInt(&flag);
					if (!flag) {
						simstate = 0;
						confile.close();
						file_read_error = true;
						emit file_format_error();
						return;
					}
					this->ord_vehicles[i] = num;
					this->cfi_vehicles[i] = num;
				}
			}
			switch (simstate) {
			case 0: {
				simstate = 1;
				curroad = Ordinary_;
				cursignal = Fixed;
				break;
			}
			case 1: {
				break;
			}
			case 2: {
				break;
			}
			case 3: {
				break;
			}
			case 4: {
				simstate = 1;
				curroad = Ordinary_;
				cursignal = Fixed;
				break;
			}
			}
			start_sim();
			return;
		}
		else if(needread && confile.atEnd()) {
			//qDebug() << "at end";
			//end
			confile.close();
			change_road();
			change_signal();
			switch (simstate) {
			case 0: {
				break;
			}
			case 1: {
				simstate = 0;
				break;
			}
			case 2: {
				simstate = 0;
				break;
			}
			case 3: {
				simstate = 0;
				break;
			}
			case 4: {
				simstate = 0;
				break;
			}
			}
			return;
		}
	}

private slots:
	void show_file_error_tip() {
		//qDebug() << "tip1";
		/*QMessageBox mesg;
		mesg.warning(this, "Warning", "File data format error");*/
		//qDebug() << "tip2";
		return;
	}
	//open new windows
	void click_ord_vehicles_input(bool triggered) {
		int maxnum = this->period;
		emit send_ord_vehicles(this->ord_vehicles,maxnum);
	};
	void click_cfi_vehicles_input(bool triggered) {
		int maxnum = this->period;
		emit send_cfi_vehicles(this->cfi_vehicles, maxnum);
	};
	void click_simulation_configure(bool triggered) {
		emit send_sim_parameter(this->period, this->resolution, this->sim_speed, this->max_speed);
	}
	//get parameters
	void get_sim_parameter(int period, int resolution, int sim_speed, bool max_speed) {
		this->period = period;
		this->resolution = resolution;
		this->sim_speed = sim_speed;
		this->max_speed = max_speed;
	};
	void get_ord_vehicles(int vehicles[]) {
		for (int i = 0; i < 8; i++) {
			this->ord_vehicles[i] = vehicles[i];
		}
	};
	void get_cfi_vehicles(int vehicles[]) {
		for (int i = 0; i < 8; i++) {
			this->cfi_vehicles[i] = vehicles[i];
		}
	};
	//set parameters
	void change_road() {
		if (this->ui.scence_Ordinary->isChecked()) {
			if (this->curroad != Ordinary_) {
				this->background->load(":/TrafficSim/images/Ordinary.png");
				this->curroad = Ordinary_;
				update();
			}
		}
		if (this->ui.scence_CFI->isChecked()) {
			if (this->curroad != CFI) {
				this->background->load(":/TrafficSim/images/CFI.png");
				this->curroad = CFI;
				update();
			}
		}
	}
	void change_signal() {
		if (this->ui.signal_Fixed->isChecked()) {
			if (this->cursignal != Fixed) {
				this->cursignal = Fixed;
			}
		}
		if (this->ui.signal_Adaptive->isChecked()) {
			if (this->cursignal != Adaptive) {
				this->cursignal = Adaptive;
			}
		}
	}

private slots:
	//simulation
	void start_sim();
	void single_step_sim();
	void stop_sim();

	void time_func(){
		if (!this->sim_running) return;
		while (!this->tonext) {}	
		update();
	}
	void sim_finished(int all_veh[]) {
		if(simstate == 0)
			emit send_result(this->curroad,this->cursignal,this->period,all_veh);
		int num = 8;
		int all = 0;
		for (int i = 0; i < num; i++) {
			all += all_veh[i];
		}
		//stop simulation
		this->ui.action_Run->setEnabled(true);
		this->ui.menuBar->setEnabled(true);
		this->sim_running = false;
		this->pause = false;
		//stop and clear
		this->timer->stop();
		update();

		QDir curdir;
		QString filename = curdir.currentPath()+ "/output.txt";
		QFile outfile(filename);
		if (!outfile.exists())
			outfile.setFileName(filename);
		if (!outfile.open(QIODevice::Append | QIODevice::Text)) {
			QMessageBox mesg;
			mesg.warning(this, QStringLiteral("警告"), QStringLiteral("文件写入错误：无法打开！"));
			return;
		}

		QTextStream output(&outfile);
		QDateTime current_date_time = QDateTime::currentDateTime();
		QString current_date = current_date_time.toString("yyyy/MM/dd - hh:mm:ss");
		output << current_date;
		if (this->curroad == Ordinary_) {
			output <<" Ordinary ";
		}
		else
			output << " CFI ";

		if (this->cursignal == Fixed)
			output << "Fixed" << " ";
		else
			output << "Adaptive" << " ";

		output << "period: " << this->period << endl << "input: ";
		for (int i = 0; i < 8; i++) {
			if (this->curroad == Ordinary_) {
				output << ord_vehicles[i] << " ";
			}
			else
				output << cfi_vehicles[i] << " ";
		}
		/*output << "\nveh: ";
		for (int i = 0; i < 8; i++) {
			output << all_veh[i] << " ";
		}*/
		output << "\nsum: " << all << endl << "effiency: " << (float)all / period << endl << endl;
		outfile.close();
		//qDebug() << "next";
		if (simstate != 0) {
			read_confile();
			/*if (file_read_error) {
				QMessageBox mesg;
				mesg.warning(this, "Warning", "File data format error");
				this->file_read_error = false;
			}*/
		}
	}
	void send_ord_veh_to_cfi() {
		int maxnum = this->period;
		emit send_ord_to_cfi(this->ord_vehicles, maxnum);
	}
	void click_openfile() {
		//qDebug() << "openfile";
		QString filename = QFileDialog::getOpenFileName(
			this, tr("open configure file"),
			"./", tr("txt files(*.txt)"));
		if (filename.isEmpty())
		{
			QMessageBox mesg;
			mesg.warning(this, QStringLiteral("警告"), QStringLiteral("没有打开文件！"));
			return;
		}
		confile.close();
		confile.setFileName(filename);
		if (!confile.exists()) {
			QMessageBox mesg;
			mesg.warning(this, QStringLiteral("警告"), QStringLiteral("文件不存在！"));
			return;
		}
		if (!confile.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QMessageBox mesg;
			mesg.warning(this, QStringLiteral("警告"), QStringLiteral("文件无法打开！"));
			return;
		}
		this->max_speed = true;
		read_confile();
		/*while (!confile.atEnd()) {
			QString line = confile.readLine();
			qDebug() << line.trimmed();
		}
		confile.close();*/
	}

public:
signals:
	//send parameters
	void file_format_error();
	void send_sim_parameter(int period, int resolution, int sim_speed, bool max_speed);
	void send_ord_vehicles(int vehicles[],int maxnum);
	void send_cfi_vehicles(int vehicles[], int maxnum);
	void send_result(RoadType road, SignalControl signal, int time, int vehnum[]);
	void send_ord_to_cfi(int vehicles[],int maxnum);
};
