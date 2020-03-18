#ifndef __bmp_h__
#define __bmp_h__

#include <gl/glut.h>

#include <windows.h>
#include <wingdi.h>

extern GLubyte * ReadBitmap(const char *filename,BITMAPINFO **info);  
extern int SaveBitmap(const char *filename, BITMAPINFO *info,GLubyte *bits); 
extern GLubyte * ReadBitmapFromScreen(BITMAPINFO **info);
#endif