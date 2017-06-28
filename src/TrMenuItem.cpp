#include "TrMenuItem.h"

void TrMenuItem::Initialize()
{
	if (text_obj.empty())
	{
		text_obj.put(new GLST_Text(FullPathTo("fonts/FreeMonoBold.ttf"), 12, GLST_Middle_Center));
	}
	text_obj.o()->SetText(text);
	width = (int32_t)text_obj.o()->Width() + 10;
}

void TrMenuItem::SetText(std::string text)
{
	this->text = text;
	text_obj.o()->SetText(text);
	width = (int32_t)text_obj.o()->Width() + 20;
}

void TrMenuItem::OnMouseOver()
{
	mouseOver = true;
	mouseOverFade = 1.0;
}

void TrMenuItem::OnMouseOut()
{
	mouseOver = false;
}

bool TrMenuItem::OnMouseUp(SDL_Event* ev, int32_t x, int32_t y)
{
	if (mouseOver)
	{
		if (onClick != NULL)
			onClick(this);
		return true;
	}
	return false;
}

bool TrMenuItem::OnMouseDown(SDL_Event* ev, int32_t x, int32_t y)
{
	if (mouseOver)
	{
		return true;
	}
	return false;
}

void TrMenuItem::Render(boost::posix_time::time_duration delta)
{
	if (mouseOverFade > 0.0 && !mouseOver)
	{
		mouseOverFade -= delta.total_milliseconds() / 1000.0f;
		if (mouseOverFade < 0.0)
			mouseOverFade = 0;
	}

	glEnable(GL_BLEND);

	glDisable(GL_TEXTURE_2D);
	glColor4f(0.3f, 0, 0, 0.1f + 0.3f * mouseOverFade);
	glBegin(GL_QUAD_STRIP);
	glVertex2i(0, 0);
	glVertex2i(0, (GLint)this->height);
	glVertex2i((GLint)this->width, 0);
	glVertex2i((GLint)this->width, (GLint)this->height);
	glEnd();
	glEnable(GL_TEXTURE_2D);

	text_obj.o()->SetColor(0.15f, 0.15f, 0.15f);
	text_obj.o()->Render(width / 2 + 1, height / 2 + 1);
	text_obj.o()->SetColor(1, 1, 1);
	text_obj.o()->Render(width / 2, height / 2);

	glDisable(GL_BLEND);
}