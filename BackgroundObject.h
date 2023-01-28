#pragma once
#include "GraphicsObject.h"

class BackgroundObject : public GraphicsObject
{
public:
	BackgroundObject(CString filename, int x, int y, int width, int height, double mapSpeed);
	double mapSpeed; //the speed at which our backgroundobject scrolls 
	void Draw(HDC offScreenDC); //our new draw function that will be used to draw our background more than once

	~BackgroundObject();
};

