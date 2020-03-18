#include "Hexa.h"
#include <WinBase.h>
#include <iostream>
#include <math.h>
using namespace std;
#include <random>

//random generator za x koordinatu prvih kugli
std::random_device rd23; 
std::mt19937 eng23(rd23()); 
std::uniform_int_distribution<> distr23(0,2); 


Hexa::Hexa(int size, int id, int xvel){
	hexasize=size;
	if(hexasize==1){
	hexapixels = ReadBitmap("Hexa/S1/hexa1.bmp", &hexainfo);
	hexamaskpixels = ReadBitmap("Hexa/S1/hexa1M.bmp", &hexamaskinfo);
	radius=48;
	}
	if(hexasize==2){
	hexapixels = ReadBitmap("Hexa/S2/hexa1.bmp", &hexainfo);
	hexamaskpixels = ReadBitmap("Hexa/S2/hexa1M.bmp", &hexamaskinfo);
	radius=32;
	}
	if(hexasize==3){
	hexapixels = ReadBitmap("Hexa/S3/hexa1.bmp", &hexainfo);
	hexamaskpixels = ReadBitmap("Hexa/S3/hexa1M.bmp", &hexamaskinfo);
	radius=20;
	}
	ugao=45.;
	speedX= cos(ugao * PI / 180);
	speedX= abs(speedX);
	speedX*=xvel;
	speedY= sin(ugao * PI / 180);
	speedY= abs(speedY);
	location[0] = SCREENMAXX/(size+distr23(eng23)) -64;
    location[1] = SCREENMAXY-radius*2;
    ID=id;
	timer=0;
}

/*
	GLubyte *hexapixels;			
	BITMAPINFO *hexainfo;	
	GLubyte *hexahexamaskpixels;			
	BITMAPINFO *hexamaskinfo;	
	*/
void Hexa::Rotate(){
	if(hexasize==1){
		if(timer>=0&&timer<5){
			hexapixels = ReadBitmap("Hexa/S1/hexa1.bmp", &hexainfo);
			hexamaskpixels = ReadBitmap("Hexa/S1/hexa1M.bmp", &hexamaskinfo);
			timer++;
		}
		if(timer>=5&&timer<10){
			hexapixels = ReadBitmap("Hexa/S1/hexa2.bmp", &hexainfo);
			hexamaskpixels = ReadBitmap("Hexa/S1/hexa2M.bmp", &hexamaskinfo);
			timer++;
		}
		if(timer>=10&&timer<15){
			hexapixels = ReadBitmap("Hexa/S1/hexa3.bmp", &hexainfo);
			hexamaskpixels = ReadBitmap("Hexa/S1/hexa3M.bmp", &hexamaskinfo);
			timer++;
		}
	}
	else if(hexasize==2){
		if(timer>=0&&timer<5){
			hexapixels = ReadBitmap("Hexa/S2/hexa1.bmp", &hexainfo);
			hexamaskpixels = ReadBitmap("Hexa/S2/hexa1M.bmp", &hexamaskinfo);
			timer++;
		}
		if(timer>=5&&timer<10){
			hexapixels = ReadBitmap("Hexa/S2/hexa2.bmp", &hexainfo);
			hexamaskpixels = ReadBitmap("Hexa/S2/hexa2M.bmp", &hexamaskinfo);
			timer++;
		}
		if(timer>=10&&timer<15){
			hexapixels = ReadBitmap("Hexa/S2/hexa3.bmp", &hexainfo);
			hexamaskpixels = ReadBitmap("Hexa/S2/hexa3M.bmp", &hexamaskinfo);
			timer++;
		}
	}
	else{
		if(timer>=0&&timer<5){
			hexapixels = ReadBitmap("Hexa/S3/hexa1.bmp", &hexainfo);
			hexamaskpixels = ReadBitmap("Hexa/S3/hexa1M.bmp", &hexamaskinfo);
			timer++;
		}
		if(timer>=5&&timer<10){
			hexapixels = ReadBitmap("Hexa/S3/hexa2.bmp", &hexainfo);
			hexamaskpixels = ReadBitmap("Hexa/S3/hexa2M.bmp", &hexamaskinfo);
			timer++;
		}
		if(timer>=10&&timer<15){
			hexapixels = ReadBitmap("Hexa/S3/hexa3.bmp", &hexainfo);
			hexamaskpixels = ReadBitmap("Hexa/S3/hexa3M.bmp", &hexamaskinfo);
			timer++;
		}
	}
	
	if(timer>=15) timer=0;
}



Hexa::~Hexa()
{
	
}

void Hexa::SetPixels(){	
}


bool Hexa::ArrowCheck(int x, int y){
	if(location[0]>=x-radius && location[0]<=x && location[1]<=y){/*
		switch(){
			case 0:
				PlaySound("Sounds/hexaoonhit.wav",NULL, SND_ASYNC);
				break;
			case 1:
				PlaySound("Sounds/hexaoonhit2.wav",NULL, SND_ASYNC);
				break;
		}*/
		return true;
	}
	return false;
}

bool Hexa::playerHit(GLfloat x, GLfloat y){
	if(location[0]>=x-radius && location[0]<=x+18 && location[1]<y+radius){
		return true;
	}
	return false;
}

void Hexa::Update(){
}


void Hexa::Draw(){
	if(location[0]+radius>SCREENMAXX) speedX*=-1;
	if(location[0]<0) speedX*=-1;
	if(location[1]+radius>SCREENMAXY) speedY*=-1;
	if(location[1]<0) speedY*=-1;

	location[0]+=speedX*2;
	location[1]+=speedY*2;
	Rotate();

	glEnable(GL_COLOR_LOGIC_OP);
	glLogicOp(GL_AND_INVERTED);
	glRasterPos2i(location[0],location[1]);
	glDrawPixels(hexamaskinfo->bmiHeader.biWidth, hexamaskinfo->bmiHeader.biHeight,GL_BGR_EXT, GL_UNSIGNED_BYTE, hexamaskpixels);
	glLogicOp(GL_OR);
	glDrawPixels(hexainfo->bmiHeader.biWidth, hexainfo->bmiHeader.biHeight,GL_BGR_EXT, GL_UNSIGNED_BYTE, hexapixels);
    glDisable(GL_COLOR_LOGIC_OP);
}

void Hexa::DrawFreeze(){	
	Rotate();

	glEnable(GL_COLOR_LOGIC_OP);
	glLogicOp(GL_AND_INVERTED);
	glRasterPos2i(location[0],location[1]);
	glDrawPixels(hexamaskinfo->bmiHeader.biWidth, hexamaskinfo->bmiHeader.biHeight,GL_BGR_EXT, GL_UNSIGNED_BYTE, hexamaskpixels);
	glLogicOp(GL_OR);
	glDrawPixels(hexainfo->bmiHeader.biWidth, hexainfo->bmiHeader.biHeight,GL_BGR_EXT, GL_UNSIGNED_BYTE, hexapixels);
    glDisable(GL_COLOR_LOGIC_OP);
}