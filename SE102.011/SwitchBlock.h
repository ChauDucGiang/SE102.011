#pragma once
#include "GameObject.h"

#define ID_ANI_SWITCH_BLOCK_NORMAL 13131
#define ID_ANI_SWITCH_BLOCK_WAS_COLLECTED 13132
#define SWITCH_BLOCK_BBOX_WIDTH 10
#define SWITCH_BLOCK_BBOX_HEIGHT 16
#define SWITCH_BLOCK_GRAVITY 0.0003f;

class CSwitchBlock : public CGameObject
{
	float ay, startY;
	bool wasCollected = false;

public:
	CSwitchBlock(float x, float y);

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsCollidable() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual int IsBlocking() { return 0; }

	//get/set
	bool WasCollected() { return wasCollected; }
	void SetWasCollected(bool wasCollected){ this->wasCollected = wasCollected; }

};