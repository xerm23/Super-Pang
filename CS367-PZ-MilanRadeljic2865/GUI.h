#include "global.h"
#include <string>

class GUI{
public:
	GUI();
	~GUI();
	void drawlife(int life);
	void drawtime(int sec);
	void drawpoints(int points);
	void drawHS();
	void drawNG();
	void drawfreeze(int sec);
	void drawexit();
	void Pause();
	void GameOver(int points);
private:
	char * int2char(int iNumber);
};