#pragma once
#include "GameObject.h"

#define BOX_ITEM_BBOX_HEIGHT 16
#define BOX_ITEM_BBOX_WIDTH 16
#define BOX_ITEM_SPEED_Y 0.07f

#define BOX_ITEM_SWITCH_MODEL_TIME 150

#define ID_ANI_ITEM_MUSHROOM 24781
#define ID_ANI_ITEM_FLOWER 24786
#define ID_ANI_ITEM_STAR 24791

#define BOX_ITEM_MUSHROOM 1
#define BOX_ITEM_FLOWER 2
#define BOX_ITEM_STAR 3

#define BOX_ITEM_STATE_COLLECTED 100

class CBoxItem : public CGameObject
{
protected: 
	int model;
	bool isCollected = false;
	ULONGLONG switchModelStart;

public:
	CBoxItem(float, float y);

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnNoCollision(DWORD dt);

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 1; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetState(int state);

	void SwitchModel();

};