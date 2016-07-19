#include "WrlModel.h"

void WrlModel::Render()
{
	WorldObject::Render();
	bool can_render = false;
	bool has_texture = false;
	if (!shader.empty() && shader.o()->enabled)
	{
		if (!texture.empty())
		{
			if (!glIsTexture(texture.o()->Get()))
			{
				std::cout << "Invalid texture" << std::endl;
			}
			has_texture = true;
			shader.o()->BindTexture("texture", 0, texture.o()->Get());
		}
		can_render = true;
		shader.o()->Use();
	}
	else
	{
		glUseProgramObjectARB(0);
		if (!texture.empty())
		{
			glBindTexture(GL_TEXTURE_2D, texture.o()->Get());
			has_texture = true;
		}
		can_render = true;
	}
	if (can_render)
	{
		if (!has_texture)
		{
			glDisable(GL_TEXTURE_2D);
		}
		wScalef(200,200,200);

		Vector3f normal;

		bool begin = true;
		for (auto it = indexes.begin(); it != indexes.end(); ++it)
		{
			if (*it == -1)
			{
				glEnd();
				begin = true;
			}
			else
			{
				Vector3f point = points.at(*it);
				Vector3f color = colors.at(colorIndexes.at(*it));

				if (begin)
				{
					Vector3f next1 = points.at(*(it + 1));
					Vector3f next2 = points.at(*(it + 2));
					ComputeFaceNormal(point, next1, next2, normal);
					glBegin(GL_TRIANGLE_FAN);
					begin = false;
				}

				//glTexCoord2f(u0, v0);
				glNormal3f(normal.x, normal.y, normal.z);
				glColor3f(color.x, color.y, color.z);
				glVertex3f(point.x,point.y,point.z);
			}
		}
		if (!has_texture)
		{
			glEnable(GL_TEXTURE_2D);
		}
	}
}