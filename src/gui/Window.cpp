#include "Window.h"

#include "Gui.h"
#include "GuiLayer.h"

MWindow::MWindow()
{
	events = NULL;
}

MWindow::~MWindow()
{

}

void MWindow::Close()
{
	if (guiLayer != NULL)
	{
		guiLayer->RemoveWindow(this);
	}
	else
		l("Error - can't close window because guiLayer object is not assigned.", L_ERROR);
}

void MWindow::Render(boost::posix_time::time_duration delta)
{
	glEnable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glColor4f(0.5f, 0.5f, 0.8f, 0.3f);
	glBegin(GL_QUAD_STRIP);
	glVertex2i(0, 0);
	glVertex2i(0, (GLint)this->height);
	glVertex2i((GLint)this->width, 0);
	glVertex2i((GLint)this->width, (GLint)this->height);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	Container::Render(delta);
}

bool MWindow::OnMouseDown(SDL_Event* ev, int32_t x, int32_t y)
{
	BringToTop();
	return Container::OnMouseDown(ev, x, y);
}