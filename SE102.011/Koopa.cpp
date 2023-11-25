#include "Koopa.h"
#include "PlayScene.h"
#include "Platform.h"
#include "Plant.h"

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
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	vy += ay * dt;
	vx += ax * dt;

	if (isDead) {
		if (GetTickCount64() - dieStart > KOOPA_DIE_TIME)
		{
			isDeleted = true;
			return;
		}
	}

	if (mario->IsHolding() && wasHeld) {
		this->x = mario->GetX() + mario->GetNx() * (MARIO_BIG_BBOX_WIDTH - 3);
		this->y = mario->GetY() - 3;

		vx = mario->GetVx();
		vy = mario->GetVy();
	}

	if ( state  != KOOPA_STATE_WAS_KICKED)
	{
		if (GetTickCount64() - defendStart > KOOPA_REVIVAL_TIME && (isDefend || isUpside)) {
			isRevival = true;
		}

		if ((GetTickCount64() - defendStart > KOOPA_DEFEND_TIME && (isDefend || isUpside))) {
			if (isRevival) {
				SetState(KOOPA_STATE_WALKING);
				y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DEFEND) / 2;
				//vy = -KOOPA_ADJUST_NOT_FALL;
				defendStart = 0;
			}
		}
	}

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
	RenderBoundingBox();
}

#pragma region Animations
int CKoopa::GetModelGreenAnimation() {
	int aniId;
	if (isUpside) {
		if (isRevival) aniId = ID_ANI_GREEN_UPSIDE_REVIVAL;
		else aniId = ID_ANI_GREEN_UPSIDE;
	}
	else
	{
		if (isDefend) {
			aniId = ID_ANI_GREEN_DEFEND;
			if (isRevival) aniId = ID_ANI_GREEN_REVIVAL;
		}
		else
		{
			if (vx > 0) aniId = ID_ANI_GREEN_WALK_RIGHT;
			else aniId = ID_ANI_GREEN_WALK_LEFT;
		}
	}

	return aniId;
}

int CKoopa::GetModelRedAnimation() {
	int aniId;
	if (isUpside) {
		if (isRevival) aniId = ID_ANI_RED_UPSIDE_REVIVAL;
		else aniId = ID_ANI_RED_UPSIDE;
	}
	else {
		if (isDefend) {
			aniId = ID_ANI_RED_DEFEND;
			if (isRevival) aniId = ID_ANI_RED_REVIVAL;
		}
		else
		{
			if (vx > 0) aniId = ID_ANI_RED_WALK_RIGHT;
			else aniId = ID_ANI_RED_WALK_LEFT;
		}
	}

	return aniId;
}
#pragma endregion


void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDefend || isUpside) {
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT_DEFEND / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT_DEFEND;
	}
	else {
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}

#pragma region Collision

void CKoopa::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e) {

	if (!dynamic_cast<CGoomba*>(e->obj) && !dynamic_cast<CMario*>(e->obj)) {
		if (e->ny < 0)
		{
			vy = 0;
			isOnPlatform = true;
		}
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = -vx;
		}
	}

	if (dynamic_cast<CPlatform*>(e->obj))
		this->OnCollisionWithPlatform(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		this->OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		this->OnCollisionWithKoopa(e);
	else if (dynamic_cast<CMario*>(e->obj))
		this->OnCollisionWithMario(e);
}

void CKoopa::OnCollisionWithMario(LPCOLLISIONEVENT e) {
	CMario* koopa = dynamic_cast<CMario*>(e->obj);
	 DebugOut(L"[INFO] Koopa OnCollisionWithMario\n");

}
void CKoopa::OnCollisionWithPlatform(LPCOLLISIONEVENT e) {

	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	isOnPlatform = true;
	vy = 0;
	if (e->ny < 0) {
		if (model == KOOPA_RED && state == KOOPA_STATE_WALKING)
		{
			// go to left
			if (platform->GetX() > GetX() && vx < 0) {
				vx = -vx;

				SetX(platform->GetX());
			}
			else if ((platform->GetX() + platform->GetWidth()) < (GetX() + KOOPA_BBOX_WIDTH) && vx > 0)
			{
				vx = -vx;

				SetX(platform->GetX() + platform->GetWidth() - KOOPA_BBOX_WIDTH);
			}
		}

	}
}

void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e) {
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (state == KOOPA_STATE_WAS_KICKED) {
		goomba->SetState(GOOMBA_STATE_DIE);
	}
}

void CKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e) {
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

	if (state == KOOPA_STATE_WAS_KICKED) {
		koopa->SetState(GOOMBA_STATE_DIE);
	}
}
void CKoopa::OnCollisionWithPlant(LPCOLLISIONEVENT e) {
	CPlant* plant = dynamic_cast<CPlant*>(e->obj);

	if (state == KOOPA_STATE_WAS_KICKED) {
		plant->SetState(PLANT_STATE_DIE);
	}
}
#pragma endregion

void CKoopa::SetState(int state) {
	CGameObject::SetState(state);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (state) {
	case KOOPA_STATE_WALKING:
		vx = -KOOPA_WALKING_SPEED;
		vy = 0;
		ay = KOOPA_GRAVITY;
		isRevival = false;
		isDefend = false;
		break;
	case KOOPA_STATE_DEFEND:
		vx = 0;
		defendStart = GetTickCount64();
		isDefend = true;
		break;
	case KOOPA_STATE_WAS_KICKED:
		isOnPlatform = true;
		vx = -KOOPA_WAS_KICKED_SPEED_X;
		break;
	case KOOPA_STATE_UPSIDE:
		isUpside = true;
		isDefend = false;
		isRevival = false;
		//isDead = true;
		//dieStart = GetTickCount64();
		if (isOnPlatform) vx = 0;
		vy = -KOOPA_JUMP_WAS_ATTACKED_SPEED_Y;
		defendStart = GetTickCount64();
		break;
	}
}

void SetLevel(int level) {

}