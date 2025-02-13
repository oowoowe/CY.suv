#include "head.h"

//建築資料類別 
class building {
	public:
		int num_id;
		string id;
		bool set;
		int age;
		int hp;
		int pass;
		int net;
		int wave;
		building(int num_ID=-1){
			id="";
			num_id=num_ID;
			set=true;
			hp=0;
			wave=0;
		}
		void set_id(string Id=""){
			id=Id;
			set=false;
		}
		void set_data(int ID,int Hp,int Pass=0,int Age=-1,int Net=0,int Wave=0){
			num_id=ID;
			hp=Hp;
			age=Age;
			set=true;
			pass=Pass;
			net=Net;
			wave=Wave;
		}
};
//地圖資料 
int map_ground[200][200];
building map_building[200][200];
//玩家資料
int player_view;
int player_PosX,player_PosY;
int player_PosX_shift,player_PosY_shift;
int player_speed;
int player_aim;
//UI資料
bool UI_show;
int UI_choose[2];
const int UI_W=3;
const int UI_H[UI_W]={6,5,4};
int UI_holding;
int UI_set;
//物件說明資料
string Data_building[8]={"a","b","c","d","e","f","g","h"};
string Data_UI[5][6]=
{	{	"build some thing.",
		"a building that can make data useful.",
		"a building where you can get data.",
		"a building which to connect others.",
		"a building which to protect your base.",
		"just a wall that you can build."},
	{	"do some thing.",
		"make damage to any thing that's infront of you.",
		"erase the build or whatever in your sight.",
		"check what is infront of you.",
		"harvest some plant to get data.","f"},
	{	"grow some thing.",
		"a weeb that can be harvest.",
		"a tree that can be harvest.",
		"a nested loop structure taht can be harvest.","e","f"},
	{"a","b","c","d","e","f"},
	{"a","b","c","d","e","f"}};
string Data_act[5][6]=
{	{"building","compiler","folder","Data Bus","Antivirus","firewall"},
	{"   act   ","attack","break","check","harvest"},
	{"cultivate","hash weebs","  tree  ","nested loop","e"},
	{"a","b","c","d","e"},
	{"a","b","c","d","e"}};
