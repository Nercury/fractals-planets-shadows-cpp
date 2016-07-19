#include "TrMenu.h"

TrMenu::TrMenu()
	: mouse_over_handle(GLGUI_INVALID_HANDLE)
{
	
}

TrMenu::~TrMenu()
{

}

void TrMenu::Terminate()
{
	Windowless * item;
	for (auto it = childs.right.begin(), iend = childs.right.end(); it != iend; ++it)
	{
		item = it->first.o();
		auto mnuItem = dynamic_cast<TrMenuItem*>(item);
		if (mnuItem != NULL)
		{
			mnuItem->Reset();
		}
	}
}

void TrMenu::Render(boost::posix_time::time_duration delta)
{
	Window::Render(delta);

	glPushMatrix();

	Windowless * item;

	glTranslatef(5, 5, 0);
	int32_t x; int32_t y;
	x = 5;
	y = 5;
	for (auto it = childs.right.begin(), iend = childs.right.end(); it != iend; ++it)
	{
		item = it->first.o();
		item->Render(delta);
		item->Move(x, y);
		item->SetHeight(height - 10);
		glTranslatef((GLfloat)item->Width() + 5, 0, 0);
		x += item->Width() + 5;
	}

	glPopMatrix();
}

bool TrMenu::OnMouseMove(SDL_Event* ev, int32_t x, int32_t y)
{
	Windowless * item;
	WHandle resetHandle = GLGUI_INVALID_HANDLE;
	bool foundWindow = false;
	for (auto it = childs.right.begin(), iend = childs.right.end(); it != iend; ++it)
	{
		item = it->first.o();
		if (x > item->X() && y > item->Y() && x < item->X() + item->Width() && y < item->Y() + item->Height())
		{
			foundWindow = true;
			if (mouse_over_handle != item->Handle())
			{
				if (mouse_over_handle != GLGUI_INVALID_HANDLE)
				{
					resetHandle = mouse_over_handle;
				}
				mouse_over_handle = item->Handle();
				item->OnMouseOver();
			}
			break;
		}
	}
	if (!foundWindow)
	{
		resetHandle = mouse_over_handle;
		mouse_over_handle = GLGUI_INVALID_HANDLE;
	}
	if (resetHandle != GLGUI_INVALID_HANDLE)
	{
		for (auto it = childs.right.begin(), iend = childs.right.end(); it != iend; ++it)
		{
			item = it->first.o();
			if (item->Handle() == resetHandle)
			{
				item->OnMouseOut();
				break;
			}
		}
	}
	return false;
}