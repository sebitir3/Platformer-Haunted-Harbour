#include "AirEnemiesObject.h"

AirEnemiesObject::AirEnemiesObject(PlayerObject* viktor, int centreX, int centreY) : EnemyObject("pics/SeaHag.bmp", x, y)
{
	this->viktor = viktor;
	this->centreX = centreX;
	this->centreY = centreY;
	width = 28;
	height = 40;
	hitWidth = 27;
	hitHeight = 40;
	xspeed = 5;
	yspeed = 5;
	isAlive = true;
	radius = 50;
	angle = 0;
	isExploding = false;

	bulletAmount = 25;
	for (int i = 0; i < bulletAmount; i++)
	{
		bullets[i] = new GreenBulletObject();
	}
}

void AirEnemiesObject::Move()
{
	Animate();

	if (isExploding)
	{
		if (currentFrame == endFrame)
		{
			isAlive = false;
		}
	}
	else
	{

		double radians = angle / 180 * 3.14159;
		angle += 10;

		y = centreY + sin(radians) * radius;
		x = centreX + cos(radians) * radius;

		coolDown += 1;

		if (coolDown >= 20)
		{
			ShootPlayer();
			coolDown = 0;
		}

		if (viktor->x > x + width)
		{
			MoveRight();
		}
		else if (viktor->x + viktor->width > x)
		{
			MoveLeft();
		}
	}

}

void AirEnemiesObject::MoveRight()
{
	picX = 0;
	picY = 40;
	startFrame = 0;
	endFrame = 4;
	canLoop = true;
}

void AirEnemiesObject::MoveLeft()
{
	picX = 0;
	picY = 0;
	startFrame = 0;
	endFrame = 4;
	canLoop = true;
}

void AirEnemiesObject::Death()
{
	picX = 0;
	picY = 156;
	startFrame = 0;
	currentFrame = 0;
	endFrame = 6;
	canLoop = true;
	isExploding = true;
}

void AirEnemiesObject::OnHit(BulletObject* bulletHitBy)
{
	Death();
	xspeed = 0;
	yspeed = 0;
}

void AirEnemiesObject::BlockCollision(GraphicsObject* targetBlock)
{
}

void AirEnemiesObject::ShootPlayer()
{
	int ydistance, xdistance;

	ydistance = viktor->y - y;
	xdistance = viktor->x - x;

	FireBullet(x, y, xdistance / 5, ydistance / 5);
}

AirEnemiesObject::~AirEnemiesObject()
{
}
