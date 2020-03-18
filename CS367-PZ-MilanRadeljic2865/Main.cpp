#include <windows.h> //the windows include file, required by all windows applications
#include <math.h>    // included for the cos and sin functions
#include <gl\glut.h> //the glut file for windows operations

#include "bmp.h"
#include "global.h"
#include <time.h>
#include "Balloon.h"
#include "Hexa.h"
#include "GUI.h"
#include <iostream>
using namespace std;
#include <random>


//random generator za size kugli za spawn
std::random_device rdy; 
std::mt19937 tst(rdy()); 
std::uniform_int_distribution<> size(1,4); 


BITMAPINFO *bginfo;				
GLubyte    *bgpixels;				
Player *igrac;
BITMAPINFO *ssinfo;				
GLubyte    *sspixels;				
GLubyte *maskpixels;			
BITMAPINFO *maskimginfo;	

vector<Balloon *> destroyb;			
BalloonMap::iterator it;
vector<Balloon *>::iterator itv;	

vector<Hexa *> destroybhex;			
HexaMap::iterator ithex;
vector<Hexa *>::iterator itvhex;	

GUI *gui;


bool shoot1 = false, shoot2 = false; //provera za strelu 1, 2 da li leti
int arrow1x1 = 0, arrow1y1 = 0; //pocetne koordinate za prvu strelu
int arrow1y = 0; // krajnje koordinate prve
int arrow2x1 = 0, arrow2y1 = 0; // pocetne koordinate za drugu strelu
int arrow2y = 0; //krajnje koordinate druge


bool pause=false;
bool freeze=false;
bool killall=false;
int lives=3;
int points=0;
int msec=0;
int unfreeze_msec;
bool hit=false;
int provera_zaHS=0;
int boostspawn=points/1000;

void createPlayer() {
	gui = new GUI();
	igrac = new Player();
	igrac->SetPixels(ssinfo, sspixels);
	igrac->SetMask(maskimginfo, maskpixels);
	//mciSendString("play \"Sounds/backgroundmusic.wav\" repeat", NULL, 0, NULL);
	PlaySound((LPCSTR)"Sounds/backgroundmusic.wav", 0, SND_ASYNC| SND_FILENAME | SND_LOOP);
}

void drawarrow1(int x1, int y1, int y){
	glLineWidth(7.);
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2i(x1,y1);
    glVertex2i(x1, y);
	glEnd();
}
void drawarrow2(int x1, int y1, int y){
	glLineWidth(7.);
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex2i(x1,y1);
    glVertex2i(x1, y);
	glEnd();
}

void highscorecontrol(){
	ifstream myfile;
	myfile.open ("hs.txt");
	string line;
	getline(myfile, line);
	myfile.close();
    provera_zaHS = stoi(line);
	if(points>provera_zaHS){
		ofstream myfile2;
		myfile2.open ("hs.txt");
		myfile2<<points;
		myfile2.close();
	}
}

void createBalloon() {
	if(points/1000>boostspawn){
		int ID = glutGet(GLUT_ELAPSED_TIME);
		Balloons[ID] = new Balloon(ID);
		boostspawn+=1;
	}
	if ( ((float)rand()/RAND_MAX) < 0.993)
		return;
		SYSTEMTIME systime;
		GetSystemTime(&systime);
		int ID = systime.wMinute*60+systime.wSecond;
		Balloons[ID] = new Balloon(size(tst),ID,20);
}

void createHexa(){	
	if ( ((float)rand()/RAND_MAX) < 0.999)
		return;
		SYSTEMTIME systime2;
		GetSystemTime(&systime2);
		int ID2 = systime2.wMinute*60+systime2.wSecond+1;
		Hexas[ID2] = new Hexa(1,ID2,1);	
}

