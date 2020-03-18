#include "global.h"
#include "Player.h"
class Balloon;

class Balloon{
public:
	Balloon(int size, int id, int xvel);
	Balloon(int id);
	virtual ~Balloon();
	bool ArrowCheck(int x, int y);
	void SetPixels();
	void Draw();
	void DrawFreeze();
	void Update(GLfloat x, GLfloat y);
	GLfloat GetXLocation(){ return location[0];}
	GLfloat GetYLocation() {return location[1];}
	float GetRadius() {return radius;}
	int ballsize;	
	int ID;
	GLfloat location[2]; 
	bool playerHit(Player *p);
private:
	float velocityX;
	float velocityY;
	float maxvelocityY;
	float acc;
	float dt;
	float limitY;
	float radius;
	GLubyte *ballpixels;			
	BITMAPINFO *ballinfo;	
	GLubyte *ballmaskpixels;			
	BITMAPINFO *ballmaskinfo;			
};

typedef map<int, Balloon*> BalloonMap;
static BalloonMap Balloons;
