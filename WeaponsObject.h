#pragma once
#include "GraphicsObject.h"
#include "BulletObject.h"

class WeaponsObject : public GraphicsObject
{
public:
	WeaponsObject(CString filename, int xpos, int yspos);

	int bulletAmount; //amount of bullets
	BulletObject* bullets[50]; //array that stores and keeps track of our bullets

	bool isAlive; //tells wether or not the character is alive or not

	void FireBullet(int startPosX, int startPosY, int bulletSpdX, int bulletSpdY);
	void DrawBullets(HDC offScreenDC);
	void MoveBullets();

	void BulletBlockCollision(GraphicsObject* targetblock);
	void BulletCharacterCollision(WeaponsObject* targetCharacter);

	virtual void OnHit(BulletObject* bulletHitBy);

	~WeaponsObject();
};

