#include "TrafficSim.h"

TrafficSim::TrafficSim(QWidget *parent)
	: QMainWindow(parent)
{
	Road_Line line;
	memset(this->ord_vehicles, 0, sizeof(this->ord_vehicles));
	memset(this->cfi_vehicles, 0, sizeof(this->cfi_vehicles));

	this->simstate = 0;
	this->mouse_x = 0;
	this->mouse_y = 0;
	this->period = 1800;
	this->resolution = 5;
	this->sim_speed = 10;
	this->file_read_error = false;
	this->max_speed = false;
	this->sim_running = false;
	this->pause = false;
	this->tonext = false;
	this->curroad = Ordinary_;
	this->cursignal = Fixed;
	this->simulation = new simulation_con(this);
	this->timer = new QTimer(this);
	this->background = new QPixmap(":/TrafficSim/images/Ordinary.png");

	//mouse move event enable
	ui.setupUi(this);
	this->ui.centralWidget->setMouseTracking(true);
	this->ui.mainToolBar->setMouseTracking(true);
	this->ui.statusBar->setMouseTracking(true);
	this->setMouseTracking(true);
	this->ui.scence_Ordinary->setChecked(true);
	this->ui.signal_Fixed->setChecked(true);

	/*QPalette bgpal = palette();
	bgpal.setColor(QPalette::Background, QColor(0, 0, 0, 255));
	bgpal.setColor(QPalette::Foreground, QColor(255, 255, 255, 255)); setPalette(bgpal);*/

	//this->setAttribute(Qt::WA_PaintOnScreen);

	//ordinary vehicles
	QObject::connect(this->ui.vehicles_Ordinary,&QAction::triggered,this, &TrafficSim::click_ord_vehicles_input);
	QObject::connect(this, &TrafficSim::send_ord_vehicles, &this->Oinputs, &Ordinary_Vehicles_Inputs::get_parameter);
	QObject::connect(&this->Oinputs,&Ordinary_Vehicles_Inputs::send_parameter,this,&TrafficSim::get_ord_vehicles);

	//cfi vehicles
	QObject::connect(this->ui.vehicles_CFI, &QAction::triggered, this, &TrafficSim::click_cfi_vehicles_input);
	QObject::connect(this, &TrafficSim::send_cfi_vehicles, &this->Cinputs, &CFI_Vehicles_Inputs::get_parameter);
	QObject::connect(&this->Cinputs, &CFI_Vehicles_Inputs::send_parameter, this, &TrafficSim::get_cfi_vehicles);
	QObject::connect(&this->Cinputs,&CFI_Vehicles_Inputs::get_ord_veh,this, &TrafficSim::send_ord_veh_to_cfi);
	QObject::connect(this, &TrafficSim::send_ord_to_cfi, &this->Cinputs, &CFI_Vehicles_Inputs::get_parameter);

	//simulation config
	QObject::connect(this->ui.simulation_Configuration,&QAction::triggered,this,&TrafficSim::click_simulation_configure);
	QObject::connect(&this->Simconfig, &Simulation_Configure::send_parameter, this, &TrafficSim::get_sim_parameter);
	QObject::connect(this, &TrafficSim::send_sim_parameter, &this->Simconfig, &Simulation_Configure::get_parameter);

	//change parameters
	QObject::connect(this->ui.scence_Ordinary,&QAction::triggered,this,&TrafficSim::change_road);
	QObject::connect(this->ui.scence_CFI, &QAction::triggered, this, &TrafficSim::change_road);
	QObject::connect(this->ui.signal_Fixed, &QAction::triggered, this, &TrafficSim::change_signal);
	QObject::connect(this->ui.signal_Adaptive, &QAction::triggered, this, &TrafficSim::change_signal);

	//simulation
	QObject::connect(this->ui.action_Run, &QAction::triggered, this, &TrafficSim::start_sim);
	//QObject::connect(this->ui.action_Run, &QAction::triggered, this, &TrafficSim::show_file_error_tip);
	QObject::connect(this->ui.action_SingleStep, &QAction::triggered, this, &TrafficSim::single_step_sim);
	QObject::connect(this->ui.action_Stop, &QAction::triggered, this, &TrafficSim::stop_sim);
	QObject::connect(this->timer, &QTimer::timeout, this, &TrafficSim::time_func);
	QObject::connect(this->simulation,&simulation_con::sim_finished,this, &TrafficSim::sim_finished);
	QObject::connect(this, &TrafficSim::send_result, this->Result, &SimResult::show_win);
	QObject::connect(this->ui.OpenFile, &QAction::triggered,this, &TrafficSim::click_openfile);
	QObject::connect(this, &TrafficSim::file_format_error,this, &TrafficSim::show_file_error_tip);
	//timer->start(1000);
}

