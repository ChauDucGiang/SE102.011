#pragma once

#include "GameObject.h"

#define KOOPA_DETECTOR_GRAVITY 0.1f

#define KOOPA_DETECTOR_BBOX_WIDTH 6
#define KOOPA_DETECTOR_BBOX_HEIGHT 16

class CKoopaDetector : public CGameObject
{
protected:
	float ax, ay, range, centerX;
	bool isOnPlatform = false, isFalling = false;

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

	bool onPlatform() {return this->isOnPlatform; }
};