#include "FireBullet.h"

CFireBullet::CFireBullet(float bx, float by)
{
}
void CFireBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CFireBullet::Render()
{
	if (!checkObjectInCamera(this)) return;

	CAnimations* animations = CAnimations::GetInstance();
	//RenderBoundingBox();
}
void CFireBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BULLET_BBOX_WIDTH_PLANT;
	b = y + BULLET_BBOX_HEIGHT_PLANT;
}

void CFireBullet::OnCollisionWith(LPCOLLISIONEVENT e) {
}