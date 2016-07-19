#pragma once

#include "gui/Window.h"

#include "TrMenuItem.h"

class TrMenu
	: public Window
{
private:
	WHandle mouse_over_handle;
public:
	TrMenu();
	virtual ~TrMenu();
	virtual void Render(boost::posix_time::time_duration delta);
	virtual bool OnMouseMove(SDL_Event* ev, int32_t x, int32_t y);
	virtual void Terminate();
	// meta info
	inline std::string toString() {
		std::ostringstream ss;
		ss << "Menu " << this->handle;
		return ss.str();
	};
};