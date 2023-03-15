#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <utility>
#include <cstdlib>
#include <cmath>
#include <ctime>

#include <windows.h>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include "../shader_lib/shader.h"
#include "../GL/glui.h"  // glut is included here.

#include "Block.h" 
#include "Ray.h"
#include "ColorButton.h"
#include "Config.h"

using namespace glm;


#define LENGTH_X 32
#define LENGTH_Y 32
#define LENGTH_Z 32



// GUI
GLint main_window;
GLUI *glui;
GLint isDrawGround = 1;
GLint isDrawAxis = 1;
GLint isDrawGrid = 1;
GLboolean isHideGui = false;
GLfloat bgColor_x = 0.2f, bgColor_y = 0.2f, bgColor_z = 0.2f;
GLUI_Button *voxelModeBtn, *faceModeBtn;
GLUI_Button *attachBtn, *eraseBtn, *paintBtn;
ColorButton colorButtons[BUTTON_COLUMN_NUM][BUTTON_ROW_NUM];
vec3 colorPalette[BUTTON_COLUMN_NUM][BUTTON_ROW_NUM] =
{
	{
		vec3(229.0 / 256.0, 115.0 / 256.0, 115.0 / 256.0),
		vec3(240.0 / 256.0, 98.0 / 256.0, 146.0 / 256.0),
		vec3(186.0 / 256.0, 104.0 / 256.0, 200.0 / 256.0),
		vec3(149.0 / 256.0, 117.0 / 256.0, 205.0 / 256.0),
		vec3(121.0 / 256.0, 134.0 / 256.0, 203.0 / 256.0),
		vec3(100.0 / 256.0, 181.0 / 256.0, 246.0 / 256.0),
		vec3(79.0 / 256.0, 195.0 / 256.0, 247.0 / 256.0),
		vec3(77.0 / 256.0, 208.0 / 256.0, 225.0 / 256.0),
		vec3(77.0 / 256.0, 182.0 / 256.0, 172.0 / 256.0),
		vec3(129.0 / 256.0, 199.0 / 256.0, 132.0 / 256.0),
		vec3(174.0 / 256.0, 213.0 / 256.0, 129.0 / 256.0),
		vec3(220.0 / 256.0, 231.0 / 256.0, 117.0 / 256.0),
		vec3(255.0 / 256.0, 241.0 / 256.0, 118.0 / 256.0),
		vec3(255.0 / 256.0, 213.0 / 256.0, 79.0 / 256.0),
		vec3(255.0 / 256.0, 183.0 / 256.0, 77.0 / 256.0),
		vec3(255.0 / 256.0, 138.0 / 256.0, 101.0 / 256.0),
		vec3(161.0 / 256.0, 136.0 / 256.0, 127.0 / 256.0),
		vec3(144.0 / 256.0, 164.0 / 256.0, 174.0 / 256.0),
		vec3(224.0 / 256.0, 224.0 / 256.0, 224.0 / 256.0)
	},

	{
		vec3(239.0 / 256.0, 83.0 / 256.0, 80.0 / 256.0),
		vec3(236.0 / 256.0, 64.0 / 256.0, 122.0 / 256.0),
		vec3(171.0 / 256.0, 71.0 / 256.0, 188.0 / 256.0),
		vec3(126.0 / 256.0, 87.0 / 256.0, 194.0 / 256.0),
		vec3(92.0 / 256.0, 107.0 / 256.0, 192.0 / 256.0),
		vec3(66.0 / 256.0, 165.0 / 256.0, 245.0 / 256.0),
		vec3(41.0 / 256.0, 182.0 / 256.0, 246.0 / 256.0),
		vec3(38.0 / 256.0, 198.0 / 256.0, 218.0 / 256.0),
		vec3(38.0 / 256.0, 166.0 / 256.0, 154.0 / 256.0),
		vec3(102.0 / 256.0, 187.0 / 256.0, 106.0 / 256.0),
		vec3(156.0 / 256.0, 204.0 / 256.0, 101.0 / 256.0),
		vec3(212.0 / 256.0, 225.0 / 256.0, 87.0 / 256.0),
		vec3(255.0 / 256.0, 238.0 / 256.0, 88.0 / 256.0),
		vec3(255.0 / 256.0, 202.0 / 256.0, 40.0 / 256.0),
		vec3(255.0 / 256.0, 167.0 / 256.0, 38.0 / 256.0),
		vec3(255.0 / 256.0, 112.0 / 256.0, 67.0 / 256.0),
		vec3(141.0 / 256.0, 110.0 / 256.0, 99.0 / 256.0),
		vec3(120.0 / 256.0, 144.0 / 256.0, 156.0 / 256.0),
		vec3(189.0 / 256.0, 189.0 / 256.0, 189.0 / 256.0)
	},
	/*
	{
		vec3(244.0 / 256.0, 67.0 / 256.0, 54.0 / 256.0),
		vec3(233.0 / 256.0, 30.0 / 256.0, 99.0 / 256.0),
		vec3(156.0 / 256.0, 39.0 / 256.0, 176.0 / 256.0),
		vec3(103.0 / 256.0, 58.0 / 256.0, 183.0 / 256.0),
		vec3(63.0 / 256.0, 81.0 / 256.0, 181.0 / 256.0),
		vec3(33.0 / 256.0, 150.0 / 256.0, 234.0 / 256.0),
		vec3(3.0 / 256.0, 169.0 / 256.0, 244.0 / 256.0),
		vec3(0.0 / 256.0, 188.0 / 256.0, 212.0 / 256.0),
		vec3(0.0 / 256.0, 150.0 / 256.0, 136.0 / 256.0),
		vec3(76.0 / 256.0, 175.0 / 256.0, 80 / 256.0),
		vec3(139.0 / 256.0, 195.0 / 256.0, 74.0 / 256.0),
		vec3(205.0 / 256.0, 220.0 / 256.0, 57.0 / 256.0),
		vec3(255.0 / 256.0, 235.0 / 256.0, 59.0 / 256.0),
		vec3(255.0 / 256.0, 193.0 / 256.0, 7.0 / 256.0),
		vec3(255.0 / 256.0, 152.0 / 256.0, 0.0 / 256.0),
		vec3(255.0 / 256.0, 87.0 / 256.0, 34.0 / 256.0),
		vec3(121.0 / 256.0, 85.0 / 256.0, 72.0 / 256.0),
		vec3(96.0 / 256.0, 125.0 / 256.0, 139.0 / 256.0),
		vec3(158.0 / 256.0, 158.0 / 256.0, 158.0 / 256.0)
	},
	*/
	{
		vec3(229.0 / 256.0, 57.0 / 256.0, 53.0 / 256.0),
		vec3(216.0 / 256.0, 27.0 / 256.0, 96.0 / 256.0),
		vec3(142.0 / 256.0, 36.0 / 256.0, 170.0 / 256.0),
		vec3(94.0 / 256.0, 53.0 / 256.0, 177.0 / 256.0),
		vec3(57.0 / 256.0, 73.0 / 256.0, 171.0 / 256.0),
		vec3(30.0 / 256.0, 136.0 / 256.0, 229.0 / 256.0),
		vec3(3.0 / 256.0, 155.0 / 256.0, 229.0 / 256.0),
		vec3(0.0 / 256.0, 172.0 / 256.0, 193.0 / 256.0),
		vec3(0.0 / 256.0, 137.0 / 256.0, 123.0 / 256.0),
		vec3(67.0 / 256.0, 160.0 / 256.0, 71.0 / 256.0),
		vec3(124.0 / 256.0, 179.0 / 256.0, 66.0 / 256.0),
		vec3(192.0 / 256.0, 202.0 / 256.0, 51.0 / 256.0),
		vec3(253.0 / 256.0, 216.0 / 256.0, 53.0 / 256.0),
		vec3(255.0 / 256.0, 179.0 / 256.0, 0.0 / 256.0),
		vec3(251.0 / 256.0, 140.0 / 256.0, 0.0 / 256.0),
		vec3(244.0 / 256.0, 81.0 / 256.0, 30.0 / 256.0),
		vec3(109.0 / 256.0, 76.0 / 256.0, 65.0 / 256.0),
		vec3(84.0 / 256.0, 110.0 / 256.0, 122.0 / 256.0),
		vec3(117.0 / 256.0, 117.0 / 256.0, 117.0 / 256.0)
	},
	/*
	{
		vec3(211.0 / 256.0, 47.0 / 256.0, 47.0 / 256.0),
		vec3(194.0 / 256.0, 24.0 / 256.0, 91.0 / 256.0),
		vec3(123.0 / 256.0, 31.0 / 256.0, 162.0 / 256.0),
		vec3(81.0 / 256.0, 45.0 / 256.0, 168.0 / 256.0),
		vec3(48.0 / 256.0, 63.0 / 256.0, 159.0 / 256.0),
		vec3(25.0 / 256.0, 118.0 / 256.0, 210.0 / 256.0),
		vec3(2.0 / 256.0, 136.0 / 256.0, 209.0 / 256.0),
		vec3(0.0 / 256.0, 151.0 / 256.0, 167.0 / 256.0),
		vec3(0.0 / 256.0, 121.0 / 256.0, 107.0 / 256.0),
		vec3(56.0 / 256.0, 142.0 / 256.0, 60 / 256.0),
		vec3(104.0 / 256.0, 159.0 / 256.0, 56.0 / 256.0),
		vec3(175.0 / 256.0, 180.0 / 256.0, 43.0 / 256.0),
		vec3(251.0 / 256.0, 192.0 / 256.0, 45.0 / 256.0),
		vec3(255.0 / 256.0, 160.0 / 256.0, 0.0 / 256.0),
		vec3(245.0 / 256.0, 124.0 / 256.0, 0.0 / 256.0),
		vec3(230.0 / 256.0, 74.0 / 256.0, 25.0 / 256.0),
		vec3(93.0 / 256.0, 64.0 / 256.0, 55.0 / 256.0),
		vec3(69.0 / 256.0, 90.0 / 256.0, 100.0 / 256.0),
		vec3(97.0 / 256.0, 97.0 / 256.0, 97.0 / 256.0)
	},
	*/
	{
		vec3(198.0 / 256.0, 40.0 / 256.0, 40.0 / 256.0),
		vec3(173.0 / 256.0, 20.0 / 256.0, 87.0 / 256.0),
		vec3(106.0 / 256.0, 27.0 / 256.0, 154.0 / 256.0),
		vec3(69.0 / 256.0, 39.0 / 256.0, 160.0 / 256.0),
		vec3(40.0 / 256.0, 53.0 / 256.0, 147.0 / 256.0),
		vec3(21.0 / 256.0, 101.0 / 256.0, 192.0 / 256.0),
		vec3(2.0 / 256.0, 119.0 / 256.0, 189.0 / 256.0),
		vec3(0.0 / 256.0, 131.0 / 256.0, 143.0 / 256.0),
		vec3(0.0 / 256.0, 105.0 / 256.0, 92.0 / 256.0),
		vec3(46.0 / 256.0, 125.0 / 256.0, 50.0 / 256.0),
		vec3(85.0 / 256.0, 139.0 / 256.0, 47.0 / 256.0),
		vec3(158.0 / 256.0, 157.0 / 256.0, 36.0 / 256.0),
		vec3(249.0 / 256.0, 168.0 / 256.0, 37.0 / 256.0),
		vec3(255.0 / 256.0, 143.0 / 256.0, 0.0 / 256.0),
		vec3(239.0 / 256.0, 108.0 / 256.0, 0.0 / 256.0),
		vec3(216.0 / 256.0, 67.0 / 256.0, 21.0 / 256.0),
		vec3(78.0 / 256.0, 52.0 / 256.0, 46.0 / 256.0),
		vec3(55.0 / 256.0, 71.0 / 256.0, 79.0 / 256.0),
		vec3(66.0 / 256.0, 66.0 / 256.0, 66.0 / 256.0)
	},

	{
		vec3(183.0 / 256.0, 28.0 / 256.0, 28.0 / 256.0),
		vec3(136.0 / 256.0, 14.0 / 256.0, 79.0 / 256.0),
		vec3(74.0 / 256.0, 20.0 / 256.0, 140.0 / 256.0),
		vec3(49.0 / 256.0, 27.0 / 256.0, 146.0 / 256.0),
		vec3(26.0 / 256.0, 35.0 / 256.0, 126.0 / 256.0),
		vec3(13.0 / 256.0, 71.0 / 256.0, 161.0 / 256.0),
		vec3(1.0 / 256.0, 87.0 / 256.0, 155.0 / 256.0),
		vec3(0.0 / 256.0, 96.0 / 256.0, 100.0 / 256.0),
		vec3(0.0 / 256.0, 77.0 / 256.0, 64.0 / 256.0),
		vec3(27.0 / 256.0, 94.0 / 256.0, 32.0 / 256.0),
		vec3(51.0 / 256.0, 105.0 / 256.0, 30.0 / 256.0),
		vec3(130.0 / 256.0, 119.0 / 256.0, 23.0 / 256.0),
		vec3(245.0 / 256.0, 127.0 / 256.0, 3.0 / 256.0),
		vec3(255.0 / 256.0, 111.0 / 256.0, 0.0 / 256.0),
		vec3(230.0 / 256.0, 81.0 / 256.0, 0.0 / 256.0),
		vec3(191.0 / 256.0, 54.0 / 256.0, 12.0 / 256.0),
		vec3(62.0 / 256.0, 39.0 / 256.0, 35.0 / 256.0),
		vec3(38.0 / 256.0, 50.0 / 256.0, 56.0 / 256.0),
		vec3(33.0 / 256.0, 33.0 / 256.0, 33.0 / 256.0)
	},
};


