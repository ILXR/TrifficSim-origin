#pragma once

#include <deque>
#include <queue>
#include <algorithm>
#include <cstdlib> 
#include <ctime>
#include <cmath>
#include <iostream>
#include <string>
#include <Qdebug.h>

using namespace std;

//General function
float getaverage(const float time[], int num);
float getvariance(const float time[], int num);
float getsum(const float time[], int num);

class Left
{
private:
	bool flag[10];//two ranges? get_time
	int road_t[10],start[10][2],end[10][2]; //Green time, start, end time
	int T[3],phasenum;  //Three phase time   phase selection
	float road_q[10];  //Traffic efficiency
	int vehicle[10]; //vehicles
	
	//Used to allocate the time of the lane in two phases
	float other_q[4][2]; //efficiency  4,8,9,10
	int other_t[4][2];   //Green time  4,8,9,10
	int other_n[4][2];   //vehicles  4,8,9,10

	//Internal process
	void get_time();//get start end road_t other_t
	void get_num(int veh_num[10]);//Get traffic and calculate efficiency
	void change_t(); //The transit time can be modified according to the efficiency (controlled within the range)
	void get_cycle();//Select cycle type calculation time

public:
	Left(void);
	virtual ~Left(void);

	//************  External interface  ***********
	void fixed_next();//Accumulated transit time 
	void next(int veh_num[10]);  //The overall process, get the next cycle timing
	void judge(int cur_t,int vehnum[10],int num2, int num3, int num6, int num7, int num9, int num10,bool * is_green);//Judging the status of the signal light according to the current time, the green light is true
	void get_last(int cur_t);//Get the actual transit time in the last cycle
	int * get_t() {
		return road_t;
	}

	int cycle;//Current cycle time

	int all_road_t[10];//Total transit time per lane

public:
	//parameter
	//Phase distribution
	const int PH[3][3][4] = { { {1,5,9,10},{2,6,0,0},{3,7,4,8} },
						  { {1,2,4,10},{5,6,8,9},{3,7,4,8} },
						  { {1,5,9,10},{2,7,4,10},{3,6,8,9} } };
	float min_q[10]; //Lower limit of traffic efficiency
	float max_q[10]; //Pass efficiency limit
	//Tunable parameter£º
	//const float Q[10] = { 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8 };
	//const float Q[8] = { 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3 };
	const float Q[10] = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 }; //Define the maximum traffic efficiency of one lane (passing vehicle/green time), 0.5 is the single lane preset
	//Cycle time limit
	const float Cmin = 45;
	const float Cmax = 90;
	//Efficiency limit
	const float lambda = 1.0f / 3.0f;
	const float miu = 2.0f / 3.0f;

	const int car_max = 11; //Turn left to turn lane to accommodate vehicles
	//Minimum transit time per lane   Minimum transit time per phase
	const int Tmin = 10;
	void get_range() { //Get efficiency range    Called when initializing
		for (int i = 0; i < 10; i++) {
			min_q[i] = Q[i] * lambda;
			max_q[i] = Q[i] * miu;
		}
	}
};

