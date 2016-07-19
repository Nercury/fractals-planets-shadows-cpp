#pragma once

#include "glgui.h"

class WindowEvents
{
public:
	virtual void OnBringWindowToTop(WHandle handle) = 0;
	WindowEvents(void) {};
	virtual ~WindowEvents(void) {};
};