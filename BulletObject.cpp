#include "BulletObject.h"
#include <math.h>

BulletObject::BulletObject(CString filepath) : GraphicsObject(filepath, x, y, width, height)
{
	
}

void BulletObject::SetExploding()
{
}

void BulletObject::Move()
{
	if (isExploding == true)
	{
		if (currentFrame == endFrame)
		{
			Reset();
		}
	}
	else
	{
		previousX = x;
		previousY = y;
		x += xspeed;
		y += yspeed;

		distanceTravelled += abs(xspeed) + abs(yspeed);

		//check to see if the bullet travels too far and then disable it
		if (distanceTravelled > maxDistance)
		{
			isAlive = false;
			distanceTravelled = 0;
		}
	}

	Animate();
}

void BulletObject::Reset()
{
}

BulletObject::~BulletObject()
{
}
