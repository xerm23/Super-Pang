
#include "GUI.h"
#include <WinBase.h>
using namespace std;

//- pocetni meni u igri (New Game, Exit, High Score). I da uvek postoji bez obzira da li je igrač izgubio živote ili je pritisnuo ESC.


GUI::GUI(){

}
char* GUI::int2char(int iNumber){
    int iNumbersCount=0;
    int iTmpNum=iNumber;
    while(iTmpNum){
        iTmpNum/=10;
        iNumbersCount++;
    }
    char *buffer=new char[iNumbersCount+1];
    for(int i=iNumbersCount-1;i>=0;i--){
        buffer[i]=(char)((iNumber%10)|48);
        iNumber/=10;
    }
    buffer[iNumbersCount]='\0';
    return buffer;

}

void GUI::drawtime(int sec){
	glColor3f(1.,0., 0.0); 
	char *sekunde=int2char(sec);
	char *c="Time alive: ";
	char *s = "s";

	glRasterPos3f(SCREENMAXX/2-60 , 670. , 0.);
	for (; *c != '\0'; c++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	
	for (; *sekunde != '\0'; sekunde++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *sekunde);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *s);
}

void GUI::drawlife(int life){
	glColor3f(1.,0., 0.0); 
	char *lives=int2char(life);
	char *c="Lives: ";

	glRasterPos3f(SCREENMAXX/4-60 , 670. , 0.);
	for (; *c != '\0'; c++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	
	for (; *lives!= '\0'; lives++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *lives);
}

void GUI::drawpoints(int points){
	glColor3f(1.,0., 0.0); 
	char *poeni=int2char(points);
	char *c="Points: ";

	glRasterPos3f(SCREENMAXX*3/4-60 , 670. , 0.);
	for (; *c != '\0'; c++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	
	for (; *poeni != '\0'; poeni++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *poeni);
}

void GUI::GameOver(int points){
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2i(0,0);
	glVertex2i(0, SCREENMAXY);
	glVertex2i(SCREENMAXX, SCREENMAXY);
	glVertex2i(SCREENMAXX, 0);
	glEnd();
	glColor3f(1.,0., 0.0);
	char *poeni=int2char(points);
	char *c="Game Over!";
	char *r="Press Enter to play again.";
	char *p="Total points: ";

	glRasterPos3f(SCREENMAXX/2-60 , SCREENMAXY/2+32 , 0.);
	for (; *c != '\0'; c++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
	glRasterPos3f(SCREENMAXX/2-130, SCREENMAXY/2 , 0.);
	for (; *r != '\0'; r++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *r);
	}
	glRasterPos3f(SCREENMAXX/2-60, SCREENMAXY/2-32 , 0.);
	
	for (; *p != '\0'; p++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
	for (; *poeni != '\0'; poeni++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *poeni);
}

void GUI::drawNG(){
	glColor3f(1.,1., 1); 
	char *c="NEW GAME";

	glRasterPos3f(SCREENMAXX/4-80 , 700. , 0.);
	for (; *c != '\0'; c++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

void GUI::drawexit(){
	glColor3f(1.,1., 1); 
	char *c="EXIT";

	glRasterPos3f(SCREENMAXX/2-40 , 700. , 0.);
	for (; *c != '\0'; c++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}


void GUI::drawfreeze(int sec){
	glColor3f(1.,0., 0.0); 
	char *sekunde=int2char(sec);
	char *c="Freeze: ";
	char *s = "s";

	glRasterPos3f(SCREENMAXX/2-60 , 400 , 0.);
	for (; *c != '\0'; c++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	
	for (; *sekunde != '\0'; sekunde++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *sekunde);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *s);
}


void GUI::drawHS(){
	
	ifstream myfile;
	myfile.open ("hs.txt");
	string line;
	getline(myfile, line);
	myfile.close();
	glColor3f(1.,0., 0.0); 
	//char *poeni=int2char();
	char *c="High score: ";
	char *poeni = new char[line.length() + 1];
	strcpy(poeni, line.c_str());

	glRasterPos3f(SCREENMAXX*3/4-60 , 700 , 0.);
	for (; *c != '\0'; c++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	
	for (; *poeni != '\0'; poeni++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *poeni);
}


void GUI::Pause(){
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2i(0,0);
	glVertex2i(0, SCREENMAXY);
	glVertex2i(SCREENMAXX, SCREENMAXY);
	glVertex2i(SCREENMAXX, 0);
	glEnd();
	glColor3f(1.,0., 0.0);
	char *c="Paused!";
	glRasterPos3f(SCREENMAXX/2-80 , SCREENMAXY/2 , 0.);
	for (; *c != '\0'; c++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}
