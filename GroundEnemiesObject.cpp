#include "GroundEnemiesObject.h"
#include <math.h>

GroundEnemiesObject::GroundEnemiesObject() : EnemyObject("Pics/SkullCrab.bmp", 280, 50)
{
	width = 28;
	height = 38;
	hitWidth = 28;
	hitHeight = 38;
	xspeed = 5;
	yspeed = 0;
	isAlive = true;

	bulletAmount = 25;
	for (int i = 0; i < bulletAmount; i++)
	{
		bullets[i] = new GreenBulletObject();
	}
}

void GroundEnemiesObject::Move()
{
	previousX = x;
	previousY = y;

	x += xspeed;
	y += yspeed;
	yspeed += GRAVITY;

	if (y > 400 - height)
	{
		y = 400 - height;
	}

	if (xspeed > 0)
	{
		MoveRight();

		int randomNum = rand() % 30;

		if (randomNum == 1)
		{
			FireBullet(x + width, y, 30, 0);
		}
	}
	if (xspeed < 0)
	{
		MoveLeft();

		int randomNum = rand() % 30;

		if (randomNum == 1)
		{
			FireBullet(x, y, -30, 0);
		}
	}

	Animate();
}

void GroundEnemiesObject::MoveRight()
{
	picX = 0;
	picY = 38;
	startFrame = 0;
	endFrame = 10;
	canLoop = true;
}

void GroundEnemiesObject::MoveLeft()
{
	picX = 0;
	picY = 0;
	startFrame = 0;
	endFrame = 10;
	canLoop = true;
}

void GroundEnemiesObject::Death()
{
	picX = 0;
	picY = 74;
	startFrame = 0;
	endFrame = 0;
	canLoop = false;
}

void GroundEnemiesObject::OnHit(BulletObject* bulletHitBy)
{
	Death();
	xspeed = 0;
	isAlive = false;
}

void GroundEnemiesObject::BlockCollision(GraphicsObject* targetBlock)
{
	if (isColliding(targetBlock))
	{
		//when colliding onto left side
		if (previousX + hitWidth <= targetBlock->x)
		{
			x = targetBlock->x - hitWidth;
			xspeed = -5;
		}
		//when colliding onto right side
		else if (previousX >= targetBlock->x + targetBlock->hitWidth)
		{
			x = targetBlock->x + targetBlock->hitWidth;
			xspeed = 5;
		}
		//when colliding onto top side
		else if (previousY + hitHeight <= targetBlock->y)
		{
			y = targetBlock->y - hitHeight;
			yspeed = 0;

		}
		//when colliding onto bottom side
		else if (previousY >= targetBlock->y + targetBlock->height)
		{
			y = targetBlock->y + targetBlock->height;
		}
	}
}

GroundEnemiesObject::~GroundEnemiesObject()
{
}
