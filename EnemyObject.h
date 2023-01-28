#pragma once
#include "WeaponsObject.h"
class EnemyObject :
    public WeaponsObject
{
public:
    EnemyObject(CString filename, int xpos, int ypos): WeaponsObject(filename, xpos, ypos)
    {
        isAlive = true;
    }
    bool isAlive;
    int xspeed, yspeed;

    virtual void Move() = 0;

    virtual void OnHit(BulletObject* bullet) = 0;

    virtual void BlockCollision(GraphicsObject* targetBlock) = 0;

    ~EnemyObject()
    {
    }
};

