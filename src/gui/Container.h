#pragma once

#include "glgui.h"

#include "Windowless.h"

#include <map>
#include <vector>
#include <list>
#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/set_of.hpp>

class Container
	: public Windowless
{
protected:
	boost::bimap<boost::bimaps::set_of<WHandle>, boost::bimaps::list_of<p<Windowless>>> childs;
	boost::bimap<boost::bimaps::set_of<WHandle>, boost::bimaps::multiset_of<int32_t>> tabOrder;
	WHandle mouse_down_child;
public:
	Container(void);
	virtual ~Container(void);
	virtual void Add(p<Windowless> w);
	virtual bool Remove(p<Windowless> w);
	virtual void Render(boost::posix_time::time_duration delta);
	// meta info
	inline std::string toString() {
		std::ostringstream ss;
		ss << "Container " << this->handle << " x:" << this->x << " y:" << this->y << " w:" << this->width << " h:" << this->height;
		return ss.str();
	};
	virtual bool OnKeyUp(SDL_Event* ev);
	virtual bool OnKeyDown(SDL_Event* ev);
	virtual bool OnMouseUp(SDL_Event* ev, int32_t x, int32_t y);
	virtual bool OnMouseDown(SDL_Event* ev, int32_t x, int32_t y);
	virtual bool OnMouseMove(SDL_Event* ev, int32_t x, int32_t y);
	virtual void OnMouseOver();
	virtual void OnMouseOut();
	virtual WHandle RealMousePosition(int32_t x, int32_t y);
};