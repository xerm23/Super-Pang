#include "global.h"

class Hexa{
public:
	Hexa(int size, int id, int xvel);
	virtual ~Hexa();
	bool ArrowCheck(int x, int y);
	void SetPixels();
	void Draw();
	void DrawFreeze();
	void Update();
	GLfloat GetXLocation(){ return location[0];}
	GLfloat GetYLocation() {return location[1];}
	float GetRadius() {return radius;}
	void Rotate();
	int hexasize, timer;	
	int ID;
	float speedX, speedY, ugao;
	GLfloat location[2]; 
	bool playerHit(GLfloat x, GLfloat y);
private:
	float radius;
	GLubyte *hexapixels;			
	BITMAPINFO *hexainfo;	
	GLubyte *hexamaskpixels;			
	BITMAPINFO *hexamaskinfo;			
};

typedef map<int, Hexa*> HexaMap;
static HexaMap Hexas;
