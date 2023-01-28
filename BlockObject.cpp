#include "BlockObject.h"

BlockObject::BlockObject() : GraphicsObject("Pics/Crate.bmp", 300, 336, 64, 64)
{
	width = 64;
	height = 64;
	hitWidth = width;
	hitHeight = height;
}

BlockObject::~BlockObject()
{
}
