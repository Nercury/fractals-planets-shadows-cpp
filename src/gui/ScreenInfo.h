#pragma once

#include "../types.h"

#include <string>
#include <sstream>

class ScreenInfo
{
public:
	int32_t width;
	int32_t height;

	ScreenInfo(int32_t width, int32_t height) : width(width), height(height) {};

	// meta info
	inline std::string toString() {
		std::ostringstream ss;
		ss << "ScreenInfo";
		return ss.str();
	};
};