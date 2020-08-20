#include "Left.h"

float getaverage(const float time[], int num) {
	float sum = 0;
	for (int i = 0; i < num; i++) {
		sum += time[i];
	}
	return sum / (float)num;
}

float getvariance(const float time[],int num) {
	float temp[4];
	float sum = 0;
	float average = getaverage(time , num);
	for (int i = 0; i < num; i++) {
		temp[i] = pow(time[i] - average, 2);
	}
	for (int i = 0; i < num; i++) {
		sum += temp[i];
	}
	return pow(sum / (float)num, 0.5);
}

float getsum(const float time[], int num) {
	float sum = 0;
	for (int i = 0; i < num; i++) {
		sum += time[i];
	}
	return sum;
}

Left::Left(void)
{
	get_range();
	memset(all_road_t,0,sizeof(all_road_t));
	for (int i = 0; i < 3; i++) {
		T[i] = 30;
	}
	cycle = 90;
	phasenum = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			other_q[i][j] = 0.5;
		}
	}
	get_time();
}

Left::~Left(void)
{
}

//using T、phasenum ; get start end road_t other_t
void Left::get_time(){
	memset(other_n,0,sizeof(other_n));
	memset(other_t,0,sizeof(other_t));
	memset(flag,0,sizeof(flag));
	memset(start,0,sizeof(start));
	memset(end,0,sizeof(end));
	memset(road_t,0,sizeof(road_t));

	int mid[3] = {0, T[0], T[0]+T[1]};
	for(int i=0;i<3;i++){
		for(int j=0;j<4;j++){
			int cur=PH[phasenum][i][j]-1;
			if (cur<0)
				continue;
			road_t[cur] += T[i];
			int tem=flag[cur]?1:0;
			flag[cur]=1;
			start[cur][tem]=mid[i];
			end[cur][tem]=mid[i]+T[i];
		}
	}

	if (phasenum == 1) { //Assigning the two phase times of the repeating lane separately
		other_t[0][0] = T[0];
		other_t[0][1] = T[2];
		other_t[1][0] = T[1];
		other_t[1][1] = T[2];
	}
	else if (phasenum == 2) {
		other_t[2][0] = T[0];
		other_t[2][1] = T[2];
		other_t[3][0] = T[0];
		other_t[3][1] = T[1];
	}
}

void Left::get_num(int veh_num[10]){
	for(int i=0;i<10;i++){
		vehicle[i]=veh_num[i];
		road_q[i] = (float)veh_num[i] / road_t[i];
	}
	if(phasenum == 1){
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				other_q[i][j] = (float)other_n[i][j]/other_t[i][j];
			}
		}
	}
	else if(phasenum == 2){
		for(int i=2;i<4;i++){
			for(int j=0;j<2;j++){
				other_q[i][j] = (float)other_n[i][j]/other_t[i][j];
			}
		}
	}
}

void Left::change_t() {
	//qDebug() << "changet";
	for (int i = 0; i < 10; i++) {
		if (road_q[i] <= 1e-15) {
			road_t[i] = Tmin;
			continue;
		}
		if (road_q[i] < min_q[i]){
			int reduce = (int)((float)vehicle[i]/min_q[i]);
			road_t[i] = reduce >= Tmin ? reduce : Tmin;
		}
		else if(road_q[i] > max_q[i]){
			road_t[i] = (int)((float)vehicle[i]/max_q[i]);
		}
		else {
			//time not change
		}
	}
}

