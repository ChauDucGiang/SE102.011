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

	switch (model)
	{
	case KOOPA_RED :
		aniId = GetModelRedAnimation();
		break;
	case KOOPA_GREEN:
		aniId = GetModelGreenAnimation();
		break;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

int CKoopa::GetModelGreenAnimation() {
	int aniId ;
	if (vx > 0) aniId = ID_ANI_RED_WALK_RIGHT;
	else aniId = ID_ANI_RED_WALK_LEFT;
	return aniId;
}

int CKoopa::GetModelRedAnimation() {
	int aniId;
	if (vx > 0) aniId = ID_ANI_GREEN_WALK_RIGHT;
	else aniId = ID_ANI_GREEN_WALK_LEFT;
	return aniId;
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
		// go to left
		if (platform->GetX() > GetX() && vx < 0) {
			vx = -vx;
		
			SetX(platform->GetX());
		}
		else if ((platform->GetX() + platform->GetLength() * platform->GetCellWidth()) < (GetX() + KOOPA_BBOX_WIDTH) && vx > 0)
		{
			vx = -vx;

			SetX(platform->GetX() + platform->GetLength() * platform->GetCellWidth() - KOOPA_BBOX_WIDTH);
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