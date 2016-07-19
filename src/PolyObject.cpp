#include "PolyObject.h"

void PolyObject::Render()
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
		glScalef(500,500,500);
		if (func1 != NULL)
		{		
			auto width = texture.o()->Width();
			auto height = texture.o()->Height();
			glColor3f(1.0f, 1.0f, 1.0f);

			glBegin(GL_QUADS);

			int density = 3;


			float u0, v0, u1, v1;
			Vector3f u0v0, u0v1, u1v0, u1v1;
			for (int ui = 0; ui < density; ui++)
			{
				u0 = ui / (float)density;
				u1 = (ui + 1) / (float)density;
				for (int vi = 0; vi < density; vi++)
				{
					v0 = vi / (float)density;
					v1 = (vi + 1) / (float)density;
					
					func1(u0,v0,u0v0.x,u0v0.y,u0v0.z);
					func1(u1,v0,u1v0.x,u1v0.y,u1v0.z);
					func1(u0,v1,u0v1.x,u0v1.y,u0v1.z);
					func1(u1,v1,u1v1.x,u1v1.y,u1v1.z);

					Vector3f normal;
					ComputeFaceNormal(u0v0, u1v0, u0v1, normal);

					glTexCoord2f(u0, v1);
					glNormal3f(normal.x, normal.y, normal.z);
					glVertex3f(u0v1.x,u0v1.y,u0v1.z);

					glTexCoord2f(u0, v0);
					glNormal3f(normal.x, normal.y, normal.z);
					glVertex3f(u0v0.x,u0v0.y,u0v0.z);

					glTexCoord2f(u1, v0);
					glNormal3f(normal.x, normal.y, normal.z);
					glVertex3f(u1v0.x,u1v0.y,u1v0.z);

					glTexCoord2f(u1, v1);
					glNormal3f(normal.x, normal.y, normal.z);
					glVertex3f(u1v1.x,u1v1.y,u1v1.z);
				}
			}

			glEnd();
		}
		if (func2 != NULL)
		{		
			auto width = texture.o()->Width();
			auto height = texture.o()->Height();
			glColor3f(1.0f, 1.0f, 1.0f);

			glBegin(GL_QUADS);

			int density = 30;


			float u0, v0, u1, v1;
			Vector3f u0v0, u0v1, u1v0, u1v1;
			for (int ui = 0; ui < density; ui++)
			{
				u0 = ui / (float)density;
				u1 = (ui + 1) / (float)density;
				for (int vi = 0; vi < density; vi++)
				{
					v0 = vi / (float)density;
					v1 = (vi + 1) / (float)density;
					
					func2(u0,v0,u0v0.x,u0v0.y,u0v0.z);
					func2(u1,v0,u1v0.x,u1v0.y,u1v0.z);
					func2(u0,v1,u0v1.x,u0v1.y,u0v1.z);
					func2(u1,v1,u1v1.x,u1v1.y,u1v1.z);

					Vector3f normal;
					ComputeFaceNormal(u0v0, u1v0, u0v1, normal);

					glTexCoord2f(u0, v1);
					glNormal3f(normal.x, normal.y, normal.z);
					glVertex3f(u0v1.x,u0v1.y,u0v1.z);

					glTexCoord2f(u0, v0);
					glNormal3f(normal.x, normal.y, normal.z);
					glVertex3f(u0v0.x,u0v0.y,u0v0.z);

					glTexCoord2f(u1, v0);
					glNormal3f(normal.x, normal.y, normal.z);
					glVertex3f(u1v0.x,u1v0.y,u1v0.z);

					glTexCoord2f(u1, v1);
					glNormal3f(normal.x, normal.y, normal.z);
					glVertex3f(u1v1.x,u1v1.y,u1v1.z);
				}
			}

			glEnd();
		}
		if (func3 != NULL)
		{		
			auto width = texture.o()->Width();
			auto height = texture.o()->Height();
			glColor3f(1.0f, 1.0f, 1.0f);

			glBegin(GL_QUADS);

			int density = 30;


			float u0, v0, u1, v1;
			Vector3f u0v0, u0v1, u1v0, u1v1;
			for (int ui = 0; ui < density; ui++)
			{
				u0 = ui / (float)density;
				u1 = (ui + 1) / (float)density;
				for (int vi = 0; vi < density; vi++)
				{
					v0 = vi / (float)density;
					v1 = (vi + 1) / (float)density;
					
					func3(u0,v0,u0v0.x,u0v0.y,u0v0.z);
					func3(u1,v0,u1v0.x,u1v0.y,u1v0.z);
					func3(u0,v1,u0v1.x,u0v1.y,u0v1.z);
					func3(u1,v1,u1v1.x,u1v1.y,u1v1.z);

					Vector3f normal;
					ComputeFaceNormal(u0v0, u1v0, u0v1, normal);

					glTexCoord2f(u0, v1);
					glNormal3f(normal.x, normal.y, normal.z);
					glVertex3f(u0v1.x,u0v1.y,u0v1.z);

					glTexCoord2f(u0, v0);
					glNormal3f(normal.x, normal.y, normal.z);
					glVertex3f(u0v0.x,u0v0.y,u0v0.z);

					glTexCoord2f(u1, v0);
					glNormal3f(normal.x, normal.y, normal.z);
					glVertex3f(u1v0.x,u1v0.y,u1v0.z);

					glTexCoord2f(u1, v1);
					glNormal3f(normal.x, normal.y, normal.z);
					glVertex3f(u1v1.x,u1v1.y,u1v1.z);
				}
			}

			glEnd();
		}
	}
}