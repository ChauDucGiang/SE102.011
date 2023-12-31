﻿#include "FireBullet.h"
#include "Pipe.h"
#include "Plant.h"
#include "PlayScene.h"

CFireBullet::CFireBullet(float x, float y, int nx, int ny):CGameObject(x, y)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	//float deltaX = abs(x - mario->GetX());
	//float deltaY = abs(x - mario->GetY());
	//time = deltaX / vx = deltaY / vy;
	vx = nx  * BULLET_SPEED_X;
	vy = -ny * BULLET_SPEED_Y;

}
void CFireBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CFireBullet::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (vx > 0)
		aniId = ID_ANI_BULLET_RIGHT;
	else
		aniId = ID_ANI_BULLET_LEFT;
	animations->Get(aniId)->Render(x, y);
}
void CFireBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BULLET_BBOX_WIDTH_PLANT;
	b = y + BULLET_BBOX_HEIGHT_PLANT;
}

//xoá nêu chạm đất hoặc pipe
void CFireBullet::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CPipe*>(e->obj)) return;
	if (e->obj->IsBlocking()) isDeleted = true;
}