//遊戲進程
int game_process; 
//資源
int resource_VailableData; 
int resource_UnvailableData;
//敵人
int spy_data[10][8]; 
//初始設定
void data_reset(){
	UI_set=0;
	player_view=8;
	player_PosX=100;
	player_PosY=100;
	player_PosX_shift=0;
	player_PosY_shift=0;
	player_speed=5;
	player_aim=0;
	UI_show=0;
	UI_holding=0;
	game_process=2;
	resource_VailableData=5000;
	resource_UnvailableData=0;
	for(int i=0;i!=200;i++){
		if(i<2)	UI_choose[i]=0;
		for(int k=0;k!=200;k++){
			if(i>=50&&i<=150&&k>=50&&k<=150){
				map_ground[i][k]=0;	
			}
			else map_ground[i][k]=2;
			map_building[i][k].set_id("air");
			}
		}
	for(int i=0;i!=8;i++){
		for(int k=0;k!=10;k++){
			spy_data[k][i]=0;
		}
	} 
	for(int i=50;i!=150;i++){
		for(int k=50;k!=150;k++){
			int x=rand()%20+1;
			if(x==1&&map_ground[i][k]==0){
				map_building[i][k].set_id("hash weebs.");
			}
		}
	}
	for(int i=0;i!=20;i++){
		int x=rand()%100+50;
		int y=rand()%100+50;
		for(int k=0;k!=50;k++){
			map_building[x][y].set_id("nested loop.");
			int c=rand()%4+1;
			if(c==1)x++;
			if(c==2)x--;
			if(c==3)y++;
			if(c==4)y--;
		}
	}
	for(int i=0;i!=50;i++){
		int x=rand()%100+50;
		int y=rand()%100+50;
		map_building[x][y].set_id("tree.");
		
	}
	for(int i=0;i!=3;i++){
		int x=rand()%100+50;
		int y=rand()%100+50;
		for(int k=0;k!=500;k++){
			map_building[x][y].set_id("firewall");
			int c=rand()%4+1;
			if(c==1)x++;
			if(c==2)x--;
			if(c==3)y++;
			if(c==4)y--;
		}
	}
	for(int i=0;i!=2;i++){
		int x=rand()%51+75;
		int y=(i*2)*25+75;
		for(int k=x-3;k!=x+4;k++){
			for(int j=y-3;j!=y+4;j++){
				map_ground[k][j]=1;
				map_building[k][j].set_id("air");
				if(k==x||j==y||j-y==k-x||j-y==-k+x){
					map_building[k][j].set_id("net");
				}
			}
		}
		map_building[x][y].set_id("hole");
	}
	
	map_building[100][100].set_id("air");
}
//提取資料
int data_get(string data_head,string data_name,int X,int Y){
	if		(data_head=="map"){
		if		(data_name=="ground")	return map_ground[X][Y];
		else if	(data_name=="building.id")	return map_building[X][Y].num_id;
		else if	(data_name=="building.pass")	return map_building[X][Y].pass;
		else if	(data_name=="building.age")	return map_building[X][Y].age;
		else if	(data_name=="building.wave")	return map_building[X][Y].wave;
	}
	else if	(data_head=="player"){
		if		(data_name=="PosX")			return player_PosX;
		else if	(data_name=="PosY")			return player_PosY;
		else if	(data_name=="PosX_shift")	return player_PosX_shift;
		else if	(data_name=="PosY_shift")	return player_PosY_shift;
		else if	(data_name=="speed")		return player_speed;
		else if	(data_name=="view")			return player_view;
		else if	(data_name=="aim")			return player_aim;
	}
	else if	(data_head=="UI"){
		if		(data_name=="show")		return UI_show;
		else if	(data_name=="choose")	return UI_choose[X];
		else if	(data_name=="UI_W")	return UI_W;
		else if	(data_name=="UI_H")	return UI_H[X];
		else if	(data_name=="holding")	return UI_holding;
		else if	(data_name=="set")	return UI_set;
	}
	else if	(data_head=="game"){
		if		(data_name=="process")		return game_process;
	}
	else if	(data_head=="resource"){
		if		(data_name=="VailableData")		return resource_VailableData;
		else if		(data_name=="UnvailableData")		return resource_UnvailableData;
	}
	else if	(data_head=="spy"){
		if		(data_name=="data")		return spy_data[X][Y];
	}
	cout<<"data_get,no data found "<<data_head<<data_name<<endl;
}

string sdata_get(string data_head,string data_name,int X,int Y){
	if		(data_head=="Data"){
		if		(data_name=="building")		return Data_building[X];
		else if	(data_name=="UI")			return Data_UI[X][Y];
		else if	(data_name=="act")			return Data_act[X][Y];
	}
	else if		(data_head=="map"){
		if		(data_name=="building") return map_building[X][Y].id;
	}
	cout<<"sdata_get,no data found"<<data_head<<data_name<<endl;
}

//變更資料
void data_set(string data_head,string data_name,int data,int X,int Y){
	if		(data_head=="map"){
		if		(data_name=="ground")	map_ground[X][Y]=data;
		else if		(data_name=="building.age")	map_building[X][Y].age=data;
	}
	else if	(data_head=="player"){
		if		(data_name=="PosX")			player_PosX=data;
		else if	(data_name=="PosY")			player_PosY=data;
		else if	(data_name=="PosX_shift")	player_PosX_shift=data;
		else if	(data_name=="PosY_shift")	player_PosY_shift=data;
		else if	(data_name=="speed")		player_speed=data;
		else if	(data_name=="view")			player_view=data;
		else if	(data_name=="aim")			player_aim=data;
	}
	else if	(data_head=="UI"){
		if		(data_name=="show")		UI_show=data;
		else if	(data_name=="choose")	UI_choose[X]=data;
		else if	(data_name=="holding")	UI_holding=data;
		else if	(data_name=="set")		UI_set=data;
	}
	else if	(data_head=="game"){
		if		(data_name=="process")	game_process=data;
	}
	else if	(data_head=="resource"){
		if			(data_name=="VailableData")			resource_VailableData=data;
		else if		(data_name=="UnvailableData")		resource_UnvailableData=data;
	}
	else if	(data_head=="spy"){
		if		(data_name=="data")		spy_data[X][Y]=data;
	}
	else cout<<"data_set,no data found"<<data_head<<data_name<<endl;
}

