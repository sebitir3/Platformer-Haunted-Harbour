#pragma once
#include "GraphicsObject.h"

class BulletObject : public GraphicsObject
{
public:
	BulletObject(CString filepath);

	int xspeed, yspeed; //speed for our bullets
	int distanceTravelled;
	int maxDistance;
	int previousX, previousY;

	bool isExploding; 
	bool isAlive; //wether the bullet is alive or not

	virtual void SetExploding();
	void Move(); //handle the bullet's movement
	virtual void Reset();

	~BulletObject();
};

