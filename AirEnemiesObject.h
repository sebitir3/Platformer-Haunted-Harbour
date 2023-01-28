#pragma once
#include "EnemyObject.h"
#include <math.h>
#include "PlayerObject.h"
#include "GreenBulletObject.h"

class AirEnemiesObject :
    public EnemyObject
{
public:
    AirEnemiesObject(PlayerObject* viktor, int centreX, int centreY);
    int previousX, previousY;
    int radius, centreX, centreY;
    int coolDown = 0;
    double angle;

    bool isExploding;

    PlayerObject* viktor;

    void Move();
    void MoveRight();
    void MoveLeft();

    void Death();

    void OnHit(BulletObject* bulletHitBy);

    void BlockCollision(GraphicsObject* targetBlock);

    void ShootPlayer();

    ~AirEnemiesObject();
};

