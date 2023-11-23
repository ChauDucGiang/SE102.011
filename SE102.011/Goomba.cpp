#include "Goomba.h"

CGoomba::CGoomba(float x, float y, int model):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	this->model = model;
	die_start = -1;
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{ 
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return; 

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	vy += ay * dt;
	vx += ax * dt;

	if ( (state==GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}

	if (model == GOOMBA_WING)
	{
		// Duoi theo mario
		if ((mario->GetX() <= x))
		{
			vx = -GOOMBA_WALKING_SPEED;
		}
		else {
			vx = GOOMBA_WALKING_SPEED;
		}
		if (GetTickCount64() - timeOnPlatform > TIME_ON_PLATFORM && isOnPlatForm) {
			SetState(GOOMBA_STATE_FLY);
		}
		else
		{
			if (GetTickCount64() - timeFly > TIME_FLY && !isOnPlatForm)
			{
				SetState(GOOMBA_STATE_WALKING);
			}
		}
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE) 
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}

	if (model == GOOMBA_WING) {
		aniId = GetModelWingAnimation();
	}
	else {
		aniId = GetModelBrownAnimation();
	}


	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	//RenderBoundingBox();
}

int CGoomba::GetModelBrownAnimation() {
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}
	return aniId;
}


int CGoomba::GetModelWingAnimation() {
	int aniId = ID_ANI_GOOMBA_RED_FLY_WALKING;
		if (!isOnPlatForm) {
			aniId = ID_ANI_GOOMBA_RED_FLY_JUMP;
		}
		else aniId = ID_ANI_GOOMBA_RED_FLY_WALKING;
	return aniId;
}


void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
			isOnPlatForm = true;
			isFlying = false;
			timeOnPlatform = GetTickCount64();
			timeFly = 0;
			break;
		case GOOMBA_STATE_FLY:
			vy = -GOOMBA_JUMP_SPEED_Y;
			isOnPlatForm = false;
			isFlying = true;
			timeOnPlatform = 0;
			timeFly = GetTickCount64();
			break;
	}
}
