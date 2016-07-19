#include "WorldObject.h"

#include "sdlgl.h"
#include "World.h"

#include <math.h>

float WorldObject::sqr(float a)
{
	return a*a;
}

// Offset pIn by pOffset into pOut
void WorldObject::VectorOffset (Vector3f & pIn, Vector3f & pOffset, Vector3f & pOut)
{
   pOut.x = pIn.x - pOffset.x;
   pOut.y = pIn.y - pOffset.y;
   pOut.z = pIn.z - pOffset.z;
}

// Compute the cross product a X b into pOut
void WorldObject::VectorGetNormal (Vector3f & a, Vector3f & b, Vector3f & pOut)
{
   pOut.x = a.y * b.z - a.z * b.y;
   pOut.y = a.z * b.x - a.x * b.z;
   pOut.z = a.x * b.y - a.y * b.x;
}

// Normalize pIn vector into pOut
bool WorldObject::VectorNormalize (Vector3f & pIn, Vector3f & pOut)
{
   float len = (float)(sqrt(sqr(pIn.x) + sqr(pIn.y) + sqr(pIn.z)));
   if (len)
   {
      pOut.x = pIn.x / len;
      pOut.y = pIn.y / len;
      pOut.z = pIn.z / len;
      return true;
   }
   return false;
}

// Compute p1,p2,p3 face normal into pOut
bool WorldObject::ComputeFaceNormal (Vector3f & p1, Vector3f & p2, Vector3f & p3, Vector3f & pOut)
{
   // Uses p2 as a new origin for p1,p3
   Vector3f a;
   VectorOffset(p3, p2, a);
   Vector3f b;
   VectorOffset(p1, p2, b);
   // Compute the cross product a X b to get the face normal
   Vector3f pn;
   VectorGetNormal(a, b, pn);
   // Return a normalized vector
   return VectorNormalize(pn, pOut);
}

WorldObject::WorldObject()
	: position(Vector3f()), rotation(Quaternionf(1,0,0,0)), shadowObject(false)
{
	world = get_world();
	collision.OnAssign(this);
}

WorldObject::WorldObject(Vector3f position, Quaternionf rotation)
	: position(position), rotation(rotation), shadowObject(false)
{
	world = get_world();
	collision.OnAssign(this);
}

WorldObject::~WorldObject()
{
	world.o()->DeleteObject(this);
}

void WorldObject::Render()
{
	wTranslatef(position.x, position.y, position.z);
	Matrix4f m;
	rotation.to4x4Matrix(&m);
	wMultMatrixf(m.element);
}