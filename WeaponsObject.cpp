#include "WeaponsObject.h"
#include <math.h>

WeaponsObject::WeaponsObject(CString filename, int xpos, int ypos) : GraphicsObject(filename, xpos, ypos, width, height)
{
	isAlive = true;
}

void WeaponsObject::FireBullet(int startPosX, int startPosY, int bulletSpdX, int bulletSpdY)
{ 
	for (int i = 0; i < bulletAmount; i++)
	{
		if (bullets[i]->isAlive == false)
		{
			bullets[i]->isAlive = true;
			bullets[i]->x = startPosX;
			bullets[i]->y = startPosY;
			bullets[i]->xspeed = bulletSpdX;
			bullets[i]->yspeed = bulletSpdY;

			bullets[i]->distanceTravelled = 0;
			break;
		}
	}
	
}

void WeaponsObject::DrawBullets(HDC offScreenDC)
{
	//check every bullet in the array
	for (int i = 0; i < bulletAmount; i++)
	{
		//only draw the bullet if the bullet is actually alive
		if (bullets[i]->isAlive == true)
		{
			bullets[i]->Draw(offScreenDC);
		}
	}
}

void WeaponsObject::MoveBullets()
{
	//check every bullet in the array
	for (int i = 0; i < bulletAmount; i++)
	{
		//only move the bullet if the bullet is actually alive
		if (bullets[i]->isAlive == true)
		{
			bullets[i]->Move();
		}
	}
}

void WeaponsObject::BulletBlockCollision(GraphicsObject* targetBlock)
{
	for (int i = 0; i < bulletAmount; i++)
	{ 
		if (bullets[i]->isColliding(targetBlock))
		{
			if (bullets[i]->isAlive == true && bullets[i]->isExploding == false)
			{
				bullets[i]->SetExploding();

				if (bullets[i]->xspeed > 0 && bullets[i]->previousX + bullets[i]->hitWidth <= targetBlock->x)
				{
					bullets[i]->x = targetBlock->x - bullets[i]->width;
				}
				else if (bullets[i]->xspeed < 0 && bullets[i]->previousX >= targetBlock->x + targetBlock->hitWidth)
				{
					bullets[i]->x = targetBlock->x + targetBlock->width;
				}
			}
		}
	}
}

void WeaponsObject::BulletCharacterCollision(WeaponsObject* targetCharacter)
{
	for (int i = 0; i < bulletAmount; i++)
	{
		if (bullets[i]->isColliding(targetCharacter))
		{
			if (bullets[i]->isAlive == true && bullets[i]->isExploding == false)
			{
				targetCharacter->OnHit(bullets[i]);
				
				bullets[i]->SetExploding();
				
			}
		}
	}
}


//OnHit handles the effects of what happens if the WeaponsObject gets hit
void WeaponsObject::OnHit(BulletObject* bulletHitBy)
{
	
}

WeaponsObject::~WeaponsObject()
{
}
