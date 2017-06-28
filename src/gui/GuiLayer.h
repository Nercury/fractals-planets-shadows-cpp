#pragma once

#include "../safep.hpp"
#include "../types.h"
#include "Window.h"
#include "WindowEvents.h"
#include "InputHandlerBase.h"
#include "GuiBase.h"

#include <list>
#include <set>
#include <queue>

class GuiLayer :
	public WindowEvents
{
private:
	bool is_active;
	int32_t width;
	int32_t height;
	std::list<p<MWindow>> windows;
	std::queue<WHandle> windowRemoveQueue;
	WHandle mouse_window_handle;
	boost::function<void ()> MouseGrabFunction;
	boost::function<void ()> MouseUngrabFunction;
	boost::function<void ()> LayerActivateFunction;
	boost::function<void ()> LayerDeactivateFunction;
	GuiBase * gui;
	void RemoveWindow(WHandle handle);
	void DoPendingWindowRemove();
	void DoWindowRemoveByHandle(WHandle handle);
public:
	void AddWindow(p<MWindow> window);
	void RemoveWindow(p<MWindow> window);
	void RemoveWindow(MWindow * window);
	void Activate();
	void Deactivate();
	void UngrabMouse();
	bool HasWindows() { return this->windows.size() > 0; };
	void SetSize(int32_t width, int32_t height);
	GuiLayer(GuiBase * gui, boost::function<void ()> layerActivateFunction, boost::function<void ()> layerDeactivateFunction, boost::function<void ()> mouseGrabFunction, boost::function<void ()> mouseUngrabFunction);
	GuiLayer(GuiBase * gui, boost::function<void ()> layerActivateFunction, boost::function<void ()> layerDeactivateFunction, boost::function<void ()> mouseGrabFunction, boost::function<void ()> mouseUngrabFunction, int32_t width, int32_t height);
	virtual ~GuiLayer(void);
	void Render(boost::posix_time::time_duration delta);
	// window events
	virtual void OnBringWindowToTop(WHandle handle);
	// meta info
	inline std::string toString() {
		std::ostringstream ss;
		ss << "GuiLayer w:" << this->width << "  h:" << this->height;
		return ss.str();
	};
	bool OnKeyUp(SDL_Event* ev);
	bool OnKeyDown(SDL_Event* ev);
	bool OnMouseUp(SDL_Event* ev);
	bool OnMouseDown(SDL_Event* ev);
	bool OnMouseMove(SDL_Event* ev);
	void OnMouseOver();
	void OnMouseOut();
};