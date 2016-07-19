#pragma once

#include "WorldObject.h"
#include "Texture.h"
#include "Shader.h"
#include "safep.hpp"

class Surface :
	public WorldObject
{
public:
	p<Texture> texture;
	p<Shader> shader;
	Vector2f size;
	Surface(void);
	Surface(Vector3f position, Quaternionf rotation, Vector2f size);
	virtual ~Surface(void);
	virtual void Render();
};