#include "DecoratedWindow.h"

#include <sstream>

using namespace std;

DecoratedWindow::DecoratedWindow(void)
{
	title_text = NULL;
	overButton = false;
	downButton = false;
	down = false;
	downResize = false;
}

DecoratedWindow::~DecoratedWindow(void)
{
}

void DecoratedWindow::Initialize()
{
	texture = gui->theme->GetTexture("gui/window_baked.png");
	title_text = new GLST_Text(FullPathTo("fonts/FreeMonoBold.ttf"), 12, GLST_Middle_Center);
	ostringstream ss;
	ss << "Yay, my window " << handle << "!";
	title_text->SetText(ss.str());
}

void DecoratedWindow::Terminate()
{
	delete title_text;
	title_text = NULL;
}

void DecoratedWindow::Render(boost::posix_time::time_duration delta)
{
	glEnable(GL_BLEND);
	texture.o()->RenderPartScaledWithBorder(0, 0, 413, 303, this->width, this->height, 19, 33, 19, 13);
	glPushMatrix();
	glTranslated(this->width - 55, 7, 0);
	if (downButton)
	{
		texture.o()->RenderPart(413, 50, 47,26);
	}
	else if (overButton)
	{
		texture.o()->RenderPart(413, 25, 47,26);
	}
	else
	{
		texture.o()->RenderPart(413, 0, 47,26);
	}
	glPopMatrix();
	title_text->SetColor(1, 1, 1);
	title_text->Render(width / 2 + 1, 21);
	title_text->SetColor(0.15f, 0.15f, 0.15f);
	title_text->Render(width / 2, 20);
	glDisable(GL_BLEND);
	Container::Render(delta);
}

bool DecoratedWindow::OnMouseUp(SDL_Event* ev, int32_t x, int32_t y)
{
	down = false;
	downResize = false;
	if (overButton && downButton)
	{
		Close();
	}
	downButton = false;
	return MWindow::OnMouseUp(ev, x, y);
}

bool DecoratedWindow::OnMouseDown(SDL_Event* ev, int32_t x, int32_t y)
{
	if (overButton)
	{
		downButton = true;
		return true;
	}
	else if (x > width - 30 && y > height - 30)
	{
		downResize = true;
		return true;
	}
	else if (y < 35)
	{
		down = true;
		return true;
	}
	else return MWindow::OnMouseDown(ev, x, y);
}

bool DecoratedWindow::OnMouseMove(SDL_Event* ev, int32_t x, int32_t y)
{
	if (x > this->width - 58 && y < 35)
	{
		if (x > this->width - 52 && x < this->width - 52 + 38 && y > 9 && y < 27)
		{
			overButton = true;
		}
		else
		{
			overButton = false;
		}
		return true;
	}
	else if (down)
	{
		this->x += ev->motion.xrel;
		this->y += ev->motion.yrel;
		downResize = false;
		return true;
	}
	else if (downResize)
	{
		this->width += ev->motion.xrel;
		this->height += ev->motion.yrel;
		down = false;
		return true;
	}
	else
		return MWindow::OnMouseMove(ev, x, y);
}