#pragma once

#include <set>
#include "safep.hpp"

#include "WorldObject.h"
#include "Camera.h"

class World
{
private:
	std::set<WorldObject*> all_objects;
	std::set<WorldObject*> solid_objects;
public:
	World();
	virtual ~World();
	void SetObjectCollision(WorldObject * obj, bool value);
	void DeleteObject(WorldObject * obj);
	void Render();
	void RenderShadows();
	void RenderShadows(WorldObject * obj);
	// meta info
	inline std::string toString() {
		std::ostringstream ss;
		ss << "World";
		return ss.str();
	};
};

p<World> get_world();