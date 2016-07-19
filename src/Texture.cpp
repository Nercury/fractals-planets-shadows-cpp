#include "Texture.h"

Texture::Texture(p<TextureManager> manager, std::string path)
	: manager(manager), path(path)
{
	bind_on_render = true;
	manager.o()->MapFileTexture(texture, path, width, height);
}

Texture::~Texture(void)
{
	this->manager.o()->RemoveTexture(path, texture);
}

void Texture::RenderPart(GLint sx, GLint sy, GLint w, GLint h)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	if (bind_on_render)
		glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUAD_STRIP);

	glTexCoord2f(sx / (GLfloat)width, 1.0f - sy / (GLfloat)height);
	glVertex2i(0, 0);

	glTexCoord2f(sx / (GLfloat)width, 1.0f - (sy + h) / (GLfloat)height);
	glVertex2i(0, h);

	glTexCoord2f((sx + w) / (GLfloat)width, 1.0f - sy / (GLfloat)height);
	glVertex2i(w, 0);

	glTexCoord2f((sx + w) / (GLfloat)width, 1.0f - (sy + h) / (GLfloat)height);
	glVertex2i(w, h);
	glEnd();
}

void Texture::RenderPartScaled(GLint sx, GLint sy, GLint sw, GLint sh, GLint w, GLint h)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	if (bind_on_render)
		glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUAD_STRIP);

	glTexCoord2f(sx / (GLfloat)width, 1.0f - sy / (GLfloat)height);
	glVertex2i(0, 0);

	glTexCoord2f(sx / (GLfloat)width, 1.0f - (sy + sh) / (GLfloat)height);
	glVertex2i(0, h);

	glTexCoord2f((sx + sw) / (GLfloat)width, 1.0f - sy / (GLfloat)height);
	glVertex2i(w, 0);

	glTexCoord2f((sx + sw) / (GLfloat)width, 1.0f - (sy + sh) / (GLfloat)height);
	glVertex2i(w, h);
	glEnd();
}

void Texture::RenderPartScaledWithBorder(GLint sx, GLint sy, GLint sw, GLint sh, GLint w, GLint h, GLint bl, GLint bt, GLint br, GLint bb)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	if (bind_on_render)
		glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUAD_STRIP);

	glTexCoord2f(sx / (GLfloat)width, 1.0f - sy / (GLfloat)height);
	glVertex2i(0, 0);
	glTexCoord2f(sx / (GLfloat)width, 1.0f - (sy + bt) / (GLfloat)height);
	glVertex2i(0, bt);

	glTexCoord2f((sx + bl) / (GLfloat)width, 1.0f - sy / (GLfloat)height);
	glVertex2i(bl, 0);
	glTexCoord2f((sx + bl) / (GLfloat)width, 1.0f - (sy + bt) / (GLfloat)height);
	glVertex2i(bl, bt);

	glTexCoord2f((sx + sw - br) / (GLfloat)width, 1.0f - sy / (GLfloat)height);
	glVertex2i(w - br, 0);
	glTexCoord2f((sx + sw - br) / (GLfloat)width, 1.0f - (sy + bt) / (GLfloat)height);
	glVertex2i(w-br, bt);

	glTexCoord2f((sx + sw) / (GLfloat)width, 1.0f - sy / (GLfloat)height);
	glVertex2i(w, 0);
	glTexCoord2f((sx + sw) / (GLfloat)width, 1.0f - (sy + bt) / (GLfloat)height);
	glVertex2i(w, bt);

	glEnd();
	glBegin(GL_QUAD_STRIP);

	glTexCoord2f(sx / (GLfloat)width, 1.0f - (sy + bt) / (GLfloat)height);
	glVertex2i(0, bt);
	glTexCoord2f(sx / (GLfloat)width, 1.0f - (sy + sh - bb) / (GLfloat)height);
	glVertex2i(0, h - bb);

	glTexCoord2f((sx + bl) / (GLfloat)width, 1.0f - (sy + bt) / (GLfloat)height);
	glVertex2i(bl, bt);
	glTexCoord2f((sx + bl) / (GLfloat)width, 1.0f - (sy + sh - bb) / (GLfloat)height);
	glVertex2i(bl, h - bb);

	glTexCoord2f((sx + sw - br) / (GLfloat)width, 1.0f - (sy + bt) / (GLfloat)height);
	glVertex2i(w - br, bt);
	glTexCoord2f((sx + sw - br) / (GLfloat)width, 1.0f - (sy + sh - bb) / (GLfloat)height);
	glVertex2i(w-br, h - bb);

	glTexCoord2f((sx + sw) / (GLfloat)width, 1.0f - (sy + bt) / (GLfloat)height);
	glVertex2i(w, bt);
	glTexCoord2f((sx + sw) / (GLfloat)width, 1.0f - (sy + sh - bb) / (GLfloat)height);
	glVertex2i(w, h - bb);

	glEnd();
	glBegin(GL_QUAD_STRIP);

	glTexCoord2f(sx / (GLfloat)width, 1.0f - (sy + sh - bb) / (GLfloat)height);
	glVertex2i(0, h - bb);
	glTexCoord2f(sx / (GLfloat)width, 1.0f - (sy + sh) / (GLfloat)height);
	glVertex2i(0, h);

	glTexCoord2f((sx + bl) / (GLfloat)width, 1.0f - (sy + sh - bb) / (GLfloat)height);
	glVertex2i(bl, h - bb);
	glTexCoord2f((sx + bl) / (GLfloat)width, 1.0f - (sy + sh) / (GLfloat)height);
	glVertex2i(bl, h);

	glTexCoord2f((sx + sw - br) / (GLfloat)width, 1.0f - (sy + sh - bb) / (GLfloat)height);
	glVertex2i(w - br, h - bb);
	glTexCoord2f((sx + sw - br) / (GLfloat)width, 1.0f - (sy + sh) / (GLfloat)height);
	glVertex2i(w-br, h);

	glTexCoord2f((sx + sw) / (GLfloat)width, 1.0f - (sy + sh - bb) / (GLfloat)height);
	glVertex2i(w, h - bb);
	glTexCoord2f((sx + sw) / (GLfloat)width, 1.0f - (sy + sh) / (GLfloat)height);
	glVertex2i(w, h);

	glEnd();
}

void Texture::Render(GLint w, GLint h)
{
	// switch to current texture
	glColor3f(1.0f, 1.0f, 1.0f);
	if (bind_on_render)
		glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUAD_STRIP);
	glTexCoord2f(0, 1);
	glVertex2i(0, 0);
	glTexCoord2f(0, 0);
	glVertex2i(0, h);
	glTexCoord2f(1, 1);
	glVertex2i(w, 0);
	glTexCoord2f(1, 0);
	glVertex2i(w, h);
	glEnd();
}

void Texture::Render(GLfloat w, GLfloat h)
{
	// switch to current texture
	glColor3f(1.0f, 1.0f, 1.0f);
	if (bind_on_render)
		glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUAD_STRIP);
	glTexCoord2f(0, 1);
	glVertex2f(0, 0);
	glTexCoord2f(0, 0);
	glVertex2f(0, h);
	glTexCoord2f(1, 1);
	glVertex2f(w, 0);
	glTexCoord2f(1, 0);
	glVertex2f(w, h);
	glEnd();
}