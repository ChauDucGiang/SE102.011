#include "KoopaDetector.h"


CKoopaDetector::CKoopaDetector(float x, float y, float vx, float vy) : CGameObject(x, y) {
	this->ay = KOOPA_DETECTOR_GRAVITY;
	this->vx = vx;
	this->vy = vy;
}

void CKoopaDetector::Render() {
	RenderBoundingBox();
}


void CKoopaDetector::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	vy += ay * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

}
void CKoopaDetector::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopaDetector::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
		isOnPlatform = true;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopaDetector::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - KOOPA_DETECTOR_BBOX_WIDTH / 2;
	t = y - KOOPA_DETECTOR_BBOX_HEIGHT / 2;
	r = l + KOOPA_DETECTOR_BBOX_WIDTH;
	b = t + KOOPA_DETECTOR_BBOX_HEIGHT;
}


void CKoopaDetector::SetState(int state) {

	CGameObject::SetState(state);
}