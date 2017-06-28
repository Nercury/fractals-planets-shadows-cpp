#include "GuiLayer.h"

using namespace std;

GuiLayer::GuiLayer(GuiBase * gui, boost::function<void ()> layerActivateFunction, boost::function<void ()> layerDeactivateFunction, boost::function<void ()> mouseGrabFunction, boost::function<void ()> mouseUngrabFunction)
	: gui(gui), LayerActivateFunction(layerActivateFunction), LayerDeactivateFunction(layerDeactivateFunction), MouseGrabFunction(mouseGrabFunction), MouseUngrabFunction(mouseUngrabFunction), width(0), height(0)
{
	this->gui = gui;
	is_active = false;
	mouse_window_handle = 0;
}

GuiLayer::GuiLayer(GuiBase * gui, boost::function<void ()> layerActivateFunction, boost::function<void ()> layerDeactivateFunction, boost::function<void ()> mouseGrabFunction, boost::function<void ()> mouseUngrabFunction, int32_t width, int32_t height)
	: gui(gui), LayerActivateFunction(layerActivateFunction), LayerDeactivateFunction(layerDeactivateFunction), MouseGrabFunction(mouseGrabFunction), MouseUngrabFunction(mouseUngrabFunction), width(width), height(height)
{
	this->gui = gui;
	is_active = false;
	mouse_window_handle = 0;
}

GuiLayer::~GuiLayer()
{

}

void GuiLayer::SetSize(int32_t width, int32_t height)
{
	this->width = width;
	this->height = height;
}

void GuiLayer::Activate()
{
	is_active = true;
}

void GuiLayer::Deactivate()
{
	is_active = false;
}

void GuiLayer::UngrabMouse()
{
	if (MouseUngrabFunction)
		MouseUngrabFunction();
}

void GuiLayer::RemoveWindow(WHandle handle)
{
	this->windowRemoveQueue.push(handle);
}

void GuiLayer::DoPendingWindowRemove()
{
	if (!windowRemoveQueue.empty())
	{
		set<WHandle> removeSet;
		do
		{
			auto handle = windowRemoveQueue.front();
			windowRemoveQueue.pop();
			removeSet.insert(handle);
		} while (!windowRemoveQueue.empty());
		for (auto handleIt = removeSet.begin(); handleIt != removeSet.end(); ++handleIt)
		{
			for (auto it = windows.begin(); it != windows.end(); ++it)
			{
				if (it->o()->Handle() == (*handleIt))
				{
					it->o()->__setGui(NULL);
					it->o()->__setGuiLayer(NULL);
					it->o()->SetEventHandler(NULL);
					it->o()->Terminate();
					windows.erase(it);
					if (windows.empty())
						if (LayerDeactivateFunction)
							LayerDeactivateFunction();
					break;
				}
			}
		}
	}
}

void GuiLayer::RemoveWindow(MWindow * window)
{
	RemoveWindow(window->Handle());
}

void GuiLayer::RemoveWindow(p<MWindow> window)
{
	RemoveWindow(window.o());
}

void GuiLayer::DoWindowRemoveByHandle(WHandle handle)
{
	for (auto it = windows.begin(); it != windows.end(); ++it)
	{
		if (it->o()->Handle() == handle)
		{
			it->o()->__setGui(NULL);
			it->o()->__setGuiLayer(NULL);
			it->o()->SetEventHandler(NULL);
			it->o()->Terminate();
			windows.erase(it);
			if (windows.empty())
				if (LayerDeactivateFunction)
					LayerDeactivateFunction();
			break;
		}
	}
}

void GuiLayer::AddWindow(p<MWindow> window)
{
	DoWindowRemoveByHandle(window.o()->Handle());
	windows.push_back(window);
	window.o()->__setGui(this->gui);
	window.o()->__setGuiLayer(this);
	window.o()->SetEventHandler(this);
	window.o()->Initialize();
	if (LayerActivateFunction)
		LayerActivateFunction();
}

