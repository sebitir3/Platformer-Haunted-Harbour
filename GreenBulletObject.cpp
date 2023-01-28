#include "GreenBulletObject.h"

GreenBulletObject::GreenBulletObject() : BulletObject("Pics/GreenFire.bmp")
{
	xspeed = 0;
	yspeed = 0;
	distanceTravelled = 0;
	isAlive = false;
	isExploding = false;
	width = 8;
	height = 8;
	hitWidth = width;
	hitHeight = height;
	maxDistance = 400;
}

void GreenBulletObject::SetExploding()
{
	picX = 0;
	picY = 8;
	startFrame = 0;
	currentFrame = 0;
	endFrame = 2;
	x -= 8;
	y -= 8;
	canLoop = false;
	height = 15;
	width = 15;
	isExploding = true;
}

void GreenBulletObject::Reset()
{
	isAlive = false;
	isExploding = false;
	picX = 0;
	picY = 0;
	width = 8;
	height = 8;
	distanceTravelled = 0;
	currentFrame = 0;
	endFrame = 0;
}

GreenBulletObject::~GreenBulletObject()
{
}
