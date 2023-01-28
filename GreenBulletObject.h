#pragma once
#include "BulletObject.h"
class GreenBulletObject :
    public BulletObject
{
public :
    GreenBulletObject();

    void SetExploding();
    void Reset();

    ~GreenBulletObject();
};

