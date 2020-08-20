#include "Ordinary.h"

//****************************************************
void Ordinary::init(){//Called every time update cycle 
	min_cycle=1000;
	while(l[0].size()>0){
		l[0].pop_back();
	}
	while(l[1].size()>0){
		l[1].pop_back();
	}
	time1=0;
	time2=0;
	for(int i=0;i<8;i++){
		state[i]=0;
		for(int j=0;j<8;j++){
			se[i][j]=0;
		}
	} 
}

void Ordinary::insert(){
/*
	cout<<"queue:";
	for(deque<int>::iterator item=l[0].begin();item!=l[0].end();++item){
		cout<<*item;
	}
	cout<<"||";
	for(deque<int>::iterator item=l[1].begin();item!=l[1].end();++item){
		cout<<*item;
	}
	cout<<endl;
*/
	int x=time1>=time2?0:1;//Longer queue 
	int y=(x+1)%2;//Shorter queue
	//Added finished
	if(l[0].size()+l[1].size()==8){ 
		cycle = time1>=time2?time1:time2;
		if(cycle<min_cycle){ //When getting better
			min_cycle=cycle;
			if(time1!=time2){//Fill the end of the team
				int r1=l[x].back(); //the last lane
				int r2=l[y].back(); //Lane that needs to be filled
				if(isin(r2,r1)){
					tem_e[r2]=tem_e[r1];
				} 
			}
			for(int i=0;i<8;i++){
				start[i]=tem_s[i];
				end[i]=tem_e[i];
			}
		} 
		return; 
	}
	
	//not finished
	if(time1==time2){//Team tail flush
		for(int i=0;i<8;i++){
			if(state[i]==0){
				l[0].push_back(i); //insert L1 
			 	state[i] = 1; 
			 	tem_s[i]=time1;
				tem_e[i]=time1+road_t[i];
				time1=tem_e[i];
				
				insert();//Recursive 
				
				//restore
				l[0].pop_back(); 
				state[i] = 0;
				time1=tem_s[i];
			}
		}
		return; 
	}
	
	//The tail of the team is not flush
	int cur=l[x].back(); //last line
	bool none=true; //Is there no compatible lane to add? 
	for(int i=0;i<3;i++){
		int next = combination[cur][i] - 1;
		if(state[next] == 0){
			none=false;
			state[next] = 1; 
			tem_s[next]=tem_e[l[y].back()];
			tem_e[next]=tem_s[next]+road_t[next];
			l[y].push_back(next); 
			if(y==0) time1=tem_e[next];
			else time2=tem_e[next];
			
			insert();//Recursive 
			
			//restore
			l[y].pop_back(); 
			state[next] = 0;
			if(y==0) time1=tem_s[next];
			else time2=tem_s[next];	
		}
	} 
	if(none){ //If there is no compatible lane, the queue is processed by the tail of the team flush. 
		int r1=l[x].back(); //last line
		int r2=l[y].back(); //Lane that needs to be filled
		if(isin(r2,r1)){
			tem_e[r2]=tem_e[r1];
		} 
		time1= tem_e[r1];
		time2= tem_e[r1];
		for(int i=0;i<8;i++){
			if(state[i]==0){
				l[0].push_back(i); //insertL1 
			 	state[i] = 1; 
			 	tem_s[i]=time1;
				tem_e[i]=time1+road_t[i];
				time1=tem_e[i];
				
				insert();//Recursive
				
				//restore 
				l[0].pop_back(); 
				state[i] = 0;
				time1=tem_s[i];
			}
		}
		return;
	}
}

void Ordinary::get_list(){
	init();
	for(int i=0;i<8;i++){//Queue head combination using memory search
		l[0].push_back(i);
		state[i]=1;
		tem_s[i]=0;tem_e[i]=road_t[i];
		time1=tem_e[i];
		
		for(int j=0;j<3;j++){
			int cur = combination[i][j]-1; 
			if(se[i][cur] || se[cur][i]){
				continue;
			}
			se[i][cur]=1;se[cur][i]=1;
			l[1].push_back(cur); 
			state[cur]=1;
			tem_s[cur]=0;tem_e[cur]=road_t[cur];
			time2=tem_e[cur];
			
			insert();//Search and insert queue
			
			l[1].pop_back();
			state[cur]=0;
			time2=0;
		}
		
		l[0].pop_back();
		state[i]=0;
		time1=0;
	}
}