void sdata_set(string data_head,string data_name,string data,int X,int Y){
	if(data_head=="map"){
		if	(data_name=="building.set_id")	map_building[X][Y].set_id(data);
	}
	else cout<<"sdata_set,no data found"<<data_head<<data_name<<endl;
}
//更新資料
void data_renew(){
	int p=0;
	for(int i=50;i!=150;i++){
		for(int k=50;k!=150;k++){
			map_building[i][k].net==0;
			if(map_building[i][k].id=="compiler"||map_building[i][k].id=="folder"||map_building[i][k].id=="Data Bus"||map_building[i][k].id=="Antivirus"){
				if(map_building[i-1][k].net!=0)map_building[i][k].net=map_building[i-1][k].net;
				else if(map_building[i][k-1].net!=0)map_building[i][k].net=map_building[i][k-1].net;
				else {map_building[i][k].net=p;p++;}
			}
			if(map_building[i][k].id=="Antivirus"){
				map_building[i][k].num_id=23;map_building[i][k].wave-=1;
			}
			if(map_building[i][k].id=="firewall"&&map_building[i][k+1].id=="firewall"){
				map_building[i][k].num_id=4;
			}
			if(map_building[i][k].id=="firewall"&&map_building[i][k+1].id!="firewall"){
				map_building[i][k].num_id=28;
			}
		}
	}
	for(int i=50;i!=150;i++){
		for(int k=50;k!=150;k++){
			//依id設置初始數據 
			if(map_building[i][k].set==false){
				if		(map_building[i][k].id=="air")	map_building[i][k].set_data(-1,0,0,-1);
				if		(map_building[i][k].id=="compiler")	map_building[i][k].set_data(0,100,1,-1);
				if		(map_building[i][k].id=="folder")	map_building[i][k].set_data(1,100,1,-1);
				if		(map_building[i][k].id=="Data Bus")	map_building[i][k].set_data(2,50,0,-1);
				if		(map_building[i][k].id=="Antivirus")	map_building[i][k].set_data(3,300,1,-1);
				if		(map_building[i][k].id=="firewall")	map_building[i][k].set_data(4,2000,1,-1);
				if		(map_building[i][k].id=="hash weebs")	map_building[i][k].set_data(5,20,0,0);
				if		(map_building[i][k].id=="tree")		map_building[i][k].set_data(6,30,1,0);
				if		(map_building[i][k].id=="nested loop")	map_building[i][k].set_data(7,30,1,0);
				if		(map_building[i][k].id=="net")		map_building[i][k].set_data(29,30,2);
				if		(map_building[i][k].id=="hole")		map_building[i][k].set_data(30,2000,1);
				
				if		(map_building[i][k].id=="hash weebs."){
					map_building[i][k].set_data(5,20,0,1000);
					map_building[i][k].id="hash weebs";
				}	
				if		(map_building[i][k].id=="tree."){
					map_building[i][k].set_data(6,30,1,1000);
					map_building[i][k].id="tree";
				}
				if		(map_building[i][k].id=="nested loop."){
					map_building[i][k].set_data(7,30,1,1000);
					map_building[i][k].id="nested loop";
				}
			}
			if(map_building[i][k].id=="hole"&&5>player_PosX-i&&-5<player_PosX-i&&5>player_PosY-k&&-5<player_PosY-k)spy_sum(i,k);
			if(map_building[i][k].id=="Data Bus"){
					int j=0;
					if(map_building[i][k-1].id=="Data Bus"||map_building[i][k-1].id=="compiler"||map_building[i][k-1].id=="folder"||map_building[i][k-1].id=="Antivirus")j=j+1;
					if(map_building[i][k+1].id=="Data Bus"||map_building[i][k+1].id=="compiler"||map_building[i][k+1].id=="folder"||map_building[i][k+1].id=="Antivirus")j=j+2;
					if(map_building[i-1][k].id=="Data Bus"||map_building[i-1][k].id=="compiler"||map_building[i-1][k].id=="folder"||map_building[i-1][k].id=="Antivirus")j=j+4;
					if(map_building[i+1][k].id=="Data Bus"||map_building[i+1][k].id=="compiler"||map_building[i+1][k].id=="folder"||map_building[i+1][k].id=="Antivirus")j=j+8;
					if(j==0)map_building[i][k].num_id=2;
					else map_building[i][k].num_id=j+7;
			}
			if		(map_building[i][k].age>=0&&map_building[i][k].age<1000)	map_building[i][k].age++;	
			if(map_building[i][k].id=="nested loop"||map_building[i][k].id=="tree"||map_building[i][k].id=="hash weebs"){
				if(map_building[i][k].age<500&&map_building[i][k].age>=0){
					map_building[i][k].num_id=26;
					map_building[i][k].pass=0;
				}
				else if(map_building[i][k].age>=0&&map_building[i][k].age<1000){
					if(map_building[i][k].id=="nested loop"){
						map_building[i][k].pass=1;
						map_building[i][k].num_id=25;
					}
					else if(map_building[i][k].id=="tree"){
						map_building[i][k].pass=1;
						map_building[i][k].num_id=24;
					}
				}
				else if(map_building[i][k].age>=0&&map_building[i][k].age==1000){
					if(map_building[i][k].id=="nested loop")map_building[i][k].num_id=7;
					if(map_building[i][k].id=="tree")map_building[i][k].num_id=6;
					if(map_building[i][k].id=="hash weebs")map_building[i][k].num_id=5;
				}
			}
		}
	}
	for(int i=149;i!=49;i--){
		for(int k=149;k!=49;k--){
			if(map_building[i][k].id=="compiler"||map_building[i][k].id=="folder"||map_building[i][k].id=="Data Bus"||map_building[i][k].id=="Antivirus"){
				if(map_building[i+1][k].net!=0)map_building[i][k].net=map_building[i+1][k].net;
				if(map_building[i][k+1].net!=0)map_building[i][k].net=map_building[i][k+1].net;
			}
		}
	}
	bool m;
	for(int i=1;i!=50;i++){
		m=0;
		for(int k=50;k!=151;k++){
			for(int l=50;l!=150;l++){
				if(map_building[k][l].net==i&&map_building[k][l].id=="folder"){
					m=1;
				}
			}
		}
		for(int k=50;k!=151;k++){
			for(int l=50;l!=151;l++){
				if(map_building[k][l].net==i&&map_building[k][l].id=="compiler"&&m&&resource_UnvailableData>0){
					resource_UnvailableData--;
					resource_VailableData=resource_VailableData+5;
				}
				if(map_building[k][l].id=="Antivirus"){
					if(map_building[k][l].net==i&&resource_VailableData>0&&m){
						resource_VailableData--;
						map_building[k][l].num_id=3;
						if(map_building[k][l].wave<60)map_building[k][l].wave+=2;
						else map_building[k][l].wave=0;
						for(int j=0;j!=10;j++){
							int x=spy_data[j][1]-k,y=spy_data[j][2]-l;
							if(x<2&&x>-2&&y<2&&y>-2)spy_data[j][0]=-1;
						}
					}
				}	
			}
		}
	}
	if(rand()%500==0){
		int a=rand()%100+50;
		int b=rand()%100+50;
		int c=rand()%3;
		if(c==0&&map_building[a][b].id=="air")map_building[a][b].set_id("hash weebs");
		if(c==1&&map_building[a][b].id=="air")map_building[a][b].set_id("tree");
		if(c==2&&map_building[a][b].id=="air")map_building[a][b].set_id("nested loop");
	}
} 
