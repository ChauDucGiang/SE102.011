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
	int aniId = ID_ANI_GREEN_WALK_LEFT;
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
	if ((state == KOOPA_STATE_WALKING))
	{
		if (platform->GetX() - KOOPA_BBOX_WIDTH / 2 > GetX()) {
			vx = -vx;
		}
		if ((GetX() > (platform->GetX() + (platform->GetLength() - 0.5) * KOOPA_BBOX_WIDTH))) {
			vx = -vx;
		}

	}
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e) {

}

void CKoopa::SetState(int state) {
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