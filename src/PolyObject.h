#pragma once

#include "math/Vector.h"
#include "Texture.h"
#include "Shader.h"
#include <functional>

#include "WorldObject.h"

class PolyObject
	: public WorldObject
{
public:
	p<Texture> texture;
	p<Shader> shader;
	Vector2f uRange;
	Vector2f vRange;
	// u, v, x, y, z
	std::function<void (float&,float&,float&,float&,float&)> func1;
	std::function<void (float&,float&,float&,float&,float&)> func2;
	std::function<void (float&,float&,float&,float&,float&)> func3;
	PolyObject() : uRange(0,1), vRange(0,1) {};
	PolyObject(Vector2f uRange, Vector2f vRange, 
		std::function<void (float&,float&,float&,float&,float&)> func1
		) : uRange(uRange), vRange(vRange), func1(func1) {};
	PolyObject(Vector2f uRange, Vector2f vRange, 
		std::function<void (float&,float&,float&,float&,float&)> func1,
		std::function<void (float&,float&,float&,float&,float&)> func2
		) : uRange(uRange), vRange(vRange), func1(func1), func2(func2) {};
	PolyObject(Vector2f uRange, Vector2f vRange, 
		std::function<void (float&,float&,float&,float&,float&)> func1,
		std::function<void (float&,float&,float&,float&,float&)> func2,
		std::function<void (float&,float&,float&,float&,float&)> func3
		) : uRange(uRange), vRange(vRange), func1(func1), func2(func2), func3(func3) {};
	virtual ~PolyObject() {};
	virtual void Render();

	// meta info
	inline std::string toString() {
		std::ostringstream ss;
		ss << "PolyObject";
		return ss.str();
	};
};