#include "head.h"
const Uint8 *keystate = SDL_GetKeyboardState(NULL);
void control_player(){
	SDL_Event event;
	int x=data_get("player","PosX");
	int y=data_get("player","PosY");
	int sx=data_get("player","PosX_shift");
	int sy=data_get("player","PosY_shift");
	if (keystate[SDL_SCANCODE_DOWN]&&y<150){
		if(data_get("map","building.pass",x,y+1)==0)sy+=data_get("player","speed");
		if(data_get("map","building.pass",x,y+1)==2)sy+=data_get("player","speed")-3;
	}
	if (keystate[SDL_SCANCODE_UP]&&y>50){
		if(data_get("map","building.pass",x,y-1)==0)sy-=data_get("player","speed");
		if(data_get("map","building.pass",x,y-1)==2)sy-=data_get("player","speed")-3;
	}
	if (keystate[SDL_SCANCODE_RIGHT]&&x<150){
		if(data_get("map","building.pass",x+1,y)==0)sx+=data_get("player","speed");
		if(data_get("map","building.pass",x+1,y)==2)sx+=data_get("player","speed")-3;
	}
	if (keystate[SDL_SCANCODE_LEFT]&&x>50){
		if(data_get("map","building.pass",x-1,y)==0)sx-=data_get("player","speed");
		if(data_get("map","building.pass",x-1,y)==2)sx-=data_get("player","speed")-3;
	}
	if (keystate[SDL_SCANCODE_DOWN]&&y<150)data_set("player","aim",0);
	if (keystate[SDL_SCANCODE_UP]&&y>50)data_set("player","aim",1);
	if (keystate[SDL_SCANCODE_RIGHT]&&x<150)data_set("player","aim",2);
	if (keystate[SDL_SCANCODE_LEFT]&&x>50)data_set("player","aim",3);
	int view=data_get("player","view");
	if (keystate[SDL_SCANCODE_KP_PLUS]) {
	if(view>8)view--;
	}
	if (keystate[SDL_SCANCODE_KP_MINUS]) {
		if(view<32)view++;
	}
	data_set("player","view",view);
	if(sx>40){	sx=-40;	x++;	}
	if(sx<-40){	sx=40;	x--;	}
	if(sy>40){	sy=-40;	y++;	}
	if(sy<-40){	sy=40;	y--;	}
	if(sx<0){		sx++;	}
	if(sy<0){		sy++;	}
	if(sx>0){		sx--;	}
	if(sy>0){		sy--;	}
	if(keystate[SDL_SCANCODE_C]) data_set("UI","show",true);
	if(keystate[SDL_SCANCODE_Z]){
		int px=x,py=y;
		if(data_get("player","aim")==0){py++;}
		if(data_get("player","aim")==1){py--;}
		if(data_get("player","aim")==2){px++;}
		if(data_get("player","aim")==3){px--;}
		if(data_get("UI","choose",0)==0&&sdata_get("map","building",px,py)=="air"){
			if(data_get("UI","choose",1)==1&&data_get("resource","VailableData")>=400){
				sdata_set("map","building.set_id","compiler",px,py);
				data_set("resource","VailableData",data_get("resource","VailableData")-400);
			}
			else if(data_get("UI","choose",1)==2&&data_get("resource","VailableData")>=400){
				sdata_set("map","building.set_id","folder",px,py);
				data_set("resource","VailableData",data_get("resource","VailableData")-400);	
			}
			else if(data_get("UI","choose",1)==3&&data_get("resource","VailableData")>=50){
				sdata_set("map","building.set_id","Data Bus",px,py);
				data_set("resource","VailableData",data_get("resource","VailableData")-50);	
			}
			else if(data_get("UI","choose",1)==4&&data_get("resource","VailableData")>=500){
				sdata_set("map","building.set_id","Antivirus",px,py);
				data_set("resource","VailableData",data_get("resource","VailableData")-500);	
			}
			else if(data_get("UI","choose",1)==5&&data_get("resource","VailableData")>=2000){
				sdata_set("map","building.set_id","firewall",px,py);
				data_set("resource","VailableData",data_get("resource","VailableData")-2000);	
			}
		}
		if(data_get("UI","choose",0)==1){
			if(data_get("UI","choose",1)==1){
				for(int i=0;i!=10;i++){
					if(px==data_get("spy","data",i,1)&&py==data_get("spy","data",i,2))data_set("spy","data",-1,i,0);
				}
			}
			else if(data_get("UI","choose",1)==2){
				sdata_set("map","building.set_id","air",px,py);	
			}
			else if(data_get("UI","choose",1)==4){
				if(sdata_get("map","building",px,py)=="hash weebs"){
					sdata_set("map","building.set_id","air",px,py);
					data_set("resource","UnvailableData",data_get("resource","UnvailableData")+200);
				}
				else if(data_get("map","building.age",px,py)==1000){
					data_set("map","building.age",500,px,py);
					data_set("resource","UnvailableData",data_get("resource","UnvailableData")+500);
				}
			}
		}
		if(data_get("UI","choose",0)==2&&sdata_get("map","building",px,py)=="air"){
			if(data_get("UI","choose",1)==1)sdata_set("map","building.set_id","hash weebs",px,py);
			if(data_get("UI","choose",1)==2)sdata_set("map","building.set_id","tree",px,py);
			if(data_get("UI","choose",1)==3)sdata_set("map","building.set_id","nested loop",px,py);
		}
	}
	data_set("player","PosX",x);
	data_set("player","PosY",y);
	data_set("player","PosX_shift",sx);
	data_set("player","PosY_shift",sy);
}


