#pragma once
#include "WeaponsObject.h"
#include "PurpleBulletObject.h"

//macros that represent the state of our character
#define MOVERIGHT 1
#define MOVELEFT 2
#define STANDRIGHT 3
#define STANDLEFT 4
#define JUMPRIGHT 5
#define JUMPLEFT 6
#define SHOOTRIGHT 7
#define SHOOTLEFT 8

class PlayerObject : public WeaponsObject
{
public:
	PlayerObject(); //constructor

	int xspeed, yspeed; //speed values

	int currentState; //the current animation/movement state of the player

	bool stoppedRight, stoppedLeft; //distinguishes whether the player should keep moving while it lands

	int previousX, previousY; //the position values RIGHT BEFORE you add the speed

	void Move(); //moves our player

	void SetMoveRight(); //sets the speed and the animation for our player
	void SetStandingRight(); //the animation for our player when standing

	void SetMoveLeft();
	void SetStandingLeft();

	void ShootingRight(); 
	void ShootingLeft();

	void JumpingRight();
	void JumpingLeft();

	void PlayerBlockCollision(GraphicsObject *targetBlock);

	void OnHit(BulletObject* bulletHitBy);

	bool IsJumping();

	~PlayerObject(); //destructor
};

