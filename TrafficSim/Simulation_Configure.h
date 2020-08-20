#pragma once

#include "ui_Simulation_Configure.h"
#include "Com_use.h"

class Simulation_Configure :
	public QMainWindow
{
	Q_OBJECT

public:
	Simulation_Configure(QWidget *parent = Q_NULLPTR);
	~Simulation_Configure();

private:
	Ui::Simulation_ConfigureClass ui;
	//simulation time
	int period;
	//steps per simulation_second
	int resolution;
	//simulation_seconds per seconds
	int sim_speed;
	//max speed
	bool max_speed;

private slots:
	void click_ok() {
		this->period = this->ui.Period->text().toInt();
		this->resolution = this->ui.Resolution->text().toInt();
		this->sim_speed = this->ui.Speed->text().toInt();
		if (this->period < 1 || this->resolution == 0 || this->sim_speed == 0) {
			QMessageBox warn(QMessageBox::Warning, QStringLiteral("警告"), QStringLiteral("参数设置过小！"), QMessageBox::Yes,this);
			warn.exec();
			return;
		}
		if (this->resolution > 10 || this->sim_speed > 1000 || this->period > 100000) {
			QMessageBox warn(QMessageBox::Warning, QStringLiteral("警告"), QStringLiteral("参数设置过大！"), QMessageBox::Yes, this);
			warn.exec();
			return;
		}
		emit send_parameter(this->period, this->resolution, this->sim_speed, this->max_speed);
		this->hide();
	};
	void change_text_state() {
		if (this->ui.MaxSpeed->isChecked()) {
			this->max_speed = true;
			this->ui.Speed->setEnabled(false);
		}
		else {
			this->max_speed = false;
			this->ui.Speed->setEnabled(true);
		}
	};

public slots:
	void get_parameter(int period, int resolution, int sim_speed, bool max_speed) {
		this->period = period;
		this->resolution = resolution;
		this->sim_speed = sim_speed;
		this->max_speed = max_speed;
		this->ui.Period->setText(QString::number(period));
		this->ui.Resolution->setText(QString::number(resolution));
		this->ui.Speed->setText(QString::number(sim_speed));
		if (max_speed) {
			this->ui.MaxSpeed->setChecked(true);
		}
		else
			this->ui.MaxSpeed->setChecked(false);
		this->show();
	};

signals:
	void send_parameter(int period, int resolution, int sim_speed, bool max_speed);
};

