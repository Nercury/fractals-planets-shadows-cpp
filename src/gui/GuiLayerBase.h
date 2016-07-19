#pragma once

#include "../safep.hpp"
#include "../MetaObject.hpp"

#include "Window.h"

class GuiLayerBase
	: public MetaObject
{
public:
	virtual void AddWindow(p<Window> window) = 0;
	virtual bool RemoveWindow(p<Window> window) = 0;
	virtual void SetSize(int32_t width, int32_t height) = 0;
	GuiLayerBase(void) {};
	virtual ~GuiLayerBase(void) {};
	// meta info
	inline virtual std::string ToString() {
		return "GuiLayerBase";
	};
};