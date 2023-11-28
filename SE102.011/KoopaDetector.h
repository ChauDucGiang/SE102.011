#pragma once

#include "GameObject.h"

#define KOOPA_DETECTOR_GRAVITY 0.0002f

#define KOOPA_DETECTOR_BBOX_WIDTH 6
#define KOOPA_DETECTOR_BBOX_HEIGHT 16

class CKoopaDetector : public CGameObject
{
public:
	float ax, ay, range, centerX;
	bool isOnPlatform = false, isFalling = false;

protected:
	CKoopaDetector(float x, float y, float vx, float vy);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsBlocking() { return 0; };
	virtual void SetState(int state);
	void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	boolean isFalling() {return this->isFalling;}
};