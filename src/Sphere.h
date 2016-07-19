#pragma once

#include "Texture.h"
#include "Shader.h"
#include "WorldObject.h"

class Sphere
	: public WorldObject
{
private:
	GLUquadricObj * quadratic;
	void PutSphere(GLfloat radius, GLint detail);
public:
	p<Texture> texture;
	p<Shader> shader;
	float radius;
	Sphere();
	virtual ~Sphere();
	virtual void Render();
};