// camera
GLboolean isRotating = false;
GLboolean isPanning = false;
GLfloat zoom = 50.0f;
GLfloat rotx = 30;
//GLfloat roty = 50.0f;
GLfloat roty = 0.001f;
GLfloat tx = 0;
GLfloat ty = 0;
GLint lastx = 0;
GLint lasty = 0;
GLint windowWidth = 0, windowHeight = 0;
GLboolean isPerspective = true;
GLdouble orthoZoomScale = 0.0005f;


// light
vec3 light0_pos = vec3(500.0f, 750.0f, 1000.0f);
vec3 light1_pos = vec3(-500.0f, 0.0f, -1000.0f);

// blocks
Block *blocks[LENGTH_X][LENGTH_Y][LENGTH_Z];
vector<Block*> activeBlocks;
vector<Block*> visibleBlocks;
vec3 currentPaintColor = colorPalette[0][5];

// shader
GLuint basicShader;

// VBO
GLuint *vboIds = NULL;
struct VtxAttrib
{
	GLfloat coord_x, coord_y, coord_z;
	GLfloat color_x, color_y, color_z;
	GLfloat normal_x, normal_y, normal_z;
};
vector<VtxAttrib> blockAttribs;

// edit
enum EditMode
{
	VOXEL = 1,
	FACE = 2
};
enum EditAction
{
	ATTACH = 1,
	ERASE = 2,
	PAINT = 3
};
EditMode mode;
EditAction action;
GLint isMirrorEdit_x = 0;
GLint isMirrorEdit_z = 0;
stack<pair<EditAction, vector<Block*>>> undoStack, redoStack;
stack<pair<vec3, vec3>> undoColorStack, redoColorStack;


// test parameter


void UpdateVBO()
{
	blockAttribs.clear();
	VtxAttrib vtxAttrib;
	for (GLuint i = 0; i < visibleBlocks.size(); i++)
	{
		// 6 faces
		for (GLuint j = 0; j < FACE_PER_BLOCK; j++)
		{
			// 4 vertices
			for (GLuint k = 0; k < VERTEX_PER_FACE; k++)
			{
				Face face = visibleBlocks.at(i)->GetFace(j);
				vtxAttrib.coord_x = face.GetVertex(k).x;
				vtxAttrib.coord_y = face.GetVertex(k).y;
				vtxAttrib.coord_z = face.GetVertex(k).z;

				vtxAttrib.color_x = face.GetColor().x;
				vtxAttrib.color_y = face.GetColor().y;
				vtxAttrib.color_z = face.GetColor().z;

				vtxAttrib.normal_x = face.GetNormal().x;
				vtxAttrib.normal_y = face.GetNormal().y;
				vtxAttrib.normal_z = face.GetNormal().z;

				blockAttribs.push_back(vtxAttrib);
			}
		}
	}

	//if (blockAttribs.size() != 0)
	//{
		glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(VtxAttrib) * blockAttribs.size(),
			&blockAttribs.front(),
			GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	//}
}



void CullHiddenBlocks()
{
	visibleBlocks.clear();
	GLuint count = 0;
	Block *adjBlock;

	//cout << activeBlocks.size() << " #" << endl;
	//cout << visibleBlocks.size() << " #" << endl;

	for (GLuint i = 0; i < activeBlocks.size(); i++)
	{
		// check if wrapped
		for (GLuint j = 0; j < FACE_PER_BLOCK; j++)
		{
			adjBlock = activeBlocks.at(i)->GetAdjacentBlock(j);
			if (adjBlock != NULL && adjBlock->IsActive())
			{
				count++;
			}
		}

		// not wrapped
		if (count != 6)
		{
			activeBlocks.at(i)->SetVisible(true);
			visibleBlocks.push_back(activeBlocks.at(i));
		}
		count = 0;
	}
}



