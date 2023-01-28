#pragma once
#include "atlimage.h"
#include "framework.h"

//The header file is where we DECLARE all of our class information

class GraphicsObject
{
public:
	GraphicsObject(CString filepath, int x, int y, int width, int height); //constructor for GO

	//*************variables***************//
	CString filepath; //filepath of the image
	CImage image; //our image variable
	int x; //x-position of GO
	int y; //y-position of GO
	int width;
	int height;
	int hitWidth, hitHeight; //the size of this GraphicsObject's hitbox
	int picX; //the x-position of where we start drawing our image
	int picY; //the y-position of where we start drawing our image
	int startFrame;
	int endFrame;
	int currentFrame;
	bool canLoop; //a true/false value that tells us id we can loop the animation

	//*************variables***************//

	//*************functions***************//
	void Draw(HDC offScreenDC);
	void Animate();
	bool isColliding(GraphicsObject* object);
	//*************functions***************//

	~GraphicsObject(); //destructor for GO
};