void DestroyAllReset(){	
	if(Balloons.empty()&&Hexas.empty()) killall=false;
}
void BaloniControl(){
	Balloon *b;
    
    if (Balloons.size() == 0) {
    }
    else{
	  for (it = Balloons.begin(); it!= Balloons.end(); ++it) {
		  b = (Balloon *)((*it).second);
		  if(!freeze) b->Draw();
		  else b->DrawFreeze();
		  if(b->playerHit(igrac)&&!freeze){
			  if(lives>1){
				  switch(size(tst)){
					case 1:
						PlaySound("Sounds/playerhit1.wav", NULL, SND_ASYNC);
						break;
					case 2:
						PlaySound("Sounds/playerhit2.wav", NULL, SND_ASYNC);
						break;
					case 3:
						PlaySound("Sounds/playerhit3.wav", NULL, SND_ASYNC);
						break;
					case 4:
						PlaySound("Sounds/playerhit4.wav", NULL, SND_ASYNC);
						break;
				}
			  }
			  else PlaySound("Sounds/gameover.wav", NULL, SND_ASYNC);
			  lives--;
			  igrac->location[0]=SCREENMAXX/2;
			  arrow1x1=-150;
			  arrow2x1=-150;
			  hit=true;
			  break;
		  }
		  if(b->ArrowCheck(arrow1x1,arrow1y)||killall){
			arrow1x1=-150;
			shoot1=false;
			destroyb.push_back(b);
			if(b->ballsize<5) points+=b->ballsize*10;
			if(b->ballsize<4){
				int ID = glutGet(GLUT_ELAPSED_TIME);
				Balloon *l, *r;
				l = new Balloon(b->ballsize+1,ID,-20);
				l->location[0]=b->location[0];
				l->location[1]=b->location[1];
				Balloons[ID] = l;
				int ID2 = glutGet(GLUT_ELAPSED_TIME)+1;
				r = new Balloon(b->ballsize+1,ID2,20);
				r->location[0]=b->location[0];
				r->location[1]=b->location[1];
				Balloons[ID2] = r;
			}
			if(b->ballsize==5){
				freeze=true;
				unfreeze_msec=msec+4000;
			}
			if(b->ballsize==6){
				freeze=false;
				killall=true;
			}
		  }
		  else if(b->ArrowCheck(arrow2x1,arrow2y)){
			arrow2x1=-150;
			shoot2=false;
			destroyb.push_back(b);
			if(b->ballsize<5) points+=b->ballsize*10;
			if(b->ballsize<4){
				int ID = glutGet(GLUT_ELAPSED_TIME);
				Balloon *l, *r;
				l = new Balloon(b->ballsize+1,ID,-20);
				l->location[0]=b->location[0];
				l->location[1]=b->location[1];
				Balloons[ID] = l;
				int ID2 = glutGet(GLUT_ELAPSED_TIME)+1;
				r = new Balloon(b->ballsize+1,ID2,20);
				r->location[0]=b->location[0];
				r->location[1]=b->location[1];
				Balloons[ID2] = r;
			}
			if(b->ballsize==5){
				freeze=true;
				unfreeze_msec=msec+4000;
			}
			if(b->ballsize==6){
				killall=true;
				freeze=false;
			}
		  }
		}
	}
	if(hit){		
		Hexas.clear();
		Balloons.clear();
		hit=false;
	}
	for (itv = destroyb.begin(); itv!= destroyb.end(); ++itv){
	    if (Balloons.size() == 0) break;
		b =((Balloon *)(*itv));
		Balloons.erase(b->ID);
	}
}
void HexaControl(){
	Hexa *b;
    
    if (Hexas.size() == 0) {
    }
    else{
	  for (ithex = Hexas.begin(); ithex!= Hexas.end(); ++ithex) {
		  b = (Hexa *)((*ithex).second);
		  if(!freeze) b->Draw();
		  else b->DrawFreeze();
		  GLfloat playerx=igrac->GetXLocation(), playery=igrac->GetYLocation();
		  if(b->playerHit(playerx,playery)&&!freeze){
			  if(lives>1){
				  switch(size(tst)){
					case 1:
						PlaySound("Sounds/playerhit1.wav", NULL, SND_ASYNC);
						break;
					case 2:
						PlaySound("Sounds/playerhit2.wav", NULL, SND_ASYNC);
						break;
					case 3:
						PlaySound("Sounds/playerhit3.wav", NULL, SND_ASYNC);
						break;
					case 4:
						PlaySound("Sounds/playerhit4.wav", NULL, SND_ASYNC);
						break;
				}
			  }
			  else PlaySound("Sounds/gameover.wav", NULL, SND_ASYNC);
			  lives--;
			  igrac->location[0]=SCREENMAXX/2;
			  arrow1x1=-150;
			  arrow2x1=-150;
			  hit=true;
			  break;
		  }
		  if(b->ArrowCheck(arrow1x1,arrow1y)||killall){
			arrow1x1=-150;
			shoot1=false;
			destroybhex.push_back(b);
			points+=b->hexasize*10;
			if(b->hexasize<3){
				SYSTEMTIME systime;
				GetSystemTime(&systime);
				int ID = glutGet(GLUT_ELAPSED_TIME);
				Hexa *l, *r;
				l = new Hexa(b->hexasize+1,ID,-1);
				l->location[0]=b->location[0];
				l->location[1]=b->location[1];
				Hexas[ID] = l;
				int ID2 = glutGet(GLUT_ELAPSED_TIME)+1;
				r = new Hexa(b->hexasize+1,ID2,1);
				r->location[0]=b->location[0];
				r->location[1]=b->location[1];
				Hexas[ID2] = r;
			}
		  }
		  else if(b->ArrowCheck(arrow2x1,arrow2y)){
			arrow2x1=-150;
			shoot2=false;
			destroybhex.push_back(b);
			points+=b->hexasize*10;
			if(b->hexasize<3){
				SYSTEMTIME systime;
				GetSystemTime(&systime);
				int ID = glutGet(GLUT_ELAPSED_TIME);
				Hexa *l, *r;
				l = new Hexa(b->hexasize+1,ID,-1);
				l->location[0]=b->location[0];
				l->location[1]=b->location[1];
				Hexas[ID] = l;
				int ID2 = glutGet(GLUT_ELAPSED_TIME)+1;
				r = new Hexa(b->hexasize+1,ID2,1);
				r->location[0]=b->location[0];
				r->location[1]=b->location[1];
				Hexas[ID2] = r;
			}
		  }
		}
	}
	if(hit){
		Hexas.clear();
		Balloons.clear();
		hit=false;
	}
	for (itvhex = destroybhex.begin(); itvhex!= destroybhex.end(); ++itvhex){
	    if (Hexas.size() == 0) break;
		b =((Hexa *)(*itvhex));
		Hexas.erase(b->ID);
	}
}

