#include "Ray.h"

Ray::Ray()
{

}


Ray::~Ray()
{

}

/*
vec3 Ray::GetDirection()
{
	return m_direction;
}
*/

vec3 Ray::GetOrigin()
{
	return m_origin;
}

vec3 Ray::GetEnd()
{
	return m_end;
}

void Ray::SetRay(vec3 origin, vec3 end)
{
	m_origin = origin;
	m_end = end;
	//m_direction = normalize(m_end - m_direction);
}