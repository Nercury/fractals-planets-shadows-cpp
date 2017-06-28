#pragma once

#include "Container.h"
#include "WindowEvents.h"

#include "../L.h"

class MWindow
	: public Container
{
private:
	bool autoSizeX;
	bool autoSizeY;
	int32_t autoMaxWidth;
	int32_t autoMinWidth;
	int32_t autoMaxHeight;
	int32_t autoMinHeight;
	WindowEvents * events;
public:
	MWindow(void);
	virtual ~MWindow(void);
	inline void BringToTop() { 
		if (this->events != NULL)
			this->events->OnBringWindowToTop(this->handle);
	};
	virtual void Close();

	// meta info
	inline std::string toString() {
		std::ostringstream ss;
		ss << "Window " << this->handle;
		return ss.str();
	};

	virtual void Render(boost::posix_time::time_duration delta);
	inline void SetEventHandler(WindowEvents * events) { this->events = events; };
	inline WindowEvents * GetEventHandler() { return this->events; };
	virtual bool OnMouseDown(SDL_Event* ev, int32_t x, int32_t y);
};