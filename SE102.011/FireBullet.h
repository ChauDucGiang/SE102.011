#pragma once
#include "GameObject.h"

#define BULLET_BBOX_WIDTH_PLANT	9
#define BULLET_BBOX_HEIGHT_PLANT	9

#define BULLET_SPEED_X	0.08f
#define BULLET_SPEED_Y	0.05f

#define BULLET_SPEED_MAX	0.05f

#define ADJUST_VECTOR_Y 30

#define CHANGE_DIRECTION 30
#define TIME_BULLET_DELETE 4000

#define ID_ANI_BULLET_RIGHT		71
#define ID_ANI_BULLET_LEFT		72	

class CFireBullet :public CGameObject
{
protected:
	ULONGLONG start_deleted;
	virtual int IsCollidable() { return 0; }

public:
	CFireBullet(float x, float y, int nx, int ny);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void OnNoCollision(DWORD dt) {
		x += vx * dt;
		y += vy * dt;
	}
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};