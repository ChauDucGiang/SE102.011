#pragma once

#include "GameObject.h"

#define HEIGHT_CAN_DOWN 15.9f

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
	virtual int IsBlocking() { return 1; }
	bool IsPlatform() { return true; }
	bool IsNoneBlockObject() { return (cellHeight != 16); };
	bool IsCanDown() { return (cellHeight == HEIGHT_CAN_DOWN); }
};

typedef CPlatform* LPPLATFORM;