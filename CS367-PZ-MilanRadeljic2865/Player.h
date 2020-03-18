#include "global.h"

class Player{
public:
	Player();
	virtual ~Player();
	void SetPixels(BITMAPINFO *ssinfo, GLubyte *sspixels);
	void SetMask(BITMAPINFO *maskinfo, GLubyte *mask_pixels);
	void Draw();
	void UpdatePosition(GLfloat x);
	GLfloat GetXLocation(){ return location[0];}
	GLfloat GetYLocation() {return location[1];}
	GLfloat location[2]; 
	bool move_l, move_r;
	void Moving();
	int timeranimacije;
private:  
	GLubyte *mypixels;
	GLubyte *maskpixels;
	BITMAPINFO *myimginfo;	
	BITMAPINFO *maskimginfo;				
};