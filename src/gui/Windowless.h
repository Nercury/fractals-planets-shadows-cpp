#pragma once

#include "../b_time.h"
#include "glgui.h"
#include <sstream>
#include "InputHandlerBase.h"
#include "GuiBase.h"

class Windowless
	: public InputHandlerBase
{
protected:
	int32_t width;
	int32_t height;
	int32_t x;
	int32_t y;
	WHandle handle;
	GuiBase * gui;
	GuiLayer * guiLayer;
public:
	void __setGui(GuiBase * gui) { this->gui = gui; };
	void __setGuiLayer(GuiLayer * guiLayer) { this->guiLayer = guiLayer; };
	inline virtual int32_t Width() { return width; };
	inline virtual int32_t Height() { return height; };
	inline virtual int32_t X() { return x; };
	inline virtual int32_t Y() { return y; };
	inline virtual WHandle Handle() { return handle; };
	virtual void Move(int32_t x, int32_t y);
	virtual void Resize(int32_t width, int32_t height);
	virtual void SetWidth(int32_t width);
	virtual void SetHeight(int32_t height);
	virtual void Render(boost::posix_time::time_duration delta);
	virtual void Initialize();
	virtual void Terminate();
	Windowless(void);
	virtual ~Windowless(void);

	// meta info
	inline std::string toString() {
		std::ostringstream ss;
		ss << "Windowless " << this->handle << " x:" << this->x << " y:" << this->y << " w:" << this->width << " h:" << this->height;
		return ss.str();
	};

	virtual bool OnKeyUp(SDL_Event* ev);
	virtual bool OnKeyDown(SDL_Event* ev);
	virtual bool OnMouseUp(SDL_Event* ev, int32_t x, int32_t y);
	virtual bool OnMouseDown(SDL_Event* ev, int32_t x, int32_t y);
	virtual bool OnMouseMove(SDL_Event* ev, int32_t x, int32_t y);
	virtual void OnMouseOver();
	virtual void OnMouseOut();
	virtual WHandle RealMousePosition(int32_t x, int32_t y) { return GLGUI_INVALID_HANDLE; };
};

