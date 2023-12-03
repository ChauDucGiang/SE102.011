#pragma once

#include "GameObject.h"

#define KOOPA_DETECTOR_GRAVITY 0.001f

#define KOOPA_DETECTOR_BBOX_WIDTH 6
#define KOOPA_DETECTOR_BBOX_HEIGHT 26

#define KOOPA_DETECTOR_MAX_GRAVITY 0.1f

class CKoopaDetector : public CGameObject
{
protected:
	float ax, ay;
	bool isOnPlatform = false;

public:
	CKoopaDetector(float x, float y, float vx, float vy);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void SetState(int state);
	void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	boolean isFalling() {
		return abs(vy) > KOOPA_DETECTOR_MAX_GRAVITY;
	}
};