void Ordinary::get_cycle(){
	get_list();
	cycle=min_cycle;
	queue<int> max_r;
	while(cycle>Tmax){
		//Choose the minimum efficiency that is not out of range
		int temr = -1;
		float temq = 2.0;
		for(int i=0;i<8;i++){
			if(road_q[i]<=temq && road_q[i]<max_q[i] && road_t[i]>S_Tmin){
				temr = i;
				temq = road_q[i];
			}
		}

		//Choose the longest and least efficient time
		int tem[8];
		for(int i=0;i<8;i++){
			tem[i]=road_t[i];
		}
		sort(tem,tem+8);
		for(int i=0;i<8;i++){
			if(road_t[i]==tem[7]) max_r.push(i);
		}
		int min_r=max_r.front();
		max_r.pop();
		while(max_r.size()>0){
			int road=max_r.front();
			max_r.pop();
			if(road_q[road]<road_q[min_r]) min_r=road;
		}

		//If it is low enough, reduce it.
		if(temr!=-1){
			min_r = temr;
		}

		road_t[min_r]-=5;
		road_q[min_r] = (float)vehicle[min_r] / road_t[min_r];
		//Regain queue
		get_list();
		cycle=min_cycle;
	}
	for(int i=0;i<8;i++){
		road_t[i] = end[i] - start[i];
		all_road_t[i] += road_t[i];
	}

}
//***************************************************************

Ordinary::Ordinary(void)
{
	get_range(); //Gain efficiency range
	//init queue
	start[0] = 0, start[1] = 0, start[2] = 45, start[3] = 45;
	start[4] = 15, start[5] = 30, start[6] = 65, start[7] = 75;
	for (int i = 0; i < 8; i++) {
		//init time
		if (i % 2 == 0)
			road_t[i] = 30;
		else
			road_t[i] = 15;
		end[i] = start[i] + road_t[i];//end time
		
		all_road_t[i] = 0;
	}
	cycle = 90;
}

Ordinary::~Ordinary(void)
{
}

inline bool Ordinary::isin(int i,int j){
	for (int x=0;x<3;x++){
		if(combination[j][x]==i+1){
			return true;
		}
	}
	return false;
}

inline void Ordinary::get_q(){
	for(int i=0;i<8;i++){
		road_q[i] = (float)vehicle[i] / road_t[i];
	}
}

void Ordinary::get_num(int veh_num[8]){
	for(int i=0;i<8;i++){
		vehicle[i] = veh_num[i];
	}
	get_q();
}

void Ordinary::change_t() {
	//Control efficiency is within the appropriate range
		for (int i = 0; i < 8; i++){
		if (road_q[i] < min_q[i]){
			int reduce = (int)((float)vehicle[i]/min_q[i]);
			road_t[i] = reduce >= S_Tmin ? reduce : S_Tmin;
		}
		else if(road_q[i] > max_q[i]){
			int increase = (int)((float)vehicle[i]/max_q[i]);
			road_t[i] = increase <= S_Tmax ? increase : S_Tmax;
		}
		else {
			//not change
		}
	}

	//Adjustment time is a multiple of 5
	for (int i = 0; i < 8; i++){
		int quotient = road_t[i]/5;
		int remainder = road_t[i]%5;
		road_t[i] = quotient*5 + (remainder<3 ? 0:5);
	}
}

//For signal control cur_t is the moment in the current cycle
bool* Ordinary::judge(int cur_t){
	for(int i=0;i<8;i++){
		if(cur_t<end[i] && cur_t>=start[i]+3){
			is_green[i]=true;
		}
		else {
			is_green[i]=false;
		}
	}
	return is_green;
}

void Ordinary::fixed_next(){
	for(int i=0;i<8;i++){
		all_road_t[i] += road_t[i];
	}
}

//Get the passing vehicle Calculate the next cycle Whether the detection cycle time meets the conditions
void Ordinary::next(int veh_num[8]){
	/*
	cout<<endl<<"time:"<<endl;
	for(int i=0;i<8;i++) cout<<road_t[i]<<" ";
	cout<<endl;
	*/
	get_num(veh_num);
	/*
	cout<<"num:"<<endl;
	for(int i=0;i<8;i++) cout<<vehicle[i]<<" ";
	cout<<endl;
	for(int i=0;i<8;i++) cout<<road_q[i]<<" ";
	cout<<endl;
	*/
	change_t();
	
	get_q();
	
	get_cycle();
}

//Called in the last cycle, no need to calculate the next cycle timing
void Ordinary::get_last(int cur_t){
	for(int i=0;i<8;i++){
		if(cur_t<start[i]){
			//
		}
		else if(cur_t<=end[i]){
			all_road_t[i] += cur_t-start[i];
		}
		else {
			all_road_t[i] += road_t[i];
		}
	}
}
