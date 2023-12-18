#include "PSwitch.h"

CPSwitch::CPSwitch(float x, float y) : CGameObject(x, y) {
	ay = -PSWITCH_GRAVITY;
	startY = y;
}

void CPSwitch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPSwitch::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId;

	if (!wasCollected) aniId = ID_ANI_PSWITCH_NORMAL;
	else aniId = ID_ANI_PSWITCH_WAS_COLLECTED;

	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}
void CPSwitch::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};
void CPSwitch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PSWITCH_BBOX_WIDTH / 2;
	t = y - PSWITCH_BBOX_HEIGHT / 2;
	r = l + PSWITCH_BBOX_WIDTH;
	b = t + PSWITCH_BBOX_HEIGHT;
}