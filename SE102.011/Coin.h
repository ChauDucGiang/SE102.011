#pragma once

#include "GameObject.h"

#define ID_ANI_COIN 11000
#define ID_ANI_COIN_IDLE 11601
#define COIN_GRAVITY 0.0003f
#define OUT_BRICK_SPEED_Y 0.2f
#define COIN_MAX_SPEED_FALL 0.1f
#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16
#define COIN_SUMMON_STATE	100
#define COIN_NOT_SUMMON_STATE	200

class CCoin : public CGameObject {
protected:
	int state;
	float ay;
public:
	CCoin(float x, float y) : CGameObject(x, y) {
		ay = COIN_GRAVITY;
	}
	void Render();
	virtual int IsCollidable() { return 1; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	void SetState(int state);
};