#include "Face.h"

Face::Face()
{

}

Face::Face(string type, float x, float y, float z)
{
	float offset = 0.5f;

	if (type == "front")
	{
		m_position = vec3(x, y, z + offset);
		m_color = vec3(1.0f, 0.0f, 0.0f);
		m_normal = vec3(0.0f, 0.0f, 1.0f);
		m_vertices[0] = vec3(x + offset, y + offset, z + offset);
		m_vertices[1] = vec3(x - offset, y + offset, z + offset);
		m_vertices[2] = vec3(x - offset, y - offset, z + offset);
		m_vertices[3] = vec3(x + offset, y - offset, z + offset);

	}
	else if (type == "back")
	{
		m_position = vec3(x, y, z - offset);
		m_color = vec3(0.0f, 1.0f, 0.0f);
		m_normal = vec3(0.0f, 0.0f, -1.0f);
		m_vertices[0] = vec3(x + offset, y + offset, z - offset);
		m_vertices[1] = vec3(x + offset, y - offset, z - offset);
		m_vertices[2] = vec3(x - offset, y - offset, z - offset);
		m_vertices[3] = vec3(x - offset, y + offset, z - offset);

	}
	else if (type == "left")
	{
		m_position = vec3(x - offset, y, z);
		m_color = vec3(0.0f, 0.0f, 1.0f);
		m_normal = vec3(-1.0f, 0.0f, 0.0f);
		m_vertices[0] = vec3(x - offset, y + offset, z + offset);
		m_vertices[1] = vec3(x - offset, y + offset, z - offset);
		m_vertices[2] = vec3(x - offset, y - offset, z - offset);
		m_vertices[3] = vec3(x - offset, y - offset, z + offset);

	}
	else if (type == "right")
	{
		m_position = vec3(x + offset, y, z);
		m_color = vec3(1.0f, 1.0f, 0.0f);
		m_normal = vec3(1.0f, 0.0f, 0.0f);
		m_vertices[0] = vec3(x + offset, y + offset, z - offset);
		m_vertices[1] = vec3(x + offset, y + offset, z + offset);
		m_vertices[2] = vec3(x + offset, y - offset, z + offset);
		m_vertices[3] = vec3(x + offset, y - offset, z - offset);

	}
	else if (type == "top")
	{
		m_position = vec3(x, y + offset, z);
		m_color = vec3(1.0f, 0.0f, 1.0f);
		m_normal = vec3(0.0f, 1.0f, 0.0f);
		m_vertices[0] = vec3(x + offset, y + offset, z - offset);
		m_vertices[1] = vec3(x - offset, y + offset, z - offset);
		m_vertices[2] = vec3(x - offset, y + offset, z + offset);
		m_vertices[3] = vec3(x + offset, y + offset, z + offset);

	}
	else if (type == "bottom")
	{
		m_position = vec3(x, y - offset, z);
		m_color = vec3(0.0f, 1.0f, 1.0f);
		m_normal = vec3(0.0f, -1.0f, 0.0f);
		m_vertices[0] = vec3(x + offset, y - offset, z + offset);
		m_vertices[1] = vec3(x - offset, y - offset, z + offset);
		m_vertices[2] = vec3(x - offset, y - offset, z - offset);
		m_vertices[3] = vec3(x + offset, y - offset, z - offset);

	}
}

Face::~Face()
{

}



vec3 Face::GetVertex(int idx)
{
	return m_vertices[idx];
}

vec3 Face::GetColor()
{
	return m_color;
}

vec3 Face::GetNormal()
{
	return m_normal;
}


void Face::SetColor(vec3 color)
{
	m_color = color;
}






