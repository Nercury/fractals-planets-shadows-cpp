#pragma once

#include <string>
#include "dim.h"

class World;
class WorldObject;

class Collision
{
public:
	Collision();
	virtual ~Collision();
	virtual bool RunSimulation(WorldObject & current, WorldObject & other) { return false; };
	virtual std::string GetName() { return "No collision"; };
	virtual void OnAssign(WorldObject * current);
};