#ifndef head_H
#define head_H

#include <cstring>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <time.h>
using namespace std;

//set
void set();
void set_end();
void Pic(string pic_head,int pic_number,int posX,int posY,int sizX,int sizY);
void renewPic();
int set_const_get(string const_name);
void text(string words,int x,int y,int sizeX,int sizeY,int R,int G,int B);

//data
void data_reset();
int data_get(string data_head,string data_name,int X=0,int Y=0);
string sdata_get(string data_head,string data_name,int X,int Y=0);
void data_set(string data_head,string data_name,int data,int X=0,int Y=0);
void sdata_set(string data_head,string data_name,string data,int X=0,int Y=0);
void data_renew();

//control
void control();

//show
void show();

//main
SDL_Event main_event();
//spy
void spy_sum(int x,int y);
void spy_act();
void spy_show();
#endif	