void Left::get_cycle() { //Select phase\ period type   ; calculation time
	/*bool jump=true;
	for (int i = 0; i < 8; i++) {
		if (i == 3 || i == 7) continue;
		if (road_q[i] < Q[i]) {
			jump = false;
			break;
		}
	}
	if (jump) return;*/

	float temp[3][3][4] = { 0 }; //Storage time
	float temq[3][3][4] = { 0 };//Storage efficiency

	//Time assignment
	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++) {
			for (int c = 0; c < 4; c++) {
				int cur = PH[a][b][c] - 1;
				if (cur < 0)
					continue;
				//No longer split the time of the repeating lane
				temp[a][b][c] = (float)road_t[cur];
				temq[a][b][c] = road_q[cur];
			}
		}
	}
	//Variance calculation
	//float d[3][3] = {0};//Storage variance
	//float D[3] = {0};//Variance and
	//for (int i = 0; i < 3; i++) {
	//	for (int j = 0; j < 3; j++) {
	//		/*
	//		if (PH[i][j][3] == 0) {
	//			d[i][j] = getvariance(temp[i][j],2);
	//		}
	//		else
	//			d[i][j] = getvariance(temp[i][j],4);
	//		*/
	//		d[i][j] = getvariance(temp[i][j],2);
	//	}
	//}
	//for (int i = 0; i < 3; i++) {
	//	D[i] = getsum(d[i], 3);
	//}
	//int minnum=0;
	//float mind = D[minnum];
	//for (int i = 0; i < 3; i++) {
	//	if (D[i] < mind) {
	//		minnum = i;
	//		mind = D[minnum];
	//	}
	//}
	//phasenum = minnum;//0 1 2

	//Traffic vehicle calculation
	float q[3][3] = { 0 };//Efficiency sum
	float n[3][3] = { 0 };//Storage quantity
	float N[3] = { 0 };//Quantity sum
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			q[i][j] = getsum(temq[i][j], 2);
			n[i][j] = getaverage(temp[i][j], 2)*q[i][j];
		}
	}
	for (int i = 0; i < 3; i++) {
		N[i] = getsum(n[i], 3);
	}
	int maxnum = -1;
	float maxn = N[maxnum];
	for (int i = 1; i < 3; i++) {
		if (N[i] > maxn) {
			maxnum = i;
			maxn = N[maxnum];
		}
	}
	phasenum = maxnum;//0 1 2

	//Calculating phase time
	float T_[3], C_;
	for (int i = 0; i < 3; i++) {
		T_[i] = getaverage(temp[phasenum][i], 2);

		T_[i] = T_[i] > Tmin ? T_[i] : Tmin;
		T_[i] = (int)(T_[i] / 5) * 5 + (((int)T_[i] % 5) < 3 ? 0 : 5);
	}
	C_ = getsum(T_, 3);
	while (C_ < Cmin || C_ > Cmax) {
		if (C_ < Cmin) {
			int tem = -1;
			float temq = -1;
			for (int i = 0; i < 3; i++) {
				if (q[phasenum][i] >= temq) {
					tem = i;
					temq = q[phasenum][i];
				}
			}
			T_[tem] += 5;
			q[phasenum][tem] = n[phasenum][tem] / T_[tem];
		}
		else if (C_ > Cmax) {
			//Choose the minimum efficiency
			int tem = -1;
			float temq = Q[0]*2;
			for (int i = 0; i < 3; i++) {
				if (q[phasenum][i]<temq && T_[i]>Tmin) {
					tem = i;
					temq = q[phasenum][i];
				}
			}
			//Choose the longest time
			int mint = 10;
			int temt = -1;
			for (int i = 0; i < 3; i++) {
				if (T_[i] > mint) {
					temt = i;
					mint = T_[i];
				}
			}
			//If it is low enough, reduce it.
			if (tem != -1) {
				T_[tem] -= 5;
				q[phasenum][tem] = n[phasenum][tem] / T_[tem];
			}
			else {
				T_[temt] -= 5;
				q[phasenum][temt] = n[phasenum][temt] / T_[temt];
			}
		}
		C_ = getsum(T_, 3);
	}

	for (int i = 0; i < 3; i++) {
		T[i] = (int)T_[i];
	}


	cycle = T[0] + T[1] + T[2];
	get_time();
}

