#include "Light.h"

#include <iostream>

using namespace std;

Light::Light()
	: WorldObject(), index(0), directional(false), farDistance(2000.0f), color(Vector3f(1,1,1)), zeroVector(0,0,0), cutOff(45)
{
}

Light::Light(int index, Vector3f position, Quaternionf rotation)
	: WorldObject(position, rotation), index(index), directional(false), farDistance(2000.0f), color(Vector3f(1,1,1)), zeroVector(0,0,0), cutOff(45)
{
}

Light::~Light()
{
}

void Light::Render()
{
	WorldObject::Render();
	glDisable(GL_LIGHTING);
	glUseProgramObjectARB(0);
	glColor3f(color.x,color.y,color.z);
	if (directional)
	{
		glBegin(GL_LINE_STRIP);
		glVertex3f(0,0,0);	glVertex3f(0,0,60);
		glEnd();
	}
	else
	{
		glBegin(GL_LINES);
		glVertex3f(-30,0,0);	glVertex3f(30,0,0);
		glVertex3f(0,-30,0);	glVertex3f(0,30,0);
		glVertex3f(0,0,-30);	glVertex3f(0,0,30);
		glEnd();
	}
	glEnable(GL_LIGHTING);
}

void Light::BeginScene() 
{ 
	glEnable(GL_LIGHT0 + index); 
	glLightfv(GL_LIGHT0 + index, GL_POSITION, Vector4f(position.x, position.y, position.z, 1.0f).asMatrix().element); 
	glLightfv(GL_LIGHT0 + index, GL_DIFFUSE, color.asMatrix().element);
	glLightfv(GL_LIGHT0 + index, GL_AMBIENT, Vector3f(0.01f,0.01f,0.01f).asMatrix().element);
	glLightf(GL_LIGHT0 + index, GL_LINEAR_ATTENUATION, 1.0 / farDistance);
	if (directional)
	{
		Matrix4f m;
		rotation.to4x4Matrix(&m);
		Vector3f transformed = Vector3f(0, 0, 1.0f).transform(m);
		//cout << transformed.x << "," << transformed.y << "," << transformed.z << endl;
		glLightfv(GL_LIGHT0 + index, GL_SPOT_DIRECTION, transformed.asMatrix().element); 
		glLightf(GL_LIGHT0 + index, GL_SPOT_CUTOFF, cutOff);
	}
	else
	{
		//glLightfv(GL_LIGHT0 + index, GL_SPOT_DIRECTION, zeroVector.asMatrix().element); 
		glLightf(GL_LIGHT0 + index, GL_SPOT_CUTOFF, 0.0f);
	}
}

void Light::EndScene()
{
	glDisable(GL_LIGHT0 + index);
}