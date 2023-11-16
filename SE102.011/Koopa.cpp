#include "Koopa.h"
#include "PlayScene.h"
#include "Platform.h"

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
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vy += ay * dt;
	vx += ax * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render() {
	int aniId = -1;
	if (vx > 0) aniId = ID_ANI_GREEN_WALK_RIGHT;
	else aniId = ID_ANI_GREEN_WALK_LEFT;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - KOOPA_BBOX_WIDTH / 2;
	top = y - KOOPA_BBOX_HEIGHT / 2;
	right = left + KOOPA_BBOX_WIDTH;
	bottom = top + KOOPA_BBOX_HEIGHT;
}

void CKoopa::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CKoopa::OnCollisionWithPlatform(LPCOLLISIONEVENT e) {

	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	int pX = platform->GetX();
	int pL = platform->GetLength();
	int kX =  GetX();
	DebugOut(L"[INFOR] Platform X : %d\n", pX);
	DebugOut(L"[INFOR] Platform Length : %d\n", pL);
	DebugOut(L"[INFOR] Koopa X : %d\n", kX);
	if ((state == KOOPA_STATE_WALKING))
	{
		if (platform->GetX() > (GetX() + KOOPA_BBOX_WIDTH / 2) && vx < 0) {
			vx = -vx;
		
			SetX(platform->GetX() + KOOPA_BBOX_WIDTH / 2);
		}
		else if ((platform->GetX() + 22) < (GetX()) && vx > 0)
		{
			vx = -vx;

			SetX(platform->GetX() + 22 - KOOPA_BBOX_WIDTH / 2);
		}


	}
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CPlatform*>(e->obj))
		this->OnCollisionWithPlatform(e);
}

void CKoopa::SetState(int state) {
	CGameObject::SetState(state);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (state) {
	case KOOPA_STATE_WALKING:
		vx = -KOOPA_WALKING_SPEED;
		vy = 0;
		ay = KOOPA_GRAVITY;
		break;
	}
}

void SetLevel(int level) {

}