#pragma once
#include "BulletObject.h"
class PurpleBulletObject :
    public BulletObject
{ 
public :
    PurpleBulletObject();

    void SetExploding();
    void Reset();

    ~PurpleBulletObject();
};

