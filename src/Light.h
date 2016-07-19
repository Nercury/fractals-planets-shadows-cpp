#pragma once

#include "sdlgl.h"
#include "math/Vector.h"
#include "WorldObject.h"

class Light
	: public WorldObject
{
private:
	Vector3f zeroVector;
public:
	bool directional;
	float farDistance;
	float cutOff;
	int index;
	Vector3f color;
	Light();
	Light(int index, Vector3f position, Quaternionf rotation);
	virtual ~Light();
	virtual void Render();
	virtual void BeginScene();
	virtual void EndScene();
};