#pragma once

#include "GameObject.h"

#define ID_ANI_COIN 11000
#define ID_ANI_COIN_IDLE 11601
#define COIN_GRAVITY 0.0003f
#define COIN_OUT_BRICK_SPEED_Y 0.2f
#define COIN_MAX_SPEED_FALL 0.1f
#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16
#define COIN_SUMMON_STATE	100
#define COIN_NOT_SUMMON_STATE	200

#define COIN_NORMAL	1
#define COIN_TURNED_INTO_BRICK	2
#define COIN_TURN_INTO_BRICK_TIME 10000


class CCoin : public CGameObject {
protected:
	int state, model;
	float ay;
	ULONGLONG turnedIntoBrickStart;
public:
	CCoin(float x, float y, int model = 1) : CGameObject(x, y) {
		ay = COIN_GRAVITY;
		this->model = model;
		if (model == COIN_TURNED_INTO_BRICK)
		{
			turnedIntoBrickStart = GetTickCount64();
		}
	}
	void Render();
	virtual int IsCollidable() { return 1; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	void SetState(int state);
};