void Display(){
	if(lives==0){
		gui->GameOver(points);
	}
	else if(pause){
		gui->Pause();
	}

	else{
	glRasterPos2i(0,0);
    glDrawPixels(bginfo->bmiHeader.biWidth, bginfo->bmiHeader.biHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bgpixels);
	
	BaloniControl();
	HexaControl();

	if(shoot1) drawarrow1(arrow1x1,arrow1y1, arrow1y);
	if(shoot2) drawarrow2(arrow2x1,arrow2y1, arrow2y);
	igrac->Draw();
	}
	if(freeze){
			gui->drawfreeze(1+(unfreeze_msec-msec)/1000);
	}
	gui->drawexit();
	gui->drawHS();
	gui->drawNG();
	gui->drawlife(lives);
	gui->drawtime(msec/1000);
	gui->drawpoints(points);	
	highscorecontrol();
	glutPostRedisplay();
	glFlush();
	glutSwapBuffers();
	glFinish();
}

void strelatajmer(){
	if(shoot1)	arrow1y+=7; //povecanje strele
	if(shoot2) arrow2y+=7; //povecanje strele
	if(arrow1y>=720) {
		shoot1=false;
		arrow1x1=-100;
	}
	if(arrow2y>720){
		shoot2=false;
		arrow2x1=-100;
	}
}

