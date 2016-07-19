#pragma once

#include <string>
#include <functional>

#include "gui/Windowless.h"
#include "glst/GLST_Text.h"
#include "safep.hpp"

class TrMenuItem
	: public Windowless
{
private:
	p<GLST_Text> text_obj;
	std::string text;
	float mouseOverFade;
	bool mouseOver;
public:
	TrMenuItem()
		: mouseOverFade(0), mouseOver(false) { };
	TrMenuItem(std::string text, std::function<void (TrMenuItem*)> onClick)
		: text(text), onClick(onClick), mouseOverFade(0), mouseOver(false) { };
	virtual ~TrMenuItem() {};
	virtual void Render(boost::posix_time::time_duration delta);
	virtual void Initialize();
	void Reset() { mouseOverFade = 0.0; mouseOver = false; };
	virtual void OnMouseOver();
	virtual void OnMouseOut();
	virtual bool OnMouseUp(SDL_Event* ev, int32_t x, int32_t y);
	virtual bool OnMouseDown(SDL_Event* ev, int32_t x, int32_t y);
	std::string Text() { return text; };
	void SetText(std::string text);
	std::function<void (TrMenuItem*)> onClick;
	// meta info
	inline std::string toString() {
		std::ostringstream ss;
		ss << "TrMenuItem " << this->handle;
		return ss.str();
	};
};