#include "Block.h"


Block::Block()
{

}

Block::Block(float pos_x, float pos_y, float pos_z, int id_x, int id_y, int id_z)
{
	m_active = false;
	m_visible = false;
	m_visited = false;
	//m_index = id;

	m_index.x = id_x;
	m_index.y = id_y;
	m_index.z = id_z;

	m_coordinate.x = pos_x;
	m_coordinate.y = pos_y;
	m_coordinate.z = pos_z;

	m_faces[0] = Face("front",	pos_x, pos_y, pos_z);
	m_faces[1] = Face("back",	pos_x, pos_y, pos_z);
	m_faces[2] = Face("left",	pos_x, pos_y, pos_z);
	m_faces[3] = Face("right",	pos_x, pos_y, pos_z);
	m_faces[4] = Face("top",	pos_x, pos_y, pos_z);
	m_faces[5] = Face("bottom", pos_x, pos_y, pos_z);

	for (int i = 0; i < 6; i++)
	{
		m_adjcentBlocks[i] = NULL;
	}
}

Block::~Block()
{

}

bool Block::IsActive()
{
	return m_active;
}

bool Block::IsVisible()
{
	return m_visible;
}

bool Block::IsVisited()
{
	return m_visited;
}

void Block::SetActive(bool active)
{
	m_active = active;
}

void Block::SetVisible(bool visible)
{
	m_visible = visible;
}

void Block::SetVisited(bool visited)
{
	m_visited = visited;
}

void Block::SetColor(vec3 color)
{
	m_color = color;
	for (int i = 0; i < 6; i++)
	{
		m_faces[i].SetColor(color);
	}
}

void Block::SetAdjacentBlock(string type, Block *blk)
{
	if (type == "front")
		m_adjcentBlocks[0] = blk;
	else if (type == "back")
		m_adjcentBlocks[1] = blk;
	else if (type == "left")
		m_adjcentBlocks[2] = blk;
	else if (type == "right")
		m_adjcentBlocks[3] = blk;
	else if (type == "top")
		m_adjcentBlocks[4] = blk;
	else if (type == "bottom")
		m_adjcentBlocks[5] = blk;
	else
		;
}

Face Block::GetFace(int idx)
{
	return m_faces[idx];
}

vec3 Block::GetCoord()
{
	return m_coordinate;
}

ivec3 Block::GetIndex()
{
	return m_index;
}

vec3 Block::GetColor()
{
	return m_color;
}

Block* Block::GetAdjacentBlock(int idx)
{
	return m_adjcentBlocks[idx];
}


