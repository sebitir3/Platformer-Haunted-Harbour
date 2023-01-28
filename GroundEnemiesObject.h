#pragma once
#include "EnemyObject.h"
#include "GreenBulletObject.h"

class GroundEnemiesObject :
    public EnemyObject
{
public :
    GroundEnemiesObject();
    int previousX, previousY;

    void Move();

    void MoveRight();
    void MoveLeft();
    void Death();

    void OnHit(BulletObject* bulletHitBy);

    void BlockCollision(GraphicsObject* targetBlock);

    ~GroundEnemiesObject();
};

