#include "TrafficSim.h"
#include "Com_use.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	QApplication a(argc, argv);
	TrafficSim w;
	w.show();
	return a.exec();
}
