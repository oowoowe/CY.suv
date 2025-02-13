#include "head.h"
SDL_Event event;
SDL_Event main_event(){
	return event;
}
int main(int argc,char *args[]){
	srand(time(NULL));	
	set();
	data_reset();
	while(data_get("game","process")!=-1){
		if(data_get("game","process")==0){
			data_reset();
		}
		else if(data_get("game","process")==2){
			if(event.type == SDL_KEYDOWN)data_set("game","process",3);
			Pic("other",4,0,0,1200,880);
		}
		else if(data_get("game","process")==3){
			if(event.type == SDL_KEYDOWN)data_set("game","process",1);
			Pic("other",7,0,0,1200,880);
		}
		if(event.type==SDL_QUIT)data_set("game","process",-1);
		SDL_PollEvent(&event);
		control();
		show();
		renewPic();
		data_renew();
	}
	set_end();
}