void UpdateActiveBlocks()
{
	activeBlocks.clear();
	for (GLuint x = 0; x < LENGTH_X; x++)
	{
		for (GLuint y = 0; y < LENGTH_Y; y++)
		{
			for (GLuint z = 0; z < LENGTH_Z; z++)
			{
				if (blocks[x][y][z]->IsActive())
					activeBlocks.push_back(blocks[x][y][z]);
			}
		}
	}
	CullHiddenBlocks();
}




void Control_Callback(GLint control)
{
	switch (control)
	{
	case TOOL_CLEAR_ID:
	case TOOL_FULL_ID:
	{
		for (GLuint x = 0; x < LENGTH_X; x++)
			for (GLuint y = 0; y < LENGTH_Y; y++)
				for (GLuint z = 0; z < LENGTH_Z; z++)
				{
					blocks[x][y][z]->SetActive(control == TOOL_FULL_ID);
					if (control == TOOL_FULL_ID)
						blocks[x][y][z]->SetColor(currentPaintColor);
				}

		stack<pair<EditAction, vector<Block*>>> emptyRedoStack, emptyUndoStack;
		stack<pair<vec3, vec3>> emptyColorRedoStack, emptyColorUndoStack;
		redoStack.swap(emptyRedoStack);
		redoColorStack.swap(emptyColorRedoStack);
		undoStack.swap(emptyRedoStack);
		undoColorStack.swap(emptyColorRedoStack);
		
		UpdateActiveBlocks();
		UpdateVBO();
		glutPostRedisplay();
		break;
	}

	case MODE_VOXEL_ID:
	{
		voxelModeBtn->set_name("# VOXEL (V) #");
		faceModeBtn->set_name(" FACE (F) ");

		mode = VOXEL;

		break; 
	}
	case MODE_FACE_ID:
	{	
		voxelModeBtn->set_name("VOXEL (V)");
		faceModeBtn->set_name("# FACE (F) #");

		mode = FACE;

		break;
	}
	case ACTION_ATTACH_ID:
	{
		attachBtn->set_name("# ATTACH (Z) #");
		eraseBtn->set_name("ERASE (X)");
		paintBtn->set_name("PAINT (C)");

		action = ATTACH;
		break;
	}
	case ACTION_ERASE_ID:
	{
		attachBtn->set_name("ATTACH (Z)");
		eraseBtn->set_name("# ERASE (X) #");
		paintBtn->set_name("PAINT (C)");

		action = ERASE;
		break;
	}
	case ACTION_PAINT_ID:
	{
		attachBtn->set_name("ATTACH (Z)");
		eraseBtn->set_name("ERASE (X)");
		paintBtn->set_name("# PAINT (C) #");

		action = PAINT;
		break;
	}


	default:
		break;
	}


}



void Initialize()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	GLuint basicVert = createShader("../Shaders/basic.vert", "vertex");
	GLuint basicFrag = createShader("../Shaders/basic.frag", "fragment");
	basicShader = createProgram(basicVert, basicFrag);

	srand(static_cast <unsigned> (time(0)));

	// block initialization
	GLfloat coord_x, coord_y, coord_z;
	vec3 color;
	activeBlocks.clear();

	for (GLuint x = 0; x < LENGTH_X; x++)
	{
		for (GLuint y = 0; y < LENGTH_Y; y++)
		{
			for (GLuint z = 0; z < LENGTH_Z; z++)
			{
				coord_x = x - (GLfloat)(LENGTH_X - 1) / 2.0f;
				coord_y = y + 0.5f;
				coord_z = z - (GLfloat)(LENGTH_Z - 1) / 2.0f;

				blocks[x][y][z] = new Block(coord_x, coord_y, coord_z, x, y, z);

				//color = vec3(static_cast <GLfloat> (rand()) / static_cast <GLfloat> (RAND_MAX),
				//		 	 static_cast <GLfloat> (rand()) / static_cast <GLfloat> (RAND_MAX),
				//		 	 static_cast <GLfloat> (rand()) / static_cast <GLfloat> (RAND_MAX));
				color = colorPalette[0][5];
				blocks[x][y][z]->SetColor(color);
				//blocks[x][y][z]->SetActive(true);
				//if (blocks[x][y][z]->IsActive())
				//	activeBlocks.push_back(blocks[x][y][z]);

			}
		}
	}

	for (GLuint x = 0; x < LENGTH_X; x++)
	{
		for (GLuint y = 0; y < LENGTH_Y; y++)
		{
			for (GLuint z = 0; z < LENGTH_Z; z++)
			{
				if (z != LENGTH_Z - 1)
					blocks[x][y][z]->SetAdjacentBlock("front", blocks[x][y][z + 1]);
				if (z != 0)
					blocks[x][y][z]->SetAdjacentBlock("back", blocks[x][y][z - 1]);
				if (x != 0)
					blocks[x][y][z]->SetAdjacentBlock("left", blocks[x - 1][y][z]);
				if (x != LENGTH_X - 1)
					blocks[x][y][z]->SetAdjacentBlock("right", blocks[x + 1][y][z]);
				if (y != LENGTH_Y - 1)
					blocks[x][y][z]->SetAdjacentBlock("top", blocks[x][y + 1][z]);
				if (y != 0)
					blocks[x][y][z]->SetAdjacentBlock("bottom", blocks[x][y - 1][z]);
			}
		}
	}

	CullHiddenBlocks();

	blockAttribs.clear();
	VtxAttrib vtxAttrib;
	for (GLuint i = 0; i < visibleBlocks.size(); i++)
	{
		// 6 faces
		for (GLuint j = 0; j < FACE_PER_BLOCK; j++)
		{
			// 4 vertices
			for (GLuint k = 0; k < VERTEX_PER_FACE; k++)
			{
				
				Face face = visibleBlocks.at(i)->GetFace(j);
				vtxAttrib.coord_x = face.GetVertex(k).x;
				vtxAttrib.coord_y = face.GetVertex(k).y;
				vtxAttrib.coord_z = face.GetVertex(k).z;

				vtxAttrib.color_x = face.GetColor().x;
				vtxAttrib.color_y = face.GetColor().y;
				vtxAttrib.color_z = face.GetColor().z;

				vtxAttrib.normal_x = face.GetNormal().x;
				vtxAttrib.normal_y = face.GetNormal().y;
				vtxAttrib.normal_z = face.GetNormal().z;

				blockAttribs.push_back(vtxAttrib);
			}
		}
	}

	vboIds = new GLuint[3];
	glGenBuffers(1, vboIds);

	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	//if (blockAttribs.size() != 0)
	//{
		glBufferData(GL_ARRAY_BUFFER,
					 sizeof(VtxAttrib) * blockAttribs.size(),
					 &blockAttribs.front(),
					 GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(0));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	//}


	mode = VOXEL;
	action = ATTACH;

	//ty = -(LENGTH_Y/3);
	zoom = (LENGTH_X + LENGTH_Z) * 1.3f;
	tx = (GLfloat) LENGTH_X / 8.0f;

	colorButtons[0][6].SetPicked(true);
}



void SetCameraView()
{
	if (isPerspective)
	{
		gluPerspective(45.0f, (GLfloat)windowWidth / (GLfloat)windowHeight, 0.1f, 500.0f);
	}
	else
	{
		glOrtho(-windowWidth  * zoom * orthoZoomScale,		// -x
				 windowWidth  * zoom * orthoZoomScale,		//  x
				-windowHeight * zoom * orthoZoomScale,		// -y
				 windowHeight * zoom * orthoZoomScale,		//	y
				 0.1, 500.0f);
	}
}



