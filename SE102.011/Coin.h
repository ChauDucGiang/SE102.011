#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

#define ID_ANI_COIN 11000
#define ID_ANI_COIN_IDLE 11601
#define COIN_GRAVITY 0.0003f
#define OUT_BRICK 0.2f
#define COIN_MAX_SPEED_FALL 0.1f
#define COIN_SUMMON_STATE	100
#define COIN_NOT_SUMMON_STATE	200

class CCoin : public CGameObject {
public:
	CCoin(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};