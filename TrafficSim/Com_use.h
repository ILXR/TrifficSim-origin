#pragma once

#include <qobject.h>
#include <QtWidgets/QMainWindow>
#include <qvalidator.h>
#include <qmessagebox.h>
#include <qdebug.h>
#include <qpushbutton.h>
#include <qaction.h>
#include <qpainter.h>
#include <qevent.h>
#include <qfont.h>
#include <qline.h>
#include <qpoint.h>
#include <qtimer.h>
#include <qpen.h>
#include <qlist.h>
#include <qvector.h>
#include <qfiledialog.h>
#include <qdatetime.h>

#include <vector>
#include <queue>
#include <string.h>
#include <ctime>

#include "vehicle.h"

using namespace std;

enum RoadType {
	Ordinary_,
	CFI
};

enum SignalControl {
	Fixed,
	Adaptive
};

enum SignalState {
	Red,
	Green,
	Yellow
};

//pix m scale
const float PROPOTION = 5.30; //pix/m
//min distance between cars    m
const float MINDISTANCE = 2.0;
//normal speed   m/s  == 30km/h
const float SPEED = 8;

const int ROAD_conflict[8][4] = { {3,6,7,8},{3,4,5,8},{1,2,5,8},{2,5,6,7},{2,3,4,7},{1,4,7,8},{1,4,5,6},{1,2,3,6} };

//0 -   1 |  signals position
const int Ord_Signals[][3] = { {613,350,0},{635,350,0},{736,411,1},{736,432,1},{678,533,0},{656,533,0},{554,474,1},{554,452,1} };
const int CFI_Signals[][3] = { {608,349,0},{629,349,0},{725,408,1},{725,471,1},{671,530,0},{648,530,0},{552,471,1},{553,408,1},
{1117,430,1},{154,450,1},{1045,430,1},{1045,450,1},{234,449,1},{234,430,1} };
//relationship between cfi_roads and cfi_signals
const int CFI_R_S[][2] = { {1,0},{2,11},{3,14},{4,9},{5,0},{6,13},{7,12},{8,10} };

class Road_Line {
public:
	//line in pixmap
	QVector<QLineF *> Ord_Line_pix[8];
	QVector<QLineF *> CFI_Line_pix[8];
	//points in pixmap
	QVector<QPointF*> Ord_Point[8];
	QVector<QPointF*> CFI_Point[8];
	//signal controllors

