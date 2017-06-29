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
	virtual ~Light() override ;
	virtual void Render() override ;
	virtual void BeginScene() override ;
	virtual void EndScene() override ;
};