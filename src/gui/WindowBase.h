#pragma once

#include "../b_time.h"
#include "../types.h"
#include "glgui.h"
#include "WindowEvents.h"
#include "InputHandlerBase.h"

class Gui;

class WindowBase
	: public InputHandlerBase
{
protected:
public:
	WindowBase(void) {};
	virtual ~WindowBase(void) {};
	virtual void __setGui(Gui * gui) = 0;
	virtual uint32_t Handle() = 0;
	virtual int32_t Width() = 0;
	virtual int32_t Height() = 0;
	virtual int32_t X() = 0;
	virtual int32_t Y() = 0;
	virtual void Render(boost::posix_time::time_duration delta) = 0;
};