	Road_Line(){
		for (int i = 0; i < 8; i++) {
			Ord_Line_pix[i].clear();
			CFI_Line_pix[i].clear();
			Ord_Point[i].clear();
			CFI_Point[i].clear();
		}

		Ord_Point[0].append(new QPointF(614, 15));
		Ord_Point[0].append(new QPointF(614,868));
		Ord_Point[1].append(new QPointF(635,15));
		Ord_Point[1].append(new QPointF(635, 352));
		Ord_Point[1].append(new QPointF(638,370));
		Ord_Point[1].append(new QPointF(649,424));
		Ord_Point[1].append(new QPointF(691,446));
		Ord_Point[1].append(new QPointF(734,453));
		Ord_Point[1].append(new QPointF(1306,452));
		Ord_Point[2].append(new QPointF(1306,409));
		Ord_Point[2].append(new QPointF(-15, 409));
		Ord_Point[3].append(new QPointF(1306, 431));
		Ord_Point[3].append(new QPointF(736, 431));
		Ord_Point[3].append(new QPointF(691,435));
		Ord_Point[3].append(new QPointF(645,470));
		Ord_Point[3].append(new QPointF(636,505));
		Ord_Point[3].append(new QPointF(635,532));
		Ord_Point[3].append(new QPointF(635,868));
		Ord_Point[4].append(new QPointF(679,868));
		Ord_Point[4].append(new QPointF(677,-15));
		Ord_Point[5].append(new QPointF(657,868));
		Ord_Point[5].append(new QPointF(657,531));
		Ord_Point[5].append(new QPointF(646,485));
		Ord_Point[5].append(new QPointF(626,457));
		Ord_Point[5].append(new QPointF(578,435));
		Ord_Point[5].append(new QPointF(554,431));
		Ord_Point[5].append(new QPointF(-15,431));
		Ord_Point[6].append(new QPointF(-15,475));
		Ord_Point[6].append(new QPointF(1306,475));
		Ord_Point[7].append(new QPointF(-15,454));
		Ord_Point[7].append(new QPointF(556, 454));
		Ord_Point[7].append(new QPointF(592,442));
		Ord_Point[7].append(new QPointF(639,424));
		Ord_Point[7].append(new QPointF(650,383));
		Ord_Point[7].append(new QPointF(655,351));
		Ord_Point[7].append(new QPointF(655,15));
		
		CFI_Point[0].append(new QPointF(607, 15));
		CFI_Point[0].append(new QPointF(607, 860));
		CFI_Point[1].append(new QPointF(628,15));
		CFI_Point[1].append(new QPointF(628, 351));
		CFI_Point[1].append(new QPointF(632,382));
		CFI_Point[1].append(new QPointF(659,414));
		CFI_Point[1].append(new QPointF(706, 425));
		CFI_Point[1].append(new QPointF(730,430));
		CFI_Point[1].append(new QPointF(1061,429));
		CFI_Point[1].append(new QPointF(1108,449));
		CFI_Point[1].append(new QPointF(1287,451));
		CFI_Point[2].append(new QPointF(1287, 409));
		CFI_Point[2].append(new QPointF(726, 409));
		CFI_Point[2].append(new QPointF(554, 430));
		CFI_Point[2].append(new QPointF(228, 430));
		CFI_Point[2].append(new QPointF(166, 408));
		CFI_Point[2].append(new QPointF(-15, 408));
		CFI_Point[3].append(new QPointF(1287, 429));
		CFI_Point[3].append(new QPointF(1111, 429));
		CFI_Point[3].append(new QPointF(1046, 470));
		CFI_Point[3].append(new QPointF(725, 470));
		CFI_Point[3].append(new QPointF(684, 477));
		CFI_Point[3].append(new QPointF(645, 493));
		CFI_Point[3].append(new QPointF(631, 509));
		CFI_Point[3].append(new QPointF(627, 529));
		CFI_Point[3].append(new QPointF(627, 860));
		CFI_Point[4].append(new QPointF(670, 860));
		CFI_Point[4].append(new QPointF(670, 15));
		CFI_Point[5].append(new QPointF(649, 860));
		CFI_Point[5].append(new QPointF(649, 529));
		CFI_Point[5].append(new QPointF(640, 495));
		CFI_Point[5].append(new QPointF(620, 471));
		CFI_Point[5].append(new QPointF(582, 457));
		CFI_Point[5].append(new QPointF(554, 451));
		CFI_Point[5].append(new QPointF(224, 450));
		CFI_Point[5].append(new QPointF(159, 428));
		CFI_Point[5].append(new QPointF(-15, 428));
		CFI_Point[6].append(new QPointF(-15, 470));
		CFI_Point[6].append(new QPointF(554, 471));
		CFI_Point[6].append(new QPointF(727, 450));
		CFI_Point[6].append(new QPointF(1049, 450));
		CFI_Point[6].append(new QPointF(1102, 469));
		CFI_Point[6].append(new QPointF(1287, 472));
		CFI_Point[7].append(new QPointF(-15, 449));
		CFI_Point[7].append(new QPointF(163, 451));
		CFI_Point[7].append(new QPointF(230, 411));
		CFI_Point[7].append(new QPointF(554, 408));
		CFI_Point[7].append(new QPointF(582, 402));
		CFI_Point[7].append(new QPointF(618, 393));
		CFI_Point[7].append(new QPointF(641, 370));
		CFI_Point[7].append(new QPointF(649, 351));
		CFI_Point[7].append(new QPointF(649, 15));

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < Ord_Point[i].size()-1; j++) {
				Ord_Line_pix[i].append(new QLineF(Ord_Point[i][j]->x(), Ord_Point[i][j]->y(), Ord_Point[i][j+1]->x(), Ord_Point[i][j+1]->y()));
			}
			for (int j = 0; j < CFI_Point[i].size()-1; j++) {
				CFI_Line_pix[i].append(new QLineF(CFI_Point[i][j]->x(), CFI_Point[i][j]->y(), CFI_Point[i][j+1]->x(), CFI_Point[i][j+1]->y()));
			}
		}
	};
};