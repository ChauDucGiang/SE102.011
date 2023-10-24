#include "Koopa.h"

CKoopa::CKoopa(float x, float y, int model) :CGameObject(x, y) {
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	this->model = model;
	if (model == KOOPA_GREEN_WING) {
		isWing = true;
		SetState(KOOPA_STATE_JUMP);
	}
	else {
		isWing = false;
		SetState(KOOPA_STATE_WALKING);
	}

	isOnPlatform = false;
	isUpside = false;
	isDead = false;
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render() {
	int aniId = ID_ANI_GREEN_WALK_LEFT;
	DebugOut(L"[INFO] Koopa rendered!\n");
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - KOOPA_BBOX_WIDTH / 2;
	top = y - KOOPA_BBOX_HEIGHT / 2;
	right = left + KOOPA_BBOX_WIDTH;
	bottom = top + KOOPA_BBOX_HEIGHT;
}

void CKoopa::OnNoCollision(DWORD dt) {

}

void CKoopa::OnCollisionWithPlatform(LPCOLLISIONEVENT e) {

}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (!e->obj->IsBlocking()) return;

	if (dynamic_cast<CKoopa*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopa::SetState(int state) {

}

void SetLevel(int level) {

}