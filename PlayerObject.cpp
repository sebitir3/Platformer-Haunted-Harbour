#include "PlayerObject.h"

PlayerObject::PlayerObject() : WeaponsObject("Pics/ViktorTesla.bmp", 200, 50)
{
	xspeed = 0;
	yspeed = 0;
	startFrame = 0;
	endFrame = 0;
	canLoop = false;
	currentState = STANDRIGHT;
	stoppedRight = true;
	stoppedLeft = true;
	width = 54;
	height = 42;

	hitWidth = width;
	hitHeight = height;

	//set up our WeaponsObject below so that our player can fire bullets
	bulletAmount = 25;
	for (int i = 0; i < bulletAmount; i++)
	{
		bullets[i] = new PurpleBulletObject(); //by writing "new" and storing it insied of the array, we are creating it and also keeping track of it in memory
	}
}

void PlayerObject::Move()
{
	previousX = x;
	previousY = y;

	x += 2 * xspeed;
	y += yspeed;
	yspeed += GRAVITY; // the reason we add to the yspeed is so our y-coordinate changes differently

	//if our charachter's y position is ever lower than the ground ...
	if (y >= 400 - height)
	{
		//... set it as the same level as the ground
		y = 400 - height;
		if (currentState == JUMPRIGHT && stoppedRight == true)
		{
			SetStandingRight();
		}
		else if (currentState == JUMPLEFT && stoppedLeft == true)
		{
			SetStandingLeft();
		}
		else if (currentState == JUMPRIGHT && stoppedRight == false)
		{
			SetMoveRight();
		}
		else if (currentState == JUMPLEFT && stoppedLeft == false)
		{
			SetMoveLeft();
		}
	} 
	
	if (x - mapPosition < 100 || x - mapPosition > 500)
	{
		mapPosition += 2 * xspeed; //everytime we move our character, we increase the map position by the same amount
	}

	Animate();
}
void PlayerObject::SetMoveRight()
{
	picX = 0;
	picY = 0;       
	startFrame = 1;
	endFrame = 8;
	canLoop = true;
	xspeed = 5;
	height = 42;
	width = 54;
	currentState = MOVERIGHT;
}

void PlayerObject::SetStandingRight()
{
	picX = 0;
	picY = 0;
	startFrame = 0;
	endFrame = 0;
	currentFrame = 0;
	canLoop = false;
	xspeed = 0;
	height = 42;
	width = 54;
	currentState = STANDRIGHT;
}

void PlayerObject::SetMoveLeft()
{
	picX = 0;
	picY = 42;
	startFrame = 1;
	endFrame = 8;
	canLoop = true;
	xspeed = -5;
	height = 42;
	width = 54;
	currentState = MOVELEFT;
}

void PlayerObject::SetStandingLeft()
{
	picX = 0;
	picY = 42;
	startFrame = 0;
	endFrame = 0;
	currentFrame = 0;
	canLoop = false;
	xspeed = 0;
	height = 42;
	width = 54;
	currentState = STANDLEFT;
}

void PlayerObject::ShootingRight()
{
	picX = 0;
	picY = 199;
	startFrame = 0;
	endFrame = 0;
	currentFrame = 0;
	canLoop = false;
	xspeed = 0;
	height = 38;
	width = 59;
	currentState = SHOOTRIGHT;
}

void PlayerObject::ShootingLeft()
{
	picX = 0;
	picY = 237;
	startFrame = 0;
	endFrame = 0;
	currentFrame = 0;
	canLoop = false;
	xspeed = 0;
	height = 38;
	width = 59;
	currentState = SHOOTLEFT;
}

void PlayerObject::JumpingRight()
{
	picX = 0;
	picY = 86;
	startFrame = 1;
	currentFrame = 1;
	endFrame = 5;
	canLoop = false;
	yspeed = -20;
	height = 56;
	width = 48;
	currentState = JUMPRIGHT;
}

void PlayerObject::JumpingLeft()
{
	picX = 0;
	picY = 146;
	startFrame = 1;
	currentFrame = 1;
	endFrame = 5;
	canLoop = false;
	yspeed = -20;
	height = 56;
	width = 48;
	currentState = JUMPLEFT;
}

void PlayerObject::PlayerBlockCollision(GraphicsObject* targetBlock)
{
	if (isColliding(targetBlock))
	{
		//when colliding onto left side
		if (previousX + hitWidth <= targetBlock->x)
		{
			x = targetBlock->x - hitWidth;
		}
		//when colliding onto right side
		else if (previousX >= targetBlock->x + targetBlock->hitWidth)
		{
			x = targetBlock->x + targetBlock->hitWidth;
		}
		//when colliding onto top side
		else if (previousY + hitHeight <= targetBlock->y)
		{
			y = targetBlock->y - hitHeight;
			yspeed = 0;

			if (currentState == JUMPRIGHT && stoppedRight == true)
			{
				SetStandingRight();
			}
			else if (currentState == JUMPLEFT && stoppedLeft == true)
			{
				SetStandingLeft();
			}
			else if (currentState == JUMPRIGHT && stoppedRight == false)
			{
				SetMoveRight();
			}
			else if (currentState == JUMPLEFT && stoppedLeft == false)
			{
				SetMoveLeft();
			}
		}
		//when colliding onto bottom side
		else if (previousY >= targetBlock->y + targetBlock->height)
		{
			y = targetBlock->y + targetBlock->height;
		}
	}
}

void PlayerObject::OnHit(BulletObject* bulletHitBy)
{
	
}

bool PlayerObject::IsJumping()
{
	return currentState == JUMPRIGHT || currentState == JUMPLEFT;
}


PlayerObject::~PlayerObject()
{
}
