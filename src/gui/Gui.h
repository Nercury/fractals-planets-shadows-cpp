#pragma once

#include "../types.h"
#include "../b_time.h"
#include "../safep.hpp"

#include "glgui.h"
#include "GuiBase.h"
#include "GuiLayer.h"
#include "Theme.h"

#include "ScreenInfo.h"

#include "InputHandlerBase.h"

class Gui
	: public GuiBase
{
private:
	int activeLayerIndex;
	int mouseLayerIndex;
	int mouseOverLayerIndex;
	int32_t width;
	int32_t height;
	GuiLayer * layers[3];
	/*void RealMousePosition(int32_t x, int32_t y);*/
public:
	virtual GuiLayer * layerBack();
	virtual GuiLayer * layer();
	virtual GuiLayer * layerTop();
	void SetSize(int32_t width, int32_t height);
	void Render(boost::posix_time::time_duration delta);
	Gui(void);
	Gui(int32_t width, int32_t height);
	virtual ~Gui(void);
	virtual inline int32_t Width() { return this->width; };
	virtual inline int32_t Height() { return this->height; };
	void OnLayerActivate(int layerIndex);
	void OnLayerDeactivate(int layerIndex);
	void OnLayerMouseGrab(int layerIndex);
	void OnLayerMouseUngrab(int layerIndex);
	bool OnKeyUp(SDL_Event* ev);
	bool OnKeyDown(SDL_Event* ev);
	bool OnMouseUp(SDL_Event* ev);
	bool OnMouseDown(SDL_Event* ev);
	bool OnMouseMove(SDL_Event* ev);
	inline std::string toString() {
		std::ostringstream ss;
		ss << "Gui";
		return ss.str();
	};
};