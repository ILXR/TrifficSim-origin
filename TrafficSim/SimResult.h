#pragma once

#include "ui_Simulation_Result.h"
#include "Com_use.h"

class SimResult :
	public QMainWindow
{
	Q_OBJECT
public:
	SimResult(QWidget *parent = Q_NULLPTR);
	virtual ~SimResult();
private:
	Ui::Simulation_ResultClass ui;
	RoadType road;
	SignalControl signal;

private slots:
	void click_ok() {
		this->close();
	}
public slots:
	void show_win(RoadType road, SignalControl signal,int time,int vehnum[]) {
		if (road == Ordinary_) {
			this->ui.road_text->setText(QStringLiteral("普通路口"));
		}
		else
			this->ui.road_text->setText(QStringLiteral("移位左转"));

		if (signal == Fixed)
			this->ui.signal_text->setText(QStringLiteral("固定配时"));
		else
			this->ui.signal_text->setText(QStringLiteral("自适应配时"));

		QString text;
		text.append("Simulation time: " + QString::number(time) + " s\n");
		int sum = 0;
		for (int i = 0; i < 8; i++) {
			text.append("L" + QString::number(i + 1) + ": " + QString::number(vehnum[i])+"\n");
			sum += vehnum[i];
		}
		text.append("Sum: " + QString::number(sum));
		float eff = (float)sum / time;
		text.append("\nEfficiency: " + QString::number(eff));
		this->ui.result_test->setText(text);
		this->show();
	}
};

