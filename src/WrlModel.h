#pragma once

#include "math/Vector.h"
#include "Texture.h"
#include "Shader.h"
#include <functional>
#include <vector>

#include "WorldObject.h"

class WrlModel
	: public WorldObject
{
public:
	p<Texture> texture;
	p<Shader> shader;
	std::vector<Vector3d> points;
	std::vector<Vector3d> colors;
	std::vector<int> colorIndexes;
	std::vector<int> indexes;
	WrlModel() {};
	virtual ~WrlModel() override  {};
	virtual void Render() override ;

	// meta info
	inline std::string toString() {
		std::ostringstream ss;
		ss << "WrlModel";
		return ss.str();
	};
};