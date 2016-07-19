#pragma once

#include "sdlgl.h"

#include "WorldObject.h"

class TmpCollisionObj
	: public WorldObject
{
public:
	Vector3f size;
	bool visible;
	TmpCollisionObj() : size(Vector3f(0,0,0)), visible(false) {};
	TmpCollisionObj(Vector3f size) : size(size), visible(false) {};
	~TmpCollisionObj() {};
	virtual void Render();
};