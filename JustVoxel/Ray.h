#pragma once

#include <glm/glm.hpp>

using namespace glm;

class Ray
{
private:
	vec3 m_origin;
	vec3 m_end;
	//vec3 m_direction;

public:
	Ray();
	~Ray();

	//vec3 GetDirection();
	vec3 GetOrigin();
	vec3 GetEnd();

	void SetRay(vec3 origin, vec3 end);
};

