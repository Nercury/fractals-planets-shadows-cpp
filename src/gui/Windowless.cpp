#include "Windowless.h"

Windowless::Windowless(void)
{
	this->x = 0;
	this->y = 0;
	this->width = 100;
	this->height = 100;
	this->handle = new_glgui_handle();
	this->gui = NULL;
}

Windowless::~Windowless(void)
{
	this->gui = NULL;
}

void Windowless::Initialize() {}
void Windowless::Terminate() {}

void Windowless::Move(int32_t x, int32_t y)
{
	this->x = x;
	this->y = y;
}

void Windowless::Resize(int32_t width, int32_t height)
{
	this->width = width;
	this->height = height;
}

void Windowless::SetWidth(int32_t width)
{
	this->width = width;
}

void Windowless::SetHeight(int32_t height)
{
	this->height = height;
}

void Windowless::Render(boost::posix_time::time_duration delta)
{
	glEnable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glColor4f(0.8f, 0.5f, 0.5f, 0.6f);
	glBegin(GL_QUAD_STRIP);
	glVertex2i(0, 0);
	glVertex2i(0, (GLint)this->height);
	glVertex2i((GLint)this->width, 0);
	glVertex2i((GLint)this->width, (GLint)this->height);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

bool Windowless::OnKeyUp(SDL_Event* ev)
{
	return false;
}

bool Windowless::OnKeyDown(SDL_Event* ev)
{
	return false;
}

bool Windowless::OnMouseUp(SDL_Event* ev, int32_t x, int32_t y)
{
	return false;
}

bool Windowless::OnMouseDown(SDL_Event* ev, int32_t x, int32_t y)
{
	return false;
}

bool Windowless::OnMouseMove(SDL_Event* ev, int32_t x, int32_t y)
{
	l("Mouse x: ", x, L_INFO);
	l("Mouse y: ", y, L_INFO);
	return false;
}

void Windowless::OnMouseOver()
{
}

void Windowless::OnMouseOut()
{
}
