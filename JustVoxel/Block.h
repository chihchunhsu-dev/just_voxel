#pragma once

#include <glm/glm.hpp>
#include <string>

#include "Face.h"

using namespace glm;
using namespace std;

class Block
{
private:
	vec3 m_coordinate;
	ivec3 m_index;
	vec3 m_color;

	bool m_active;
	bool m_visible;
	bool m_visited;

	Face m_faces[6];
	Block* m_adjcentBlocks[6];

public:
	Block();
	Block(float pos_x, float pos_y, float pos_z, int id_x, int id_y, int id_z);
	~Block();

	bool IsActive();
	bool IsVisible();
	bool IsVisited();

	void SetActive(bool active);
	void SetVisible(bool visible);
	void SetVisited(bool visited);
	void SetColor(vec3 color);
	void SetAdjacentBlock(string type, Block *blk);

	Face GetFace(int idx);
	vec3 GetCoord();
	vec3 GetColor();
	ivec3 GetIndex();
	Block* GetAdjacentBlock(int idx);
};