void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// background color
	glClearColor(bgColor_x, bgColor_y, bgColor_z, 1.0f);
	
	if (!isHideGui)
	{	// color palette gui
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, windowWidth, windowHeight, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//	2		  1 (pivot)
		//	 +------+
		//	 |      |
		//	 |      |
		//	 +------+
		//	3		  4

		glBegin(GL_QUADS);
		for (GLint id_y = 0; id_y < BUTTON_ROW_NUM; id_y++)
		{
			for (GLint id_x = 0; id_x < BUTTON_COLUMN_NUM; id_x++)
			{
				vec3 color = colorButtons[id_x][id_y].GetColor();
				vec2 coords[4];

				for (GLint i = 0; i < VERTEX_PER_FACE; i++)
					coords[i] = colorButtons[id_x][id_y].GetVertex(i);

				glColor3f(color.x, color.y, color.z);
				glVertex2i(coords[0].x, coords[0].y);
				glVertex2i(coords[1].x, coords[1].y);
				glVertex2i(coords[2].x, coords[2].y);
				glVertex2i(coords[3].x, coords[3].y);
			}
		}
		glEnd();

		// picked color outline
		glBegin(GL_LINES);
		for (GLint id_y = 0; id_y < BUTTON_ROW_NUM; id_y++)
		{
			for (GLint id_x = 0; id_x < BUTTON_COLUMN_NUM; id_x++)
			{
				vec2 coords[4];
				for (GLint i = 0; i < VERTEX_PER_FACE; i++)
					coords[i] = colorButtons[id_x][id_y].GetVertex(i);
				if (colorButtons[id_x][id_y].IsPicked())
				{
					glColor3f(1.0f, 1.0f, 1.0f);
					glVertex2i(coords[0].x + 1.0f, coords[0].y - 1.0f);
					glVertex2i(coords[1].x - 1.0f, coords[1].y - 1.0f);

					glVertex2i(coords[1].x - 1.0f, coords[1].y - 1.0f);
					glVertex2i(coords[2].x - 1.0f, coords[2].y + 1.0f);

					glVertex2i(coords[2].x - 1.0f, coords[2].y + 1.0f);
					glVertex2i(coords[3].x + 1.0f, coords[3].y + 1.0f);

					glVertex2i(coords[3].x + 1.0f, coords[3].y + 1.0f);
					glVertex2i(coords[0].x + 1.0f, coords[0].y - 1.0f);
				}
			}
		}
		glEnd();
	}
	// main scene
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	SetCameraView();
	GLfloat pmat4[16];
	glGetFloatv(GL_PROJECTION_MATRIX, pmat4);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLfloat mvmat4_light[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mvmat4_light);

	//glLoadIdentity();
	glTranslatef(0, 0, -zoom);
	glTranslatef(tx, ty, 0);
	glRotatef(rotx, 1, 0, 0);
	glRotatef(roty, 0, 1, 0);

	GLfloat mvmat4[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mvmat4);

	
	// base ground plane
	if (isDrawGround)
	{
		glBegin(GL_QUADS);
		glColor3f(0.737f, 0.882f, 1.0f);
		glVertex3f(LENGTH_X, -0.1, LENGTH_Z);
		glVertex3f(LENGTH_X, -0.1, -LENGTH_Z);
		glVertex3f(-LENGTH_X, -0.1, -LENGTH_Z);
		glVertex3f(-LENGTH_X, -0.1, LENGTH_Z);
		glEnd();
	}

	GLfloat gridOffset_x = LENGTH_X % 2 == 1 ? 0.5f : 0.0f;
	GLfloat gridOffset_z = LENGTH_Z % 2 == 1 ? 0.5f : 0.0f;

	// base grid
	if (isDrawGrid)
	{
		glLineWidth(1.0f);
		glBegin(GL_LINES);
		glColor3f(0.5f, 0.5f, 0.5f);
		for (GLint i = floor((GLfloat)-LENGTH_X / 2); i <= LENGTH_X / 2; i++)
		{

			glVertex3f(i + gridOffset_x, 0, -(LENGTH_Z / 2 + gridOffset_z));
			glVertex3f(i + gridOffset_x, 0, LENGTH_Z / 2 + gridOffset_z);
		}
		for (GLint i = floor((GLfloat)-LENGTH_Z / 2); i <= LENGTH_Z / 2; i++)
		{
			glVertex3f(LENGTH_X / 2 + gridOffset_x, 0, i + gridOffset_z);
			glVertex3f(-(LENGTH_X / 2 + gridOffset_x), 0, i + gridOffset_z);
		}
		glEnd();
	}


	// xyz axises
	if (isDrawAxis)
	{
		GLfloat axisOffset_x = 0.025f + gridOffset_x;
		GLfloat axisOffset_y = 0.025f;
		GLfloat axisOffset_z = 0.025f + gridOffset_z;
		glLineWidth(3.0f);
		glBegin(GL_LINES);
		// x-axis
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-(LENGTH_X / 2 + axisOffset_x), -axisOffset_y, LENGTH_Z / 2 + axisOffset_z);
		glVertex3f(LENGTH_X / 2 + axisOffset_x, -axisOffset_y, LENGTH_Z / 2 + axisOffset_z);

		// y-axis
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-(LENGTH_X / 2 + axisOffset_x), -axisOffset_y, LENGTH_Z / 2 + axisOffset_z);
		glVertex3f(-(LENGTH_X / 2 + axisOffset_x), LENGTH_Y - axisOffset_y, LENGTH_Z / 2 + axisOffset_z);

		// z-axis
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-(LENGTH_X / 2 + axisOffset_x), -axisOffset_y, LENGTH_Z / 2 + axisOffset_z);
		glVertex3f(-(LENGTH_X / 2 + axisOffset_x), -axisOffset_y, -(LENGTH_Z / 2 + axisOffset_z));
		glEnd();
	}

	GLint loc_pmat  = glGetUniformLocation(basicShader, "u_projection");
	GLint loc_mvmat = glGetUniformLocation(basicShader, "u_modelview");
	GLint loc_mvmat_light = glGetUniformLocation(basicShader, "u_modelview_light");
	GLint loc_light0pos = glGetUniformLocation(basicShader, "u_light0_pos");
	GLint loc_light1pos = glGetUniformLocation(basicShader, "u_light1_pos");

	glUseProgram(basicShader);
		glUniformMatrix4fv(loc_pmat, 1, GL_FALSE, pmat4);
		glUniformMatrix4fv(loc_mvmat, 1, GL_FALSE, mvmat4);
		glUniformMatrix4fv(loc_mvmat_light, 1, GL_FALSE, mvmat4_light);
		glUniform4f(loc_light0pos, light0_pos.x, light0_pos.y, light0_pos.z, 1.0f);
		glUniform4f(loc_light1pos, light1_pos.x, light1_pos.y, light1_pos.z, 1.0f);

		// draw
		glDrawArrays(GL_QUADS,
					 0,
					 VERTEX_PER_FACE * FACE_PER_BLOCK * visibleBlocks.size());

	glUseProgram(0);

	

	glutSwapBuffers();
}



Ray ComputeCursorRay(GLint x, GLint y)
{
	Ray ray;
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat  window_x, window_y;
	GLdouble origin_x, origin_y, origin_z;
	GLdouble end_x, end_y, end_z;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	window_x = (GLfloat)x;
	window_y = (GLfloat)viewport[3] - (GLfloat)y;

	gluUnProject(window_x, window_y, 0.0, modelview, projection, viewport, &origin_x, &origin_y, &origin_z);
	gluUnProject(window_x, window_y, 1.0, modelview, projection, viewport, &end_x, &end_y, &end_z);

	ray.SetRay(vec3(origin_x, origin_y, origin_z), vec3(end_x, end_y, end_z));

	return ray;
}



GLfloat HitTest(Face face, Ray ray)
{
	vec3 R1 = ray.GetOrigin();
	vec3 R2 = ray.GetEnd();

	vec3 vtx1 = face.GetVertex(0);
	vec3 vtx2 = face.GetVertex(1);
	vec3 vtx3 = face.GetVertex(3);

	vec3 dS21 = vtx2 - vtx1;
	vec3 dS31 = vtx3 - vtx1;
	vec3 n = face.GetNormal();

	vec3 dR = R2 - R1;
	GLfloat ndotdR = dot(n, dR);

	if (abs(ndotdR) < 1e-6f || ndotdR > 0.0f)
		return -1;

	GLfloat t = dot(-n, R1 - vtx1) / ndotdR;

	vec3 M = R1 + dR * t;

	vec3 dMS1 = M - vtx1;
	GLfloat u = dot(dMS1, dS21);
	GLfloat v = dot(dMS1, dS31);

	if (u >= 0.0f && u <= dot(dS21, dS21) && 
		v >= 0.0f && v <= dot(dS31, dS31) && ndotdR < 0.0f)
		return t;	// hit
	else
		return -1;	// miss
}



