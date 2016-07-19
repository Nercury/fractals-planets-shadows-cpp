#pragma once

#include "dim.h"
#include "safep.hpp"
#include "Collision.h"
#include "math/Matrix.h"
#include "math/Vector.h"
#include "math/Quaternion.h"

class World;

class WorldObject
{
protected:
	p<World> world;
	Collision collision;

	float sqr(float a);
	// Offset pIn by pOffset into pOut
	void VectorOffset (Vector3f & pIn, Vector3f & pOffset, Vector3f & pOut);
	// Compute the cross product a X b into pOut
	void VectorGetNormal (Vector3f & a, Vector3f & b, Vector3f & pOut);
	// Normalize pIn vector into pOut
	bool VectorNormalize (Vector3f & pIn, Vector3f & pOut);
	// Compute p1,p2,p3 face normal into pOut
	bool ComputeFaceNormal (Vector3f & p1, Vector3f & p2, Vector3f & p3, Vector3f & pOut);
public:
	bool shadowObject;
	Vector3f position;
	Quaternionf rotation;
	Vector3f velocity;
	WorldObject(void);
	WorldObject(Vector3f position, Quaternionf rotation);
	virtual ~WorldObject();
	Collision GetCollision() { return collision; };
	void SetCollision(Collision c) { collision = c; c.OnAssign(this); };
	virtual void Render();
	virtual void BeginScene() {};
	virtual void EndScene() {};
};