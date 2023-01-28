#include "PurpleBulletObject.h"

PurpleBulletObject::PurpleBulletObject() : BulletObject("Pics/PurpleFire.bmp")
{
	xspeed = 5;
	yspeed = 0;
	distanceTravelled = 0;
	isAlive = false;
	isExploding = false;
	width = 13;
	height = 14;
	hitWidth = width;
	hitHeight = height;
	maxDistance = 400;
}

void PurpleBulletObject::SetExploding()
{
	picX = 0;
	picY = 12;
	startFrame = 0;
	currentFrame = 0;
	endFrame = 1;
	canLoop = false;
	height = 32;
	width = 27;
	isExploding = true;
}

void PurpleBulletObject::Reset()
{
	isAlive = false;
	isExploding = false;
	picX = 0;
	picY = 0;
	width = 14;
	height = 14;
	distanceTravelled = 0;
	currentFrame = 0;
	endFrame = 0;
}

PurpleBulletObject::~PurpleBulletObject()
{

}
