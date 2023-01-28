#include "GraphicsObject.h"

//The CPP file is where we DEFINE all of our class information
GraphicsObject::GraphicsObject(CString filepath, int x, int y, int width, int height)
{
	this->x = x;  
	this->y = y;
	this->width = width;
	this->height = height;
	this->hitWidth = width;
	this->hitHeight = height;
	picX = 0;
	picY = 0;
	startFrame = 0;
	endFrame = 0;
	currentFrame = 0;
	this->filepath = filepath;
	canLoop = true;
	image.Load(filepath);

}

void GraphicsObject::Draw(HDC offScreenDC)
{
	Animate();
	HDC screenDC = offScreenDC; //variable for your screen
	image.SetTransparentColor(RGB(255, 174, 201)); //causes the pink background to be transparent
	image.TransparentBlt(
		offScreenDC, //our target screen
		x - mapPosition, //xpos of image, we substract map position so that EVERY OTHER	GraphicsObject 
		y, //ypos of image
		width, //width of image
		height, //height of image
		picX, //xpos of where we start drawing on the source image
		picY, //ypos of where we start drawing on the source image
		width, //how much of the image we want to draw
		height //how much of the image we want to draw
	);
	
}

void GraphicsObject::Animate()
{
		currentFrame += 1; //gp through the frame in order

		if (currentFrame >= endFrame)
		{

			if (canLoop == true)
			{
				currentFrame = startFrame; //if statement used to loop our animation
			}
			else
			{
				currentFrame = endFrame;
			}
			
		}


	picX = width * currentFrame;
}

bool GraphicsObject::isColliding(GraphicsObject* object)
{
	if (x + hitWidth > object->x && x < object->x + object->hitWidth
		&& y + hitHeight > object->y && y < object->y + object->hitHeight)
	{
			return true;
	}
	return false;
}

GraphicsObject::~GraphicsObject()
{
}