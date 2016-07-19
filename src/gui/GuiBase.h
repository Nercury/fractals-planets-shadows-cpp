#pragma once

#include "../types.h"
#include "../b_time.h"
#include "../safep.hpp"

#include "glgui.h"
#include "Theme.h"

#include "ScreenInfo.h"

#include "InputHandlerBase.h"

class GuiLayer;

class GuiBase
{
public:
	GuiBase() { theme = new Theme(); };
	virtual ~GuiBase() { delete theme; };
	Theme * theme;
	virtual GuiLayer * layerBack() = 0;
	virtual GuiLayer * layer() = 0;
	virtual GuiLayer * layerTop() = 0;
	virtual int32_t Width() = 0;
	virtual int32_t Height() = 0;
};