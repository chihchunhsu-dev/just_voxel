#include "ColorButton.h"



ColorButton::ColorButton()
{
}

ColorButton::ColorButton(vec2 pivotPos, vec3 color)
{
	m_color = color;
	m_isPicked = false;

	float x = pivotPos.x;
	float y = pivotPos.y;

	m_vertices[0] = vec2(x, y);
	m_vertices[1] = vec2(x - BUTTON_SIZE, y);
	m_vertices[2] = vec2(x - BUTTON_SIZE, y + BUTTON_SIZE);
	m_vertices[3] = vec2(x, y + BUTTON_SIZE);
	

}


ColorButton::~ColorButton()
{
}


bool ColorButton::IsPicked()
{
	return m_isPicked;
}



void ColorButton::SetPicked(bool isPicked)
{
	m_isPicked = isPicked;
}

void ColorButton::SetPosition(vec2 pos)
{
	float x = pos.x;
	float y = pos.y;

	m_vertices[0] = vec2(x, y);
	m_vertices[1] = vec2(x - BUTTON_SIZE, y);
	m_vertices[2] = vec2(x - BUTTON_SIZE, y + BUTTON_SIZE);
	m_vertices[3] = vec2(x, y + BUTTON_SIZE);
}

vec3 ColorButton::GetColor()
{
	return m_color;
}

vec2 ColorButton::GetVertex(int idx)
{
	return m_vertices[idx];
}