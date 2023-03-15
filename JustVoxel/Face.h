#pragma once

#include <glm/glm.hpp>
#include <string>

using namespace glm;
using namespace std;

class Face
{
private:
	vec3 m_position;
	vec3 m_color;
	vec3 m_normal;
	vec3 m_vertices[4];

public:
	Face();
	Face(string type, float x, float y, float z);
	~Face();

	vec3 GetVertex(int idx);
	vec3 GetColor();
	vec3 GetNormal();

	void SetColor(vec3 color);

};

