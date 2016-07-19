#include "Sphere.h"

void Sphere::PutSphere(GLfloat radius, GLint detail)
{
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluSphere(quadratic, radius, detail, detail);
	glPopMatrix();
}

Sphere::Sphere()
	: radius(128)
{
}

Sphere::~Sphere()
{
}

void Sphere::Render()
{
	WorldObject::Render();
	bool can_render = false;
	if (!shader.empty() && shader.o()->enabled)
	{
		shader.o()->Use();
		if (!texture.empty())
		{
			if (!glIsTexture(texture.o()->Get()))
			{
				std::cout << "Invalid texture" << std::endl;
			}
			shader.o()->BindTexture("texture", 0, texture.o()->Get());
			can_render = true;
		}
	}
	else
	{
		glUseProgramObjectARB(0);
		if (!texture.empty())
		{
			glBindTexture(GL_TEXTURE_2D, texture.o()->Get());
			can_render = true;
		}
	}
	quadratic = gluNewQuadric();			// Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(quadratic, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
	gluQuadricTexture(quadratic, GL_TRUE);		// Create Texture Coords ( NEW )
	PutSphere(radius, 50);
	gluDeleteQuadric(quadratic);
}