#pragma once

#include <glm/glm.hpp>

#include "Config.h"

using namespace glm;

class ColorButton
{
private:
	vec3 m_color;
	vec2 m_vertices[4];
	bool m_isPicked;


public:
	ColorButton();
	ColorButton(vec2 pivotPos, vec3 color);
	~ColorButton();

	bool IsPicked();
	
	void SetPicked(bool isPicked);
	void SetPosition(vec2 pos);

	vec3 GetColor();
	vec2 GetVertex(int idx);
};