vector<Block*> BFS(Block* firstBlock, GLuint face_idx)
{
	queue<Block*> q;
	Block *currentBlock;
	Block *adjBlock;
	vec3 originalColor;
	vector<Block*> connectedBlocks;

	for (GLuint x = 0; x < LENGTH_X; x++)
		for (GLuint y = 0; y < LENGTH_Y; y++)
			for (GLuint z = 0; z < LENGTH_Z; z++)
				blocks[x][y][z]->SetVisited(false);

	originalColor = firstBlock->GetColor();
	firstBlock->SetVisited(true);
	connectedBlocks.push_back(firstBlock);
	q.push(firstBlock);

	while (!q.empty())
	{
		currentBlock = q.front();
		q.pop();

		// front & back
		if (face_idx == 0 || face_idx == 1)
		{
			for (GLuint i = 2; i < 6; i++)
			{
				adjBlock = currentBlock->GetAdjacentBlock(i);
				if (adjBlock != NULL &&
					adjBlock->IsActive() &&
					((adjBlock->GetAdjacentBlock(face_idx) != NULL && !adjBlock->GetAdjacentBlock(face_idx)->IsActive())
						|| (adjBlock->GetIndex().z == LENGTH_Z - 1 && face_idx != 1) 
						|| (adjBlock->GetIndex().z == 0 && face_idx != 0)) &&
					!adjBlock->IsVisited() &&
					adjBlock->GetColor() == originalColor)
				{
					adjBlock->SetVisited(true);
					connectedBlocks.push_back(adjBlock);
					q.push(adjBlock);
				}
			}
		}
		// left & right
		else if (face_idx == 2 || face_idx == 3)
		{
			for (GLuint i = 0; i < 2; i++)
			{
				adjBlock = currentBlock->GetAdjacentBlock(i);
				if (adjBlock != NULL &&
					adjBlock->IsActive() &&
					((adjBlock->GetAdjacentBlock(face_idx) != NULL && !adjBlock->GetAdjacentBlock(face_idx)->IsActive())
						|| (adjBlock->GetIndex().x == LENGTH_X - 1 && face_idx != 2)
						|| (adjBlock->GetIndex().x == 0 && face_idx != 3)) &&
					!adjBlock->IsVisited() &&
					adjBlock->GetColor() == originalColor)
				{
					adjBlock->SetVisited(true);
					connectedBlocks.push_back(adjBlock);
					q.push(adjBlock);
				}
			}

			for (GLuint i = 4; i < 6; i++)
			{
				adjBlock = currentBlock->GetAdjacentBlock(i);
				if (adjBlock != NULL &&
					adjBlock->IsActive() &&
					((adjBlock->GetAdjacentBlock(face_idx) != NULL && !adjBlock->GetAdjacentBlock(face_idx)->IsActive())
						|| (adjBlock->GetIndex().x == LENGTH_X - 1 && face_idx != 2)
						|| (adjBlock->GetIndex().x == 0 && face_idx != 3)) &&
					!adjBlock->IsVisited() &&
					adjBlock->GetColor() == originalColor)
				{
					adjBlock->SetVisited(true);
					connectedBlocks.push_back(adjBlock);
					q.push(adjBlock);
				}
			}
		}
		// top & bottom
		else if (face_idx == 4 || face_idx == 5)
		{
			for (GLuint i = 0; i < 4; i++)
			{
				adjBlock = currentBlock->GetAdjacentBlock(i);
				if (adjBlock != NULL &&
					adjBlock->IsActive() &&
					((adjBlock->GetAdjacentBlock(face_idx) != NULL && !adjBlock->GetAdjacentBlock(face_idx)->IsActive())
						|| (adjBlock->GetIndex().y == LENGTH_Y - 1 && face_idx != 5)
						|| (adjBlock->GetIndex().y == 0 && face_idx != 4)) &&
					!adjBlock->IsVisited() &&
					adjBlock->GetColor() == originalColor)
				{
					adjBlock->SetVisited(true);
					connectedBlocks.push_back(adjBlock);
					q.push(adjBlock);
				}
			}
		}
	}

	return connectedBlocks;
}



void MirrorEdit(EditAction action, vector<Block*> &undoBlks, ivec3 blockId)
{
	GLint x = blockId.x;
	GLint y = blockId.y;
	GLint z = blockId.z;

	switch (action)
	{
		case ATTACH:
		{
			if (isMirrorEdit_x)
			{
				Block* mirrorBlock = blocks[LENGTH_X - 1 - x][y][z];
				if (!mirrorBlock->IsActive())
				{
					mirrorBlock->SetActive(true);
					mirrorBlock->SetColor(currentPaintColor);
					undoBlks.push_back(mirrorBlock);
				}
			}
			if (isMirrorEdit_z)
			{
				Block* mirrorBlock = blocks[x][y][LENGTH_Z - 1 - z];
				if (!mirrorBlock->IsActive())
				{
					mirrorBlock->SetActive(true);
					mirrorBlock->SetColor(currentPaintColor);
					undoBlks.push_back(mirrorBlock);
				}
			}
			if (isMirrorEdit_x && isMirrorEdit_z)
			{
				Block* mirrorBlock = blocks[LENGTH_X - 1 - x][y][LENGTH_Z - 1 - z];
				if (!mirrorBlock->IsActive())
				{
					mirrorBlock->SetActive(true);
					mirrorBlock->SetColor(currentPaintColor);
					undoBlks.push_back(mirrorBlock);
				}
			}

			break;
		}
		case ERASE:
		{
			if (isMirrorEdit_x)
			{
				Block* mirrorBlock = blocks[LENGTH_X - 1 - x][y][z];
				if (mirrorBlock->IsActive())
				{
					mirrorBlock->SetActive(false);
					undoBlks.push_back(mirrorBlock);
				}
			}
			if (isMirrorEdit_z)
			{
				Block* mirrorBlock = blocks[x][y][LENGTH_Z - 1 - z];
				if (mirrorBlock->IsActive())
				{
					mirrorBlock->SetActive(false);
					undoBlks.push_back(mirrorBlock);
				}
			}
			if (isMirrorEdit_x && isMirrorEdit_z)
			{
				Block* mirrorBlock = blocks[LENGTH_X - 1 - x][y][LENGTH_Z - 1 - z];
				if (mirrorBlock->IsActive())
				{
					mirrorBlock->SetActive(false);
					undoBlks.push_back(mirrorBlock);
				}
			}

			break;
		}
		case PAINT:
		{
			if (isMirrorEdit_x)
			{
				Block* mirrorBlock = blocks[LENGTH_X - 1 - x][y][z];
				if (mirrorBlock->GetColor() != currentPaintColor)
				{
					mirrorBlock->SetColor(currentPaintColor);
					undoBlks.push_back(mirrorBlock);
				}
			}
			if (isMirrorEdit_z)
			{
				Block* mirrorBlock = blocks[x][y][LENGTH_Z - 1 - z];
				if (mirrorBlock->GetColor() != currentPaintColor)
				{
					mirrorBlock->SetColor(currentPaintColor);
					undoBlks.push_back(mirrorBlock);
				}
			}
			if (isMirrorEdit_x && isMirrorEdit_z)
			{
				Block* mirrorBlock = blocks[LENGTH_X - 1 - x][y][LENGTH_Z - 1 - z];
				if (mirrorBlock->GetColor() != currentPaintColor)
				{
					mirrorBlock->SetColor(currentPaintColor);
					undoBlks.push_back(mirrorBlock);
				}
			}

			break;
		}
		default:
			break;
	}

	
}



void AttachBlock(EditMode mode, GLuint block_idx, GLuint face_idx)
{
	vector<Block*> undoBlocks;
	pair<EditAction, vector<Block*>> undoItem;
	pair<vec3, vec3> undoColor;
	switch (mode)
	{
		case VOXEL:
		{
			ivec3 idx = visibleBlocks.at(block_idx)->GetIndex();

			Block *newBlock;
			newBlock = visibleBlocks.at(block_idx)->GetAdjacentBlock(face_idx);

			if (newBlock != NULL)
			{
				newBlock->SetActive(true);
				newBlock->SetColor(currentPaintColor);

				undoBlocks.push_back(newBlock);

				ivec3 idx = newBlock->GetIndex();
				MirrorEdit(ATTACH, undoBlocks, idx);

				undoItem = make_pair(ATTACH, undoBlocks);
				undoStack.push(undoItem);
				undoColor = make_pair(currentPaintColor,
										currentPaintColor);
				undoColorStack.push(undoColor);

				
			}

			break;
		}
		case FACE:
		{
			vector<Block*> connectedBlocks;

			connectedBlocks.clear();
			connectedBlocks = BFS(visibleBlocks.at(block_idx), face_idx);

			// add blocks
			for (GLuint i = 0; i < connectedBlocks.size(); i++)
			{
				Block *newBlock = connectedBlocks.at(i)->GetAdjacentBlock(face_idx);
				if (newBlock != NULL)
				{
					newBlock->SetActive(true);
					newBlock->SetColor(currentPaintColor);

					undoBlocks.push_back(newBlock);

					ivec3 idx = newBlock->GetIndex();
					MirrorEdit(ATTACH, undoBlocks, idx);
					

				}
			}

			if (undoBlocks.size() != 0)
			{
				undoItem = make_pair(ATTACH, undoBlocks);
				undoStack.push(undoItem);
				undoColor = make_pair(currentPaintColor,
					currentPaintColor);
				undoColorStack.push(undoColor);
			}
			break;
		}
		default:
			break;
	}
}



