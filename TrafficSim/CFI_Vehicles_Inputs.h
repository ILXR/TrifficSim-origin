#pragma once

#include "ui_CFI_Vehicles_Inputs.h"
#include "Com_use.h"

class CFI_Vehicles_Inputs :
	public QMainWindow
{
	Q_OBJECT
public:
	CFI_Vehicles_Inputs(QWidget *parent = Q_NULLPTR);
	~CFI_Vehicles_Inputs();

private:
	//all num of vehicles needs to be generalize
	int vehicles[8];
	int maxnum;
	Ui::CFI_Vehicles_InputsClass ui;

private slots:
	void click_ok() {
		this->vehicles[0] = this->ui.L1->text().toInt();
		this->vehicles[1] = this->ui.L2->text().toInt();
		this->vehicles[2] = this->ui.L3->text().toInt();
		this->vehicles[3] = this->ui.L4->text().toInt();
		this->vehicles[4] = this->ui.L5->text().toInt();
		this->vehicles[5] = this->ui.L6->text().toInt();
		this->vehicles[6] = this->ui.L7->text().toInt();
		this->vehicles[7] = this->ui.L8->text().toInt();
		for (int i = 0; i < 8; i++) {
			if (this->vehicles[i] > this->maxnum) {
				QMessageBox warn(QMessageBox::Warning, QStringLiteral("警告"), QStringLiteral("参数设置过大！"), QMessageBox::Yes, this);
				warn.exec();
				return;
			}
		}
		emit send_parameter(this->vehicles);
		this->hide();
	};
	void click_min() {
		this->ui.L1->setText(QString::number(0));
		this->ui.L2->setText(QString::number(0));
		this->ui.L3->setText(QString::number(0));
		this->ui.L4->setText(QString::number(0));
		this->ui.L5->setText(QString::number(0));
		this->ui.L6->setText(QString::number(0));
		this->ui.L7->setText(QString::number(0));
		this->ui.L8->setText(QString::number(0));
	}
	void click_max() {
		int max = this->maxnum;
		this->ui.L1->setText(QString::number(max));
		this->ui.L2->setText(QString::number(max));
		this->ui.L3->setText(QString::number(max));
		this->ui.L4->setText(QString::number(max));
		this->ui.L5->setText(QString::number(max));
		this->ui.L6->setText(QString::number(max));
		this->ui.L7->setText(QString::number(max));
		this->ui.L8->setText(QString::number(max));
	}
	void click_random() {
		int randnum[8];
		int leftmax = maxnum * 11 / 90 + maxnum / 18;
		for (int i = 0; i < 8; i++) {
			if (i == 3 || i == 7) {
				randnum[i] = rand() % leftmax + 1;
			}
			else 
				randnum[i] = rand() % this->maxnum + 1;
		}
		this->ui.L1->setText(QString::number(randnum[0]));
		this->ui.L2->setText(QString::number(randnum[1]));
		this->ui.L3->setText(QString::number(randnum[2]));
		this->ui.L4->setText(QString::number(randnum[3]));
		this->ui.L5->setText(QString::number(randnum[4]));
		this->ui.L6->setText(QString::number(randnum[5]));
		this->ui.L7->setText(QString::number(randnum[6]));
		this->ui.L8->setText(QString::number(randnum[7]));
	}

public slots:
	void get_parameter(int vehicles[], int maxnum) {
		for (int i = 0; i < 8; i++) {
			this->vehicles[i] = vehicles[i];
		}
		this->maxnum = maxnum;
		this->ui.L1->setText(QString::number(vehicles[0]));
		this->ui.L2->setText(QString::number(vehicles[1]));
		this->ui.L3->setText(QString::number(vehicles[2]));
		this->ui.L4->setText(QString::number(vehicles[3]));
		this->ui.L5->setText(QString::number(vehicles[4]));
		this->ui.L6->setText(QString::number(vehicles[5]));
		this->ui.L7->setText(QString::number(vehicles[6]));
		this->ui.L8->setText(QString::number(vehicles[7]));
		this->show();
	}
	void get_same_veh() {
		emit get_ord_veh();
	}

signals:
	void send_parameter(int vehicles[]);
	void get_ord_veh();
};

