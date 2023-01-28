#include "BackgroundObject.h"

BackgroundObject::BackgroundObject(CString filepath, int x, int y, int width, int height, double mapSpeed) : GraphicsObject(filepath, x, y, width, height)
{
	this->mapSpeed = mapSpeed;
}

void BackgroundObject::Draw(HDC offScreenDC)
{
	int relativeX = (int) ((x - mapPosition) * mapSpeed) % width;

	HDC screenDC = offScreenDC;
	image.SetTransparentColor(RGB(255, 174, 201)); 
	image.TransparentBlt(screenDC, relativeX, y, width, height, 0, 0, width, height); //this is our middle backgound image we're drawing
	image.TransparentBlt(screenDC, relativeX - width, y, width, height, 0, 0, width, height); //this is our left backgound image we're drawing
	image.TransparentBlt(screenDC, relativeX + width, y, width, height, 0, 0, width, height); //this is our right backgound image we're drawing
  
}

BackgroundObject::~BackgroundObject()
{
}