void timer(int value)
{   
	if(!pause && lives>0){
	createBalloon();
	createHexa();
	strelatajmer();
	msec+=30;
	DestroyAllReset();
	}
	if(msec>unfreeze_msec) freeze=false;
    glutTimerFunc(30, timer, 0);
}



void reshape(int w, int h) {
    glutReshapeWindow(SCREENMAXX, SCREENMAXY);
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
   // keep our logical coordinate system constant
    gluOrtho2D(0.0, SCREENMAXX, 0.0, SCREENMAXY);
}

void init(void){
	createPlayer();
}

//potrebno da bi znali koja strela se brise ako se ispaljuje treci put
int check=1;
void processKeys(unsigned char key, int x, int y) {
	if (key==13){//enter key
		if(lives==0){
			lives=3;
			points=0;
			boostspawn=points/1000;
			msec=0;
			Balloons.clear();
			Hexas.clear();
		}
	}
	if (key == 27)// escape key
        pause=!pause;
    if (key == 32){ //space key
		  sspixels = ReadBitmap("PSR.bmp", &ssinfo);  
		  maskpixels = ReadBitmap("PSRmask.bmp", &maskimginfo);
		  igrac->SetPixels(ssinfo,sspixels);
		  igrac->SetMask(maskimginfo,maskpixels);
		  igrac->move_l=false;
		  igrac->move_r=false;

		  if(!shoot1){
		  arrow1x1 = int (igrac->GetXLocation()+10);
		  arrow1y1 = int (igrac->GetYLocation());
		  arrow1y = 30;
		  shoot1 = true;
		  }
		  else if(shoot1 && !shoot2){
		  arrow2x1 = int (igrac->GetXLocation()+10);
		  arrow2y1 = int (igrac->GetYLocation());
		  arrow2y = 30;
		  shoot2 = true;
		  }
		  else if(shoot1 && shoot2 && check==1){
				arrow1x1 = int (igrac->GetXLocation()+10);
				arrow1y1 = int (igrac->GetYLocation());
				arrow1y = 30;
				check=-1;
		  }
		  else if(shoot1 && shoot2 && check==-1){
				arrow2x1 = int (igrac->GetXLocation()+10);
				arrow2y1 = int (igrac->GetYLocation());
				arrow2y = 30;
				check=1;
		  }
		PlaySound("Sounds/shoot.wav", NULL, SND_ASYNC);
	  }	
}

void specialKeys(int key, int x, int y) {
	if(key==GLUT_KEY_RIGHT){
		igrac->move_l=false;
		igrac->move_r=true;
		igrac->UpdatePosition(12);
	}
	if(key==GLUT_KEY_LEFT){
		igrac->move_r=false;
		igrac->move_l=true;
		igrac->UpdatePosition(-12);	
	}
}
void KeyboardUp(int key, int x, int y ){	
	switch(key) {
		case GLUT_KEY_RIGHT:
			igrac->move_r=false;
		break;
		case GLUT_KEY_LEFT:
			igrac->move_l=false;
		break;
	}
}

void MouseButton(int button,int state,int x, int y)
{
	if (state == GLUT_DOWN) 
	{
		switch(button){
		case GLUT_LEFT_BUTTON:
			if(x>180 && x<330 && y>3 && y<20){
				Balloons.clear();
				lives=3;
				msec=0;
				points=0;
				boostspawn=points/1000;
			}
			if(x>500 && x<560 && y>3 && y<20){
				exit(0);
			}

			break;
		}
	}
}

void main(int argc, char* argv[])
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (SCREENMAXX, SCREENMAXY);   
  glutCreateWindow("Super Pang!");
  
  bgpixels = ReadBitmap("background.bmp", &bginfo);
  
  init();
  glutSpecialFunc(specialKeys);
  glutSpecialUpFunc(KeyboardUp);
  glutKeyboardFunc(processKeys);
  glutTimerFunc(0, timer, 0);
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutMouseFunc(MouseButton);
  glutMainLoop();

  
}