void control_UI(){
	const int UI_W=data_get("UI","UI_W");
	int UI_H[data_get("UI","UI_W")];
	for(int i=0;i!=data_get("UI","UI_W");i++){
		UI_H[i]=data_get("UI","UI_H",i);
	}
	
	SDL_Event event=main_event();
	if (event.type == SDL_KEYDOWN) {
		int UI_w=data_get("UI","choose",0);
		int UI_h=data_get("UI","choose",1);
		if(keystate[SDL_SCANCODE_X]||keystate[SDL_SCANCODE_Z])	data_set("UI","show",false);
		if(keystate[SDL_SCANCODE_RIGHT]&&UI_w<UI_W-1){UI_w++;UI_h=0;}
		if(keystate[SDL_SCANCODE_LEFT]&&UI_w>0){UI_w--;UI_h=0;}
		if(keystate[SDL_SCANCODE_UP]&&UI_h<UI_H[UI_w]-1)UI_h++;
		if(keystate[SDL_SCANCODE_DOWN]&&UI_h>0)UI_h--;
		data_set("UI","choose",UI_w,0);
		data_set("UI","choose",UI_h,1);
	}
}
void control_set(){
	SDL_Event event_set=main_event();
	if(keystate[SDL_SCANCODE_Q]&&event_set.type == SDL_KEYDOWN){
		if(data_get("UI","set")==0)data_set("UI","set",1);
		else if(data_get("UI","set")!=0)data_set("UI","set",0);
	}
	else if(event_set.type == SDL_KEYDOWN){
		if(keystate[SDL_SCANCODE_DOWN])
			if(data_get("UI","set")==1)data_set("UI","set",2);
			else if(data_get("UI","set")==2)data_set("UI","set",3);
		if(keystate[SDL_SCANCODE_UP])
			if(data_get("UI","set")==3)data_set("UI","set",2);
			else if(data_get("UI","set")==2)data_set("UI","set",1);
		if(keystate[SDL_SCANCODE_Z]){
			if(data_get("UI","set")==2)data_set("game","process",0);
			else if(data_get("UI","set")==3)data_set("game","process",-1);
			data_set("UI","set",0);
		}
		if(keystate[SDL_SCANCODE_X])
			data_set("UI","set",0);
	}
}

void control(){
	if(data_get("game","process")==1){
		if(data_get("UI","show")==0&&data_get("UI","set")==0)		control_player();
		else if(data_get("UI","show")==1&&data_get("UI","set")==0)	control_UI();
		control_set();
		spy_act();
	}
}
