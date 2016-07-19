#include "Surface.h"

Surface::Surface(void)
	: size(Vector2f())
{

}

Surface::Surface(Vector3f position, Quaternionf rotation, Vector2f size)
	: WorldObject(position, rotation), size(size)
{

}

Surface::~Surface(void)
{

}

void Surface::Render()
{
	WorldObject::Render();
	bool can_render = false;
	if (!shader.empty() && shader.o()->enabled)
	{
		if (!texture.empty())
		{
			if (!glIsTexture(texture.o()->Get()))
			{
				std::cout << "Invalid texture" << std::endl;
			}
			shader.o()->BindTexture("texture", 0, texture.o()->Get());
			can_render = true;
		}
		shader.o()->Use();
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
	if (can_render)
	{
		auto width = texture.o()->Width();
		auto height = texture.o()->Height();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUAD_STRIP);

		glTexCoord2f(0, size.y / (GLfloat)height);
		glNormal3f(0,0,1);
		glVertex3f(0, size.y,0);

		glTexCoord2f(0, 0);
		glNormal3f(0,0,1);
		glVertex3f(0,0,0);

		glTexCoord2f(size.x / (GLfloat)width, size.y / (GLfloat)height);
		glNormal3f(0,0,1);
		glVertex3f(size.x, size.y,0);

		glTexCoord2f(size.x / (GLfloat)width, 0);
		glNormal3f(0,0,1);
		glVertex3f(size.x, 0,0);

		glEnd();

		/*glDisable(GL_LIGHTING);
		glUseProgramObjectARB(0);

		glBegin(GL_LINES);
		glVertex3f(0, 0,0); glVertex3f(0, 0, 30);
		glVertex3f(0, size.y,0);glVertex3f(0, size.y, 30);
		glVertex3f(size.x, 0,0);glVertex3f(size.x, 0, 30);
		glVertex3f(size.x, size.y,0);glVertex3f(size.x, size.y, 30);
		glEnd();

		glEnable(GL_LIGHTING);*/
	}
}