#include "TmpCollisionObj.h"

void TmpCollisionObj::Render()
{
	WorldObject::Render();
	if (visible)
	{
		glDisable(GL_LIGHTING);
		glUseProgramObjectARB(0);

		Vector3f half = size / 2;

		glColor3f(0.0f, 1.0f, 0.0f);

		glBegin(GL_LINE_STRIP);
		glVertex3f(half.x,-half.y,-half.z);
		glVertex3f(half.x,-half.y,half.z);
		glVertex3f(half.x,half.y,half.z);
		glVertex3f(half.x,half.y,-half.z);
		glVertex3f(half.x,-half.y,-half.z);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glVertex3f(-half.x,-half.y,-half.z);
		glVertex3f(-half.x,-half.y,half.z);
		glVertex3f(-half.x,half.y,half.z);
		glVertex3f(-half.x,half.y,-half.z);
		glVertex3f(-half.x,-half.y,-half.z);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(-half.x,-half.y,-half.z); glVertex3f(half.x,-half.y,-half.z);
		glVertex3f(-half.x,-half.y,half.z); glVertex3f(half.x,-half.y,half.z);
		glVertex3f(-half.x,half.y,half.z); glVertex3f(half.x,half.y,half.z);
		glVertex3f(-half.x,half.y,-half.z); glVertex3f(half.x,half.y,-half.z);
		glEnd();

		glEnable(GL_LIGHTING);
	}
}