void TrafficSim::paintEvent(QPaintEvent *event) {
	Q_UNUSED(event);
	//qDebug() << "paint";
	tonext = false;
	painter.begin(this);
	painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
	painter.setFont(QFont("Microsoft YaHei",10,63));
	painter.setBrush(QBrush(Qt::white));
	int h = this->ui.menuBar->height();
	this->setFixedSize(background->width(), background->height() + h);
	painter.drawPixmap(0, h, background->width(), background->height(), *background);

	QPointF pos = this->ui.statusBar->pos();
	//QString pos = QString::number((float)mouse_x / PROPOTION, 'f', 1) + " , " + QString::number((float)mouse_y / PROPOTION, 'f', 1);
	painter.drawText(pos.x()+10, pos.y()-10, 150 ,40, Qt::AlignCenter, QString::number((float)mouse_x / PROPOTION, 'f', 1) + " , " + QString::number((float)mouse_y / PROPOTION, 'f', 1));

	if (sim_running || pause) {
		//single step
		this->simulation->single_step_sim(painter);
	}
	else {
		this->simulation->single_step_draw(painter);
	}

	if (simulation->is_running()) {//show time
		QString time = QString::number((float)this->simulation->cur_time / this->resolution, 'f', 1) + "/" + QString::number(this->period, 'f', 1);
		painter.drawText(pos.x() + 200, pos.y() - 10, 200, 40, Qt::AlignCenter, time);
	}
	painter.end();
	tonext = true;
	pause = false;
}

void TrafficSim::mouseMoveEvent(QMouseEvent * e) {
	
	/*float x = e->x()/ PROPOTION;
	float y = e->y() / PROPOTION;
	QString pos = QString::number(x,'f',1) + " , " + QString::number(y, 'f', 1);*/
	this->mouse_x = e->x();
	this->mouse_y = e->y();
	//QString pos = QString::number((float)mouse_x/PROPOTION,'f', 1) + " , " + QString::number((float)mouse_y/PROPOTION, 'f', 1);
	if(!sim_running)
		update();
}

void TrafficSim::start_sim()
{
	if (this->curroad == Ordinary_) {
		this->background->load(":/TrafficSim/images/Ordinary.png");
		//update();
	}
	if (this->curroad == CFI) {
		this->background->load(":/TrafficSim/images/CFI.png");
		//update();
	}

	this->simulation->start_sim();
	this->ui.action_Run->setEnabled(false);
	this->ui.menuBar->setEnabled(false);
	this->sim_running = true;
	this->pause = false;
	//run timer
	float interval;
	if (this->max_speed) {
		this->timer->start(1);
	}
	else {
		interval = 1000 / (this->resolution*this->sim_speed);
		this->timer->start(interval);
	}
}

void TrafficSim::single_step_sim()
{
	if (!this->simulation->is_running()) return;
	this->ui.action_Run->setEnabled(true);
	this->sim_running = false;
	this->pause = true;
	//run single step
	if (this->timer->isActive()) {
		this->timer->stop();
	}
	update();
}

void TrafficSim::stop_sim()
{
	//state machine init
	this->confile.close();
	this->simstate = 0;
	change_road();
	change_signal();

	if(simulation->is_running())
		this->simulation->stop_sim();
	this->ui.action_Run->setEnabled(true);
	this->ui.menuBar->setEnabled(true);
	this->sim_running = false;
	this->pause = false;
	//stop and clear
	this->timer->stop();
	update();
}

