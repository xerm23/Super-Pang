#include "Balloon.h"
#include <WinBase.h>
#include <iostream>
#include <math.h>
using namespace std;
#include <random>

//random generator za x koordinatu prvih kugli
std::random_device rd; 
std::mt19937 eng(rd()); 
std::uniform_int_distribution<> distr(0,3); 

//random za zvuk
std::random_device rd2; 
std::mt19937 eng2(rd2()); 
std::uniform_int_distribution<> distr2(0,1); 



Balloon::Balloon(int size, int id, int xvel){
	ballsize=size;
	if(ballsize==1){
	ballpixels = ReadBitmap("Ball/B1.bmp", &ballinfo);
	ballmaskpixels = ReadBitmap("Ball/B1mask.bmp", &ballmaskinfo);
	maxvelocityY=84.2801;
	radius=64;
	}
	if(ballsize==2){
	ballpixels = ReadBitmap("Ball/B2.bmp", &ballinfo);
	ballmaskpixels = ReadBitmap("Ball/B2mask.bmp", &ballmaskinfo);
	maxvelocityY=68.6;
	radius=48;
	}
	if(ballsize==3){
	ballpixels = ReadBitmap("Ball/B3.bmp", &ballinfo);
	ballmaskpixels = ReadBitmap("Ball/B3mask.bmp", &ballmaskinfo);
	maxvelocityY=59.78;
	radius=32;
	}
	if(ballsize==4){
	ballpixels = ReadBitmap("Ball/B4.bmp", &ballinfo);
	ballmaskpixels = ReadBitmap("Ball/B4mask.bmp", &ballmaskinfo);
	maxvelocityY=52.92;
	radius=16;
	}
	location[0] = SCREENMAXX/(size+distr(eng)) -64;
    location[1] = SCREENMAXY-radius*2;
    limitY=SCREENMAXY/(size+1);
    velocityX = xvel;
    velocityY = 0;
    acc = 9.8;
    dt = 0.1;
    ID=id;
}



Balloon::~Balloon()
{	
}

Balloon::Balloon(int id){
	ID = id;
	ballsize=5;
	ballpixels = ReadBitmap("Booster/Freeze.bmp", &ballinfo);
	ballmaskpixels = ReadBitmap("Booster/FreezeM.bmp", &ballmaskinfo);
	maxvelocityY=70.252;
	radius=48;
	location[0] = SCREENMAXX/(distr(eng)+1) -64;
    location[1] = SCREENMAXY-radius*2;
    velocityX = 20;
    velocityY = 0;
    limitY=SCREENMAXY/2;
    acc = 9.8;
    dt = 0.1;
}

void Balloon::SetPixels(){	
}


bool Balloon::ArrowCheck(int x, int y){
	if(location[0]>=x-radius && location[0]<=x && location[1]<=y){
		switch(distr2(eng2)){
			case 0:
				PlaySound("Sounds/balloonhit.wav",NULL, SND_ASYNC);
				break;
			case 1:
				PlaySound("Sounds/balloonhit2.wav",NULL, SND_ASYNC);
				break;
		}
		return true;
	}
	return false;
}

bool Balloon::playerHit(Player *p){
	if(location[0]>=p->location[0]-radius && location[0]<=p->location[0]+18 && location[1]<=p->location[1]+radius){
		return true;
	}
	return false;
}

void Balloon::Draw(){	
	velocityY = velocityY - acc*dt;
	if(velocityY<=maxvelocityY*(-1)) velocityY=maxvelocityY*(-1);
	if(velocityY>=maxvelocityY) velocityY=maxvelocityY;

	location[0] = location[0] - (velocityX*dt);
	location[1] = location[1] + (velocityY*dt) + 0.1*acc*(dt*dt);

	if(location[0]<0) velocityX*=-1;
	if(location[0]>1080-radius) {
		velocityX*=-1;
	}
	if(location[1]<=0) {
		if(ballsize==5){
			ballpixels = ReadBitmap("Booster/Kill.bmp", &ballinfo);
			ballmaskpixels = ReadBitmap("Booster/KillM.bmp", &ballmaskinfo);
			ballsize=6;
		}
		else if(ballsize==6){
			ballpixels = ReadBitmap("Booster/Freeze.bmp", &ballinfo);
			ballmaskpixels = ReadBitmap("Booster/FreezeM.bmp", &ballmaskinfo);
			ballsize=5;			
		}
		location[1]=1;
		velocityY=maxvelocityY;
	}
	if(location[1]>limitY && velocityY>0){
		velocityY*=-1;
	}
	glEnable(GL_COLOR_LOGIC_OP);
	glLogicOp(GL_AND_INVERTED);
	glRasterPos2i(location[0],location[1]);
	glDrawPixels(ballmaskinfo->bmiHeader.biWidth, ballmaskinfo->bmiHeader.biHeight,GL_BGR_EXT, GL_UNSIGNED_BYTE, ballmaskpixels);
	glLogicOp(GL_OR);
	glDrawPixels(ballinfo->bmiHeader.biWidth, ballinfo->bmiHeader.biHeight,GL_BGR_EXT, GL_UNSIGNED_BYTE, ballpixels);
    glDisable(GL_COLOR_LOGIC_OP);
}


void Balloon::DrawFreeze(){
	glEnable(GL_COLOR_LOGIC_OP);
	glLogicOp(GL_AND_INVERTED);
	glRasterPos2i(location[0],location[1]);
	glDrawPixels(ballmaskinfo->bmiHeader.biWidth, ballmaskinfo->bmiHeader.biHeight,GL_BGR_EXT, GL_UNSIGNED_BYTE, ballmaskpixels);
	glLogicOp(GL_OR);
	glDrawPixels(ballinfo->bmiHeader.biWidth, ballinfo->bmiHeader.biHeight,GL_BGR_EXT, GL_UNSIGNED_BYTE, ballpixels);
    glDisable(GL_COLOR_LOGIC_OP);
	
}
void Balloon::Update(GLfloat x, GLfloat y) 
{
}