#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define ID_ANI_BRICK_COLOR 10001

#define BRICK_STATE_WAS_BROKEN 100
#define BRICK_STATE_TURNS_INTO_COIN 200
#define BRICK_STATE_NORMAL 300

class CBrickColor : public CGameObject
{
protected:
	int model;	
	bool isBreak = false, isCoin = false, isUsedSwitchPBlock = false;
public:
	CBrickColor(float x, float y, int model) : CGameObject(x, y) {
		this->model = model;
		SetState(BRICK_STATE_NORMAL);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	void IsUsedSwitchPBlock();
	void Destroy();
};