void EraseBlock(EditMode mode, GLuint block_idx, GLuint face_idx)
{
	vector<Block*> undoBlocks;
	pair<EditAction, vector<Block*>> undoItem;
	pair<vec3, vec3> undoColor;
	switch (mode)
	{
		case VOXEL:
		{
			// not allowed to delete the last block
			//if (visibleBlocks.size() == 1)
			//	return;

			visibleBlocks.at(block_idx)->SetActive(false);
			
			// only single one
			undoBlocks.push_back(visibleBlocks.at(block_idx));

			ivec3 idx = visibleBlocks.at(block_idx)->GetIndex();
			MirrorEdit(ERASE, undoBlocks, idx);

			undoItem = make_pair(ERASE, undoBlocks);
			undoStack.push(undoItem);
			undoColor = make_pair(visibleBlocks.at(block_idx)->GetColor(),
									visibleBlocks.at(block_idx)->GetColor());
			undoColorStack.push(undoColor);

			break;
		}
		case FACE:
		{
			vector<Block*> deletedBlocks;

			deletedBlocks.clear();
			deletedBlocks = BFS(visibleBlocks.at(block_idx), face_idx);

			// last face
			//if (deletedBlocks.size() == activeBlocks.size())
			//	return;

			// erase
			for (GLuint i = 0; i < deletedBlocks.size(); i++)
			{
				deletedBlocks.at(i)->SetActive(false);

				undoBlocks.push_back(deletedBlocks.at(i));

				ivec3 idx = deletedBlocks.at(i)->GetIndex();
				MirrorEdit(ERASE, undoBlocks, idx);
			}

			undoItem = make_pair(ERASE, undoBlocks);
			undoStack.push(undoItem);
			undoColor = make_pair(visibleBlocks.at(block_idx)->GetColor(),
									visibleBlocks.at(block_idx)->GetColor());
			undoColorStack.push(undoColor);

			break;
		}
		default:
			break;
	}

}



void PaintBlock(EditMode mode, GLuint block_idx, GLuint face_idx)
{
	if (visibleBlocks.at(block_idx)->GetColor() == currentPaintColor)
		return;

	vector<Block*> undoBlocks;
	pair<EditAction, vector<Block*>> undoItem;
	pair<vec3, vec3> undoColor;
	switch (mode)
	{
		case VOXEL:
		{
			// push color before changing it
			undoColor = make_pair(visibleBlocks.at(block_idx)->GetColor(),
									currentPaintColor);
			undoColorStack.push(undoColor);

			visibleBlocks.at(block_idx)->SetColor(currentPaintColor);

			undoBlocks.push_back(visibleBlocks.at(block_idx));

			ivec3 idx = visibleBlocks.at(block_idx)->GetIndex();
			MirrorEdit(PAINT, undoBlocks, idx);

			undoItem = make_pair(PAINT, undoBlocks);
			undoStack.push(undoItem);
			
			break; 
		}
		case FACE:
		{
			vector<Block*> paintedBlocks;

			paintedBlocks.clear();
			paintedBlocks = BFS(visibleBlocks.at(block_idx), face_idx);

			undoColor = make_pair(visibleBlocks.at(block_idx)->GetColor(),
									currentPaintColor);
			undoColorStack.push(undoColor);

			// paint
			for (GLuint i = 0; i < paintedBlocks.size(); i++)
			{
				paintedBlocks.at(i)->SetColor(currentPaintColor);

				undoBlocks.push_back(paintedBlocks.at(i));

				ivec3 idx = paintedBlocks.at(i)->GetIndex();
				MirrorEdit(PAINT, undoBlocks, idx);
			}

			undoItem = make_pair(PAINT, undoBlocks);
			undoStack.push(undoItem);

			break;
		}
		default:
			break;
	}

}



void UndoEdit(EditAction action, vector<Block*> undoBlocks)
{
	// do the inverse operation
	switch (action)
	{
		case ATTACH:
		{	// erase attached blocks
			pair<vec3, vec3> undoColor = undoColorStack.top();
			redoColorStack.push(undoColor);
			undoColorStack.pop();
			for (GLuint i = 0; i < undoBlocks.size(); i++)
			{
				undoBlocks.at(i)->SetActive(false);
			}
			break;
		}
		case ERASE:
		{	// attach erased blocks
			pair<vec3, vec3> undoColor = undoColorStack.top();
			redoColorStack.push(undoColor);
			undoColorStack.pop();
			for (GLuint i = 0; i < undoBlocks.size(); i++)
			{
				undoBlocks.at(i)->SetActive(true);
				undoBlocks.at(i)->SetColor(undoColor.first);
			}
			break;
		}
		case PAINT:
		{
			pair<vec3, vec3> undoColor = undoColorStack.top();
			redoColorStack.push(undoColor);
			undoColorStack.pop();
			for (GLuint i = 0; i < undoBlocks.size(); i++)
			{
				undoBlocks.at(i)->SetColor(undoColor.first);
			}
			break;
		}
		default:
			break;
	}
}



void RedoEdit(EditAction action, vector<Block*> redoBlocks)
{
	// do the same operation
	switch (action)
	{
		case ATTACH:
		{	
			pair<vec3, vec3> undoColor = redoColorStack.top();
			undoColorStack.push(undoColor);
			redoColorStack.pop();
			for (GLuint i = 0; i < redoBlocks.size(); i++)
			{
				redoBlocks.at(i)->SetActive(true);
				redoBlocks.at(i)->SetColor(undoColor.first);
			}
			break;
		}
		case ERASE:
		{
			pair<vec3, vec3> undoColor = redoColorStack.top();
			undoColorStack.push(undoColor);
			redoColorStack.pop();
			for (GLuint i = 0; i < redoBlocks.size(); i++)
			{
				redoBlocks.at(i)->SetActive(false);
			}
			break;
		}
		case PAINT:
		{
			pair<vec3, vec3> undoColor = redoColorStack.top();
			undoColorStack.push(undoColor);
			redoColorStack.pop();
			for (GLuint i = 0; i < redoBlocks.size(); i++)
			{
				redoBlocks.at(i)->SetColor(undoColor.second);
			}
			break;
		}
		default:
			break;
	}
}




