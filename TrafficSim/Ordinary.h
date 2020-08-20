#pragma once

#include <deque>
#include <queue>
#include <algorithm>
#include <cstdlib> 
#include <ctime>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

class Ordinary
{
private:
	//Internal variable
	int road_t[8],start[8],end[8]; //Green time, start, end time
	int vehicle[8]; //Passing the vehicle this cycle
	float road_q[8];  //efficiency this cycle
	bool is_green[8]; //Whether it is green or not, for external interface

	//******************** Used when queuing***********************
	int se[8][8];//Memory search    1 return directly
	int state[8];//0  yet added
	int tem_s[8],tem_e[8];// assignment in the process
	int time1,time2,min_cycle;//queue tail time, process assignment
	deque<int> l[2];//assignment in the process
	void init();
	void insert();
	//**************************************************************

	//Common function
	inline bool isin(int i,int j);//Whether i is a compatible lane of j, the parameter is the actual lane number minus one
	inline void get_q(); //get efficiency

	//process
	void get_num(int veh_num[8]);  //Get traffic and calculate efficiency
	void change_t();//The transit time can be modified according to the efficiency (controlled within the range)
	void get_list();//Recursive call
	void get_cycle();//Whether the cycle is suitable

public:
	Ordinary(void);
	virtual ~Ordinary(void);

	//************  External interface  ***********
	void fixed_next();//Accumulated transit time 
	void next(int veh_num[8]);  //The overall process, get the next cycle timing
	bool * judge(int cur_t);//Judging the status of the signal light according to the current time, the green light is true
	void get_last(int cur_t);//Get the actual transit time in the last cycle
	int * get_t() {
		return road_t;
	}

	int cycle;

	int all_road_t[8];//Total transit time per lane

	//The initial period is fixed at 90s, not repairable 1

//Tunable parameter£º
	//const float Q[8] = { 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3 };
	//const float Q[8] = { 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8 };
	const float Q[8] = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 }; //Define the maximum traffic efficiency of one lane (passing vehicle/green time), 0.5 is the single lane preset
	const int Tmax = 90; //Define the maximum time allowed for a single cycle
	const int S_Tmin = 10; //Define the minimum time allowed for a single lane
	const int S_Tmax = Tmax - S_Tmin * 3; //Can get the maximum time allowed for a single lane      without modification
	//Minimum time of a single cycle = S_Tmin * 4

	const float lambda = 1.0f / 3.0f;//Best pass efficiency lower bound coefficient
	const float miu = 2.0f / 3.0f;//Optimal efficiency upper limit factor

	//Compatible lanes 1-8 true lane number, not recommended for modification
	const int combination[8][3] = { { 2,4,5 },{ 1,6,7 },{ 4,6,7 },{ 1,3,8 },{ 1,6,8 },{ 2,3,5 },{ 2,3,8 },{ 4,5,7 } };

	float min_q[8]; //Lower limit of traffic efficiency
	float max_q[8]; //Pass efficiency limit
	void get_range() { //Get efficiency range Called when initializing
		for (int i = 0; i < 8; i++) {
			min_q[i] = Q[i] * lambda;
			max_q[i] = Q[i] * miu;
		}
	}
};

