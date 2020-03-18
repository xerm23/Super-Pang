#include "Player.h"
#include <WinBase.h>
#include <iostream>
#include <time.h>
using namespace std;




Player::Player(){
	location[0] = SCREENMAXX/2. ;
	location[1] = 0;
	move_l=false;
	move_r=false;
	timeranimacije=0;
	mypixels = ReadBitmap("PSR.bmp", &myimginfo);  
	maskpixels = ReadBitmap("PSRmask.bmp", &maskimginfo);
}

Player::~Player( )
{
	
}

void Player::SetPixels(BITMAPINFO *ssinfo, GLubyte *sspixels){
	mypixels = sspixels;
	myimginfo = ssinfo;
}

void Player::SetMask(BITMAPINFO *maskinfo, GLubyte *mask_pixels){
	maskpixels = mask_pixels;
	maskimginfo = maskinfo;
}
void Player::Moving(){
	if(move_r){
		if(timeranimacije>=0&&timeranimacije<10){
			mypixels = ReadBitmap("Player/PR1.bmp", &myimginfo);
			maskpixels = ReadBitmap("Player/PRM1.bmp", &maskimginfo);
			timeranimacije++;
		}
		if(timeranimacije>=10&&timeranimacije<20){
			mypixels = ReadBitmap("Player/PR2.bmp", &myimginfo);
			maskpixels = ReadBitmap("Player/PRM2.bmp", &maskimginfo);
			timeranimacije++;
		}
		if(timeranimacije>=20&&timeranimacije<30){
			mypixels = ReadBitmap("Player/PR3.bmp", &myimginfo);
			maskpixels = ReadBitmap("Player/PRM3.bmp", &maskimginfo);
			timeranimacije++;
		}
		if(timeranimacije>=30&&timeranimacije<40){
			mypixels = ReadBitmap("Player/PR4.bmp", &myimginfo);
			maskpixels = ReadBitmap("Player/PRM4.bmp", &maskimginfo);
			timeranimacije++;
		}
	}
	else if(move_l){
		if(timeranimacije>=0&&timeranimacije<10){
			mypixels = ReadBitmap("Player/PL1.bmp", &myimginfo);
			maskpixels = ReadBitmap("Player/PLM1.bmp", &maskimginfo);
			timeranimacije++;
		}
		if(timeranimacije>=10&&timeranimacije<20){
			mypixels = ReadBitmap("Player/PL2.bmp", &myimginfo);
			maskpixels = ReadBitmap("Player/PLM2.bmp", &maskimginfo);
			timeranimacije++;
		}
		if(timeranimacije>=20&&timeranimacije<30){
			mypixels = ReadBitmap("Player/PL3.bmp", &myimginfo);
			maskpixels = ReadBitmap("Player/PLM3.bmp", &maskimginfo);
			timeranimacije++;
		}
		if(timeranimacije>=30&&timeranimacije<40){
			mypixels = ReadBitmap("Player/PL4.bmp", &myimginfo);
			maskpixels = ReadBitmap("Player/PLM4.bmp", &maskimginfo);
			timeranimacije++;
		}
	}
	else{
		mypixels = ReadBitmap("PSR.bmp", &myimginfo);  
		maskpixels = ReadBitmap("PSRmask.bmp", &maskimginfo);
	}
	
	if(timeranimacije>=40) timeranimacije=0;
}

void Player::Draw(){
	Moving();
	glEnable(GL_COLOR_LOGIC_OP);
	glLogicOp(GL_AND_INVERTED);
	glRasterPos2i(location[0],location[1]);
	glDrawPixels(maskimginfo->bmiHeader.biWidth, maskimginfo->bmiHeader.biHeight,GL_BGR_EXT, GL_UNSIGNED_BYTE, maskpixels);
	glLogicOp(GL_OR);
	glDrawPixels(myimginfo->bmiHeader.biWidth, myimginfo->bmiHeader.biHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, mypixels);
	glDisable(GL_COLOR_LOGIC_OP);
}


void Player::UpdatePosition(GLfloat x){	
	location[0]  += x;
	if(location[0]>=SCREENMAXX-24) location[0]=SCREENMAXX-24;
	if(location[0]<=0) location[0]=0;
}