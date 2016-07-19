#include "Container.h"

using namespace std;

Container::Container()
{
	mouse_down_child = GLGUI_INVALID_HANDLE;
}

Container::~Container()
{

}

void Container::Add(p<Windowless> w)
{
	WHandle handle = w.o()->Handle();
	auto it = childs.left.find(handle);
	if (it == childs.left.end())
	{
		w.o()->__setGui(gui);
		w.o()->__setGuiLayer(guiLayer);
		childs.left.insert(pair<WHandle,p<Windowless>>(handle, w));
		tabOrder.left.insert(pair<WHandle, int32_t>(handle, 0));
		w.o()->Initialize();
	}
}

bool Container::Remove(p<Windowless> w)
{
	w.o()->__setGui(NULL);
	w.o()->__setGuiLayer(NULL);
	auto mapit = childs.left.find(w.o()->Handle());
	if (mapit != childs.left.end())
	{
		childs.left.erase(mapit);
		tabOrder.left.erase(tabOrder.left.find(w.o()->Handle()));
		w.o()->Terminate();
		return true;
	} else return false;
}

void Container::Render(boost::posix_time::time_duration delta)
{
	GLfloat prevx = 0, prevy = 0;

	glPushMatrix();

	Windowless * item;
	GLfloat x; GLfloat y;
	for (auto it = childs.right.begin(), iend = childs.right.end(); it != iend; ++it)
	{
		item = it->first.o();
		x = (GLfloat)item->X();
		y = (GLfloat)item->Y();
		glTranslatef(x - prevx, y - prevy, 0);
		item->Render(delta);
		prevx = x;
		prevy = y;
	}

	glPopMatrix();
}

bool Container::OnKeyUp(SDL_Event* ev)
{
	return false;
}

bool Container::OnKeyDown(SDL_Event* ev)
{
	return false;
}

bool Container::OnMouseUp(SDL_Event* ev, int32_t x, int32_t y)
{
	if (mouse_down_child != GLGUI_INVALID_HANDLE)
	{
		auto it = childs.left.find(mouse_down_child);
		mouse_down_child = GLGUI_INVALID_HANDLE;
		if (it != childs.left.end())
		{
			return it->second.o()->OnMouseUp(ev, x - it->second.o()->X(), y - it->second.o()->Y());
		}
	}
	return false;
}

bool Container::OnMouseDown(SDL_Event* ev, int32_t x, int32_t y)
{
	int32_t ix, iy, w, h;
	Windowless * item;
	for (auto it = childs.right.rbegin(), iend = childs.right.rend(); it != iend; ++it)
	{
		item = it->first.o();
		ix = item->X();
		iy = item->Y();
		w = item->Width();
		h = item->Height();
		if (x >= ix && x < ix + w && y >= iy && y < iy + h)
		{
			mouse_down_child = it->second;
			return item->OnMouseDown(ev, x - ix, y - iy);
		}
	}
	return false;
}

bool Container::OnMouseMove(SDL_Event* ev, int32_t x, int32_t y)
{
	if (mouse_down_child == GLGUI_INVALID_HANDLE)
	{
		int32_t ix, iy, w, h;
		Windowless * item;
		for (auto it = childs.right.rbegin(), iend = childs.right.rend(); it != iend; ++it)
		{
			item = it->first.o();
			ix = item->X();
			iy = item->Y();
			w = item->Width();
			h = item->Height();
			if (x >= ix && x < ix + w && y >= iy && y < iy + h)
			{
				return item->OnMouseMove(ev, x - ix, y - iy);
			}
		}
	}
	else
	{
		auto it = childs.left.find(mouse_down_child);
		if (it != childs.left.end())
		{
			return it->second.o()->OnMouseMove(ev, x - it->second.o()->X(), y - it->second.o()->Y());
		}
	}
	return false;
}

void Container::OnMouseOver()
{
}

void Container::OnMouseOut()
{
}

WHandle Container::RealMousePosition(int32_t x, int32_t y)
{
	return GLGUI_INVALID_HANDLE;
}