void Left::next(int veh_num[10]){
	/*cout<<endl<<"time:"<<endl;
	for(int i=0;i<10;i++) cout<<road_t[i]<<" ";
	cout<<endl;
	for(int i=0;i<10;i++) cout<<all_road_t[i]<<" ";
	printf("\n%2d %2d %2d\n%2d\n",T[0],T[1],T[2],phasenum);*/

	/*for (int i = 0; i < 10; i++) {
		all_road_t[i] += road_t[i];
	}*/
	get_num(veh_num);
	/*cout<<"num:"<<endl;
	for(int i=0;i<10;i++) cout<<vehicle[i]<<" ";
	cout<<endl;
	for(int i=0;i<10;i++) cout<<road_t[i]<<" ";
	cout<<endl;
	for(int i=0;i<10;i++) cout<<road_q[i]<<" ";
	cout<<endl;
	*/
	change_t();
	get_cycle();
}

void Left::fixed_next(){
	for(int i=0;i<10;i++){
		all_road_t[i] += road_t[i];
	}
}

//For signal control; cur_t is the moment in the current cycle
void Left::judge(int cur_t,int vehnum[10],int num2, int num3, int num6, int num7, int num9, int num10, bool * is_green){
	for(int i=0;i<10;i++){
		for(int j=0;j<1;j++){
			if(cur_t<=end[i][j] && cur_t>=start[i][j]+3){
				is_green[i]=true;
			}
		}
	}
	/*if (num2 >= car_max) {
		is_green[1] = false;
	}
	if (num3 >= car_max) {
		is_green[2] = false;
	}
	if(num6 >=car_max){
		is_green[5]=false;
	}
	if(num7>=car_max){
		is_green[6]=false;
	}*/
	if (num9 >= car_max) {
		is_green[8] = false;
	}
	if (num10 >= car_max) {
		is_green[9] = false;
	}
	is_green[10] = is_green[8]?0:1;
	is_green[11] = is_green[9]?0:1;
	/*
	if(phasenum == 0){
		if(vehnum[8]>=car_max){
			is_green[8]=false;
		}
		if(vehnum[9]>=car_max){
			is_green[9]=false;
		}
	}
	else if(phasenum == 1){
		if(cur_t<=start[3][1]){//4车道
			other_n[0][0]=vehnum[3];
		}
		else{
			other_n[0][1]=vehnum[3]-other_n[0][0];
		}

		if(cur_t<=start[7][1]){//8车道
			other_n[1][0]=vehnum[7];
		}
		else{
			other_n[1][1]=vehnum[7]-other_n[1][0];
		}
	}
	else if(phasenum == 2){
		if(cur_t<=start[8][1]){//9车道
			other_n[2][0]=vehnum[8];
			if(other_n[2][0]>=car_max) is_green[8]=false;
		}
		else{
			other_n[2][1]=vehnum[8]-other_n[2][0];
			if(other_n[2][1]>=car_max) is_green[8]=false;
		}

		if(cur_t<=start[9][1]){//10车道
			other_n[3][0]=vehnum[9];
			if(other_n[3][0]>=car_max) is_green[9]=false;
		}
		else{
			other_n[3][1]=vehnum[9]-other_n[3][0];
			if(other_n[3][1]>=car_max) is_green[9]=false;
		}
	}
	is_green[10] = is_green[8]?0:1;
	is_green[11] = is_green[9]?0:1;
	*/
}

//Called in the last cycle, no need to calculate the next cycle timing
void Left::get_last(int cur_t){
	for(int i=0;i<10;i++){
		if(cur_t>start[i][0] && cur_t<=end[i][0]){
			all_road_t[i] += cur_t-start[i][0];
		}
		else if(cur_t>start[i][1] && cur_t<=end[i][1]){
			all_road_t[i] += cur_t-start[i][1]+end[i][0]-start[i][0];
		}
		else if(cur_t>end[i][0] && cur_t<=start[i][1]){
			all_road_t[i] += end[i][0]-start[i][0];
		}
	}
}