void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// check color palette
		GLfloat right_x, left_x, top_y, bottom_y;
		GLint picked_x, picked_y;
		GLboolean isColorPicked = false;

		for (GLint id_y = 0; id_y < BUTTON_ROW_NUM; id_y++)
		{
			for (GLint id_x = 0; id_x < BUTTON_COLUMN_NUM; id_x++)
			{
				right_x = colorButtons[id_x][id_y].GetVertex(0).x;
				left_x = colorButtons[id_x][id_y].GetVertex(1).x;
				top_y = colorButtons[id_x][id_y].GetVertex(0).y;
				bottom_y = colorButtons[id_x][id_y].GetVertex(2).y;
				
				if (x <= right_x && x >= left_x && y >= top_y && y <= bottom_y)
				{
					isColorPicked = true;
					picked_x = id_x;
					picked_y = id_y;
				}
			}
		}

		if (isColorPicked)
		{
			for (GLint id_y = 0; id_y < BUTTON_ROW_NUM; id_y++)
				for (GLint id_x = 0; id_x < BUTTON_COLUMN_NUM; id_x++)
					colorButtons[id_x][id_y].SetPicked(false);

			colorButtons[picked_x][picked_y].SetPicked(true);
			currentPaintColor = colorButtons[picked_x][picked_y].GetColor();
			return;
		}


		// check all visible blocks
		GLfloat t, min_t = 100.0f;
		GLint block_idx_in_vector, face_idx;
		GLboolean isHitBlock = false;
		Ray cursorRay;
		cursorRay = ComputeCursorRay(x, y);

		for (GLuint i = 0; i < visibleBlocks.size(); i++)
		{
			/*  
			if (!visibleBlocks.at(i)->IsActive())
				continue;
			*/

			for (GLuint j = 0; j < FACE_PER_BLOCK; j++)
			{
				t = HitTest(visibleBlocks.at(i)->GetFace(j), cursorRay);
				if (t > 0 && t < min_t)
				{
					min_t = t;
					block_idx_in_vector = i;
					face_idx = j;
					isHitBlock = true;
				}
			}
		}

		if (isHitBlock)
		{
			GLint mod = glutGetModifiers();

			// pick color from block
			if (mod & GLUT_ACTIVE_ALT)
			{
				currentPaintColor = visibleBlocks.at(block_idx_in_vector)->GetColor();

				for (GLint id_y = 0; id_y < BUTTON_ROW_NUM; id_y++)
					for (GLint id_x = 0; id_x < BUTTON_COLUMN_NUM; id_x++)
						if (colorButtons[id_x][id_y].GetColor() == currentPaintColor)
							colorButtons[id_x][id_y].SetPicked(true);
						else
							colorButtons[id_x][id_y].SetPicked(false);
							
				
				glutPostRedisplay();
				return;
			}

			// clear redo stacks when editing
			stack<pair<EditAction, vector<Block*>>> emptyRedoStack;
			stack<pair<vec3, vec3>> emptyColorRedoStack;
			redoStack.swap(emptyRedoStack);
			redoColorStack.swap(emptyColorRedoStack);

			switch (action)
			{
			case ATTACH:
				AttachBlock(mode, block_idx_in_vector, face_idx);
				break;
			case ERASE:
				EraseBlock(mode, block_idx_in_vector, face_idx);
				break;
			case PAINT:
				PaintBlock(mode, block_idx_in_vector, face_idx);
				break;
			default:
				break;
			}
		}
		else
		{
			// check ground intersection

			if (action != ATTACH)
				return;

			vec3 R1 = cursorRay.GetOrigin();
			vec3 R2 = cursorRay.GetEnd();

			vec3 vtx1 = vec3(LENGTH_X, -0.1, LENGTH_Z);
			vec3 vtx2 = vec3(LENGTH_X, -0.1, -LENGTH_Z);
			vec3 vtx3 = vec3(-LENGTH_X, -0.1, LENGTH_Z);

			vec3 dS21 = vtx2 - vtx1;
			vec3 dS31 = vtx3 - vtx1;
			vec3 n = vec3(0.0f, 1.0f, 0.0f);

			vec3 dR = R2 - R1;
			GLfloat ndotdR = dot(n, dR);

			if (abs(ndotdR) < 1e-6f || ndotdR > 0.0f)
				return;

			GLfloat t = dot(-n, R1 - vtx1) / ndotdR;

			vec3 M = R1 + dR * t;

			vec3 dMS1 = M - vtx1;
			GLfloat u = dot(dMS1, dS21);
			GLfloat v = dot(dMS1, dS31);

			// check if hitting the ground
			if (u >= 0.0f && u <= dot(dS21, dS21) &&
				v >= 0.0f && v <= dot(dS31, dS31) && ndotdR < 0.0f)
			{
				// check if within drawing range
				if (M.x >= (GLfloat)LENGTH_X / 2.0f || M.x <= -(GLfloat)LENGTH_X / 2.0f ||
					M.z >= (GLfloat)LENGTH_Z / 2.0f || M.z <= -(GLfloat)LENGTH_Z / 2.0f)
					return;

				stack<pair<EditAction, vector<Block*>>> emptyRedoStack;
				stack<pair<vec3, vec3>> emptyColorRedoStack;
				redoStack.swap(emptyRedoStack);
				redoColorStack.swap(emptyColorRedoStack);

				vector<Block*> undoBlocks;
				pair<EditAction, vector<Block*>> undoItem;
				pair<vec3, vec3> undoColor;
				switch (mode)
				{
					case VOXEL:
					{
						// for even length: floor(M.x) + 0.5 
						// for odd length:  floor(M.x + 0.5)

						GLfloat coord_x = LENGTH_X % 2 == 1 ? floor(M.x + 0.5) : floor(M.x) + 0.5;
						GLfloat coord_z = LENGTH_Z % 2 == 1 ? floor(M.z + 0.5) : floor(M.z) + 0.5;

						GLint x = coord_x + (GLfloat)(LENGTH_X - 1) / 2.0f;
						GLint z = coord_z + (GLfloat)(LENGTH_Z - 1) / 2.0f;

						blocks[x][0][z]->SetActive(true);
						blocks[x][0][z]->SetColor(currentPaintColor);
						undoBlocks.push_back(blocks[x][0][z]);

						MirrorEdit(ATTACH, undoBlocks, ivec3(x, 0, z));

						undoItem = make_pair(ATTACH, undoBlocks);
						undoStack.push(undoItem);
						undoColor = make_pair(currentPaintColor,
												currentPaintColor);
						undoColorStack.push(undoColor);

						break;
					}
					case FACE:
					{
						GLfloat coord_x = LENGTH_X % 2 == 1 ? floor(M.x + 0.5) : floor(M.x) + 0.5;
						GLfloat coord_z = LENGTH_Z % 2 == 1 ? floor(M.z + 0.5) : floor(M.z) + 0.5;

						GLint x = coord_x + (GLfloat)(LENGTH_X - 1) / 2.0f;
						GLint z = coord_z + (GLfloat)(LENGTH_Z - 1) / 2.0f;

						// initial block
						Block *initialBlock = blocks[x][0][z];
						
						// BFS for ground
						queue<Block*> q;
						Block *currentBlock;
						Block *adjBlock;
						vec3 originalColor; 
						vector<Block*> connectedBlocks;
						connectedBlocks.clear();

						for (GLuint x = 0; x < LENGTH_X; x++)
							for (GLuint y = 0; y < LENGTH_Y; y++)
								for (GLuint z = 0; z < LENGTH_Z; z++)
									blocks[x][y][z]->SetVisited(false);

						originalColor = initialBlock->GetColor();
						initialBlock->SetVisited(true);
						connectedBlocks.push_back(initialBlock);
						q.push(initialBlock);

						while (!q.empty())
						{
							currentBlock = q.front();
							q.pop();

							for (GLuint i = 0; i < 4; i++)
							{
								adjBlock = currentBlock->GetAdjacentBlock(i);
								if (adjBlock != NULL &&
									!adjBlock->IsActive() &&
									!adjBlock->IsVisited())
								{
									adjBlock->SetVisited(true);
									connectedBlocks.push_back(adjBlock);
									q.push(adjBlock);
								}
							}
						}


						for (GLuint i = 0; i < connectedBlocks.size(); i++)
						{
							connectedBlocks.at(i)->SetActive(true);
							connectedBlocks.at(i)->SetColor(currentPaintColor);

							undoBlocks.push_back(connectedBlocks.at(i));

							ivec3 idx = connectedBlocks.at(i)->GetIndex();
							MirrorEdit(ATTACH, undoBlocks, idx);
							
						}

						undoItem = make_pair(ATTACH, undoBlocks);
						undoStack.push(undoItem); 
						undoColor = make_pair(currentPaintColor,
												currentPaintColor);
						undoColorStack.push(undoColor);

						break;

					}
					default:
						break;
				}
			}
			else
			{	
				// miss
				return;
			}
		}
		UpdateActiveBlocks();
		UpdateVBO();

	}

	// Zoom
	else if (button == 3 || button == 4)
	{
		if (state == GLUT_UP) 
			return;

		GLint zoomSpeed = 5;
		GLfloat minDistance = 10.0f;
		GLfloat maxDistance = 300.0f;
		GLint dir = (button == 3) ? 1 : -1;

		zoom -= zoomSpeed * dir;
		zoom = zoom < minDistance ? minDistance : zoom;
		zoom = zoom > maxDistance ? maxDistance : zoom;
	}

	// Pan
	else if (button == GLUT_MIDDLE_BUTTON)
	{
		isPanning = ((GLUT_DOWN == state) ? true : false);
		lastx = x;
		lasty = y;
	}

	// Rotate
	else if (button == GLUT_RIGHT_BUTTON)
	{
		isRotating = ((GLUT_DOWN == state) ? true : false);
		lastx = x;
		lasty = y;
	}

	glutPostRedisplay();
}



void MouseMotion(int x, int y)
{
	GLint diffx = x - lastx;
	GLint diffy = y - lasty;
	lastx = x;
	lasty = y;

	if (isPanning)
	{
		tx += (GLfloat) 0.001f * zoom * diffx;
		ty -= (GLfloat) 0.001f * zoom * diffy;
	}

	else if (isRotating)
	{
		rotx += (GLfloat) 0.5f * diffy;
		// clamp
		if (rotx > 90.0f) rotx = 90.0f;
		else if (rotx < -90.0f) rotx = -90.0f;
		
		roty += (GLfloat) 0.5f * diffx;
	}

	glutPostRedisplay();
}



