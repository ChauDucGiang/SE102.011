#pragma once

#include "GameObject.h"

#define HEIGHT_BLOCK 16.0f
#define HEIGHT_CAN_DOWN 15.9f
#define HEIGHT_CAN_UP 15.0f

//model
#define PLATFORM_BLOCK 1
#define PLATFORM_CAN_UP 2
#define PLATFORM_CAN_DOWN 2

// 
// The most popular type of object in Mario! 
// 
class CPlatform : public CGameObject
{
protected: 
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;

public: 
	CPlatform(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin = sprite_id_begin;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int GetLength() { return length; }
	float GetCellWidth() { return cellWidth; }
	float GetCellHeight() { return this->cellHeight; }
	float GetWidth() { return this->length * this->cellWidth; };

	bool IsPlatform() { return true; }

	bool IsNoneBlockObject() { return (cellHeight == 15.0f); };
	bool IsCanUp() { return (cellHeight == HEIGHT_CAN_UP); };
	bool IsCanDown() { return (cellHeight == HEIGHT_CAN_DOWN); }

	virtual int IsBlocking() { return true; }
};

typedef CPlatform* LPPLATFORM;