void GuiLayer::Render(boost::posix_time::time_duration delta)
{
	DoPendingWindowRemove();

	GLfloat prevx = 0, prevy = 0;

	glPushMatrix();

	MWindow * item;
	GLfloat x, y;
	int i = 0;
	for (auto it = windows.begin(); it != windows.end(); ++it)
	{
		item = it->o();
		x = (GLfloat)item->X();
		y = (GLfloat)item->Y();
		glTranslatef(x - prevx, y - prevy, 0);
		item->Render(delta);
		/*if (i == windows.size() - 1 && this->is_active)
		{
			glColor3f(0.9f, 0.0f, 0.0f);
			glBegin(GL_LINE_STRIP);
			glVertex2i(0, 0);
			glVertex2i(0, (GLint)item->Height());
			glVertex2i((GLint)item->Width(), (GLint)item->Height());
			glVertex2i((GLint)item->Width(), 0);
			glVertex2i(0, 0);
			glEnd();
		}*/
		prevx = x;
		prevy = y;
		i++;
	}

	glPopMatrix();
}

/* window events */

void GuiLayer::OnBringWindowToTop(WHandle handle)
{
	p<MWindow> window;
	for (auto it = windows.begin(); it != windows.end(); ++it)
	{
		if (it->o()->Handle() == handle)
		{
			window = (*it);
			windows.erase(it);
			break;
		}
	}
	if (!window.empty())
	{
		windows.push_back(window);
	}
}

bool GuiLayer::OnKeyUp(SDL_Event* ev)
{
	if (HasWindows())
	{
		windows.front().o()->OnKeyUp(ev);
	}
	return false;
}

bool GuiLayer::OnKeyDown(SDL_Event* ev)
{
	if (HasWindows())
	{
		windows.front().o()->OnKeyDown(ev);
	}
	return false;
}

bool GuiLayer::OnMouseUp(SDL_Event* ev)
{
	bool result = false;
	UngrabMouse();
	if (mouse_window_handle != 0)
	{
		MWindow * item;
		for (auto it = windows.rbegin(); it != windows.rend(); ++it)
		{
			item = it->o();
			if (item->Handle() == mouse_window_handle)
			{
				result = item->OnMouseUp(ev, ((int32_t)ev->button.x) - item->X(), ((int32_t)ev->button.y) - item->Y());
				break;
			}
		}
		mouse_window_handle = 0;
	}
	return result;
}

bool GuiLayer::OnMouseDown(SDL_Event* ev)
{
	MWindow * item;
	int32_t x, y, w, h, mx, my;
	for (auto it = windows.rbegin(); it != windows.rend(); ++it)
	{
		item = it->o();
		x = item->X();
		y = item->Y();
		w = item->Width();
		h = item->Height();
		mx = (int32_t)ev->button.x;
		my = (int32_t)ev->button.y;
		if (mx >= x && mx < x + w && my >= y && my < y + h)
		{
			if (item->OnMouseDown(ev, mx - x, my - y))
			{
				mouse_window_handle = item->Handle();
				if (MouseGrabFunction)
					MouseGrabFunction();
				if (!is_active)
					if (LayerActivateFunction)
						LayerActivateFunction();
				return true;
			}
		}
	}

	return false;
}

bool GuiLayer::OnMouseMove(SDL_Event* ev)
{
	bool result = false;
	if (mouse_window_handle != 0)
	{
		MWindow * item;
		for (auto it = windows.rbegin(); it != windows.rend(); ++it)
		{
			item = it->o();
			if (item->Handle() == mouse_window_handle)
			{
				result = item->OnMouseMove(ev, ((int32_t)ev->button.x) - item->X(), ((int32_t)ev->button.y) - item->Y());
				break;
			}
		}
	}
	else
	{
		MWindow * item;
		int32_t x, y, w, h, mx, my;
		for (auto it = windows.rbegin(); it != windows.rend(); ++it)
		{
			item = it->o();
			x = item->X();
			y = item->Y();
			w = item->Width();
			h = item->Height();
			mx = (int32_t)ev->motion.x;
			my = (int32_t)ev->motion.y;
			if (mx >= x && mx < x + w && my >= y && my < y + h)
			{
				if (item->OnMouseMove(ev, mx - item->X(), my - item->Y()))
				{
					result = true;
					break;
				}
			}
		}
	}
	return result;
}

void GuiLayer::OnMouseOver()
{
}

void GuiLayer::OnMouseOut()
{
}