void Keyboard(unsigned char key, int x, int y)
{
	GLint mod = glutGetModifiers();
	
	// undo
	if ((mod & GLUT_ACTIVE_CTRL) && (key == '\x1A')) // keycode for letter 'z'
	{
		if (undoStack.empty())
			return;
		
		pair<EditAction, vector<Block*>> undoItem;
		undoItem = undoStack.top();
		undoStack.pop();

		redoStack.push(undoItem);

		UndoEdit(undoItem.first, undoItem.second);

		UpdateActiveBlocks();
		UpdateVBO();

		glutPostRedisplay();
		return;
	}

	// redo
	else if ((mod & GLUT_ACTIVE_CTRL) && (key == '\x19')) // keycode for letter 'y'
	{
		if (redoStack.empty())
			return;

		pair<EditAction, vector<Block*>> redoItem;
		redoItem = redoStack.top();
		redoStack.pop();

		undoStack.push(redoItem);

		RedoEdit(redoItem.first, redoItem.second);

		UpdateActiveBlocks();
		UpdateVBO();

		glutPostRedisplay();
		return;
	}

	// mirror shortcuts
	/*
	else if ((mod & GLUT_ACTIVE_ALT) && (key == 'x'))
	{
		isMirrorEdit_x = !isMirrorEdit_x;

		if (isMirrorEdit_x)
			cout << "x-mirror on" << endl;
		else
			cout << "x-mirror off" << endl;
		return;
	}
	else if ((mod & GLUT_ACTIVE_ALT) && (key == 'z'))
	{
		isMirrorEdit_z = !isMirrorEdit_z;

		if (isMirrorEdit_z)
			cout << "z-mirror on" << endl;
		else
			cout << "z-mirror off" << endl;
		return;
	}
	*/


	switch (key)
	{
		// reset the camera
		case 'r': case 'R':
		{
			tx = (GLfloat)LENGTH_X / 8.3f;
			ty = 0;
			//ty = -(LENGTH_Y/3);

			glutPostRedisplay();
			
			break;
		}

		case 'v': case 'V':
		{
			voxelModeBtn->set_name("# VOXEL (V) #");
			faceModeBtn->set_name("FACE (F)");

			mode = VOXEL;
			break;
		}

		case 'f': case 'F':
		{
			voxelModeBtn->set_name("VOXEL (V)");
			faceModeBtn->set_name("# FACE (F) #");

			mode = FACE;
			break;
		}

		case 'z': case 'Z':
		{
			attachBtn->set_name("# ATTACH (Z) #");
			eraseBtn->set_name("ERASE (X)");
			paintBtn->set_name("PAINT (C)");

			action = ATTACH;
			break;
		}

		case 'x': case 'X':
		{
			attachBtn->set_name("ATTACH (Z)");
			eraseBtn->set_name("# ERASE (X) #");
			paintBtn->set_name("PAINT (C)");

			action = ERASE;
			break;
		}

		case 'c': case 'C':
		{
			attachBtn->set_name("ATTACH (Z)");
			eraseBtn->set_name("ERASE (X)");
			paintBtn->set_name("# PAINT (C) #");

			action = PAINT;
			break;
		}

		// switch between perspective and orthographic
		case 'p': case 'P':
		{
			isPerspective = !isPerspective;
			glutPostRedisplay();

			break;
		}

		case 'h': case 'H':
		{
			isHideGui = !isHideGui;

			if (isHideGui)
				glui->hide();
			else
				glui->show();
			glutPostRedisplay();
			break;
		}

		/*
		// esc to close window
		case 27:
		{
			exit(0);
			break;
		}
		*/
		default:
		{
			break;
		}
	}

}



void Reshape(int width, int height)
{
	windowWidth = width;
	windowHeight = height;

	GLUI_Master.auto_set_viewport();


	GLfloat offset = 5.0f;
	for (GLint id_y = 0; id_y < BUTTON_ROW_NUM; id_y++)
	{
		for (GLint id_x = 0; id_x < BUTTON_COLUMN_NUM; id_x++)
		{
			vec2 pivotPos;
			pivotPos.x = windowWidth - id_x * BUTTON_SIZE - offset;
			pivotPos.y = id_y * BUTTON_SIZE + offset;

			colorButtons[id_x][id_y].SetPosition(pivotPos);
		}
	}

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	SetCameraView();
}



int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	//glutInitWindowPosition(0, 0);
	glutInitWindowSize(1280, 800);
	//glutInitWindowSize(1000, 800);

	windowWidth = 1280;
	windowHeight = 800;

	main_window = glutCreateWindow("JUST VOXEL"); 
	glutDisplayFunc(Display);
	//GLUI_Master.set_glutKeyboardFunc(Keyboard);
	//GLUI_Master.set_glutMouseFunc(MouseButton);
	GLUI_Master.set_glutReshapeFunc(Reshape);
	glutMotionFunc(MouseMotion);

	//glutReshapeFunc(Reshape);
	glutMouseFunc(MouseButton);
	glutKeyboardFunc(Keyboard);


	// main GUI
	glui = GLUI_Master.create_glui_subwindow(main_window, GLUI_SUBWINDOW_LEFT);

	glui->add_statictext("");
	glui->add_separator();
	GLUI_StaticText *title = glui->add_statictext("   JUST VOXEL");
	title->set_alignment(GLUI_ALIGN_CENTER);
	glui->add_separator();
	glui->add_statictext("");

	GLUI_Panel *toolPanel = glui->add_panel("TOOL");	glui->add_button_to_panel(toolPanel, "CLEAR", TOOL_CLEAR_ID, Control_Callback);	glui->add_button_to_panel(toolPanel, "FULL", TOOL_FULL_ID, Control_Callback);
	glui->add_statictext("");

	GLUI_Panel *modePanel = glui->add_panel("MODE");	voxelModeBtn = glui->add_button_to_panel(modePanel, "# VOXEL (V) #", MODE_VOXEL_ID, Control_Callback);	faceModeBtn = glui->add_button_to_panel(modePanel, "FACE (F)", MODE_FACE_ID, Control_Callback);
	glui->add_statictext("");

	GLUI_Panel *actionPanel = glui->add_panel("ACTION");	attachBtn = glui->add_button_to_panel(actionPanel, "# ATTACH (Z) #", ACTION_ATTACH_ID, Control_Callback);	eraseBtn = glui->add_button_to_panel(actionPanel, "ERASE (X)", ACTION_ERASE_ID, Control_Callback);	paintBtn =  glui->add_button_to_panel(actionPanel, "PAINT (C)", ACTION_PAINT_ID, Control_Callback);
	glui->add_statictext("");

	GLUI_Panel *mirrorModePanel = glui->add_panel("MIRROR");
	glui->add_checkbox_to_panel(mirrorModePanel, "X-AXIS", &isMirrorEdit_x);
	glui->add_checkbox_to_panel(mirrorModePanel, "Z-AXIS", &isMirrorEdit_z);
	glui->add_statictext("");

	GLUI_Panel *viewPanel = glui->add_panel("VIEW");
	glui->add_checkbox_to_panel(viewPanel, "GROUND", &isDrawGround);
	glui->add_checkbox_to_panel(viewPanel, "AXIS", &isDrawAxis);
	glui->add_checkbox_to_panel(viewPanel, "GRID", &isDrawGrid);
	glui->add_statictext("");

	GLUI_Panel *bgColorPanel = glui->add_panel("BACKGROUND");
	GLUI_Scrollbar *sb;
	sb = new GLUI_Scrollbar(bgColorPanel, "Red", GLUI_SCROLL_HORIZONTAL,
		&bgColor_x, BG_COLOR_ID, Control_Callback);
	sb->set_float_limits(0, 1);
	sb->set_w(120);
	sb = new GLUI_Scrollbar(bgColorPanel, "Green", GLUI_SCROLL_HORIZONTAL,
		&bgColor_y, BG_COLOR_ID, Control_Callback);
	sb->set_float_limits(0, 1);
	sb->set_w(120);
	sb = new GLUI_Scrollbar(bgColorPanel, "Blue", GLUI_SCROLL_HORIZONTAL,
		&bgColor_z, BG_COLOR_ID, Control_Callback);
	sb->set_float_limits(0, 1);
	sb->set_w(120);

	glui->add_statictext("");

	glui->add_button("QUIT", 0, (GLUI_Update_CB)exit);
	
	glui->set_main_gfx_window(main_window);
	GLUI_Master.set_glutIdleFunc(NULL);


	// color palette GUI
	GLfloat offset = 5.0f;
	for (GLint id_y = 0; id_y < BUTTON_ROW_NUM; id_y++)
	{
		for (GLint id_x = 0; id_x < BUTTON_COLUMN_NUM ; id_x++)
		{
			vec2 pivotPos;
			pivotPos.x = windowWidth - id_x * BUTTON_SIZE - offset;
			pivotPos.y = id_y * BUTTON_SIZE + offset;

			colorButtons[id_x][id_y] = ColorButton(pivotPos, colorPalette[id_x][id_y]);

		}
	}

	glewInit();
	Initialize();

	glutMainLoop();

	delete[] vboIds;
	delete[] &blocks;

	return 0;
}

