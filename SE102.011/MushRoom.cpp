#include "MushRoom.h"

CMushRoom::CMushRoom(float x, float y, int model) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = MUSHROOM_GRAVITY;
	vy = 0;
	this->model = model;
	startY = y;
	SetState(MUSHROOM_STATE_OUTSIDE);
}

void CMushRoom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushRoom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (model == MUSHROOM_RED) animations->Get(ID_ANI_MUSHROOM_RED)->Render(x, y);
	else animations->Get(ID_ANI_MUSHROOM_GREEN)->Render(x, y);

	//RenderBoundingBox();
}

void CMushRoom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMushRoom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CMushRoom::SetState(int state)
{
	switch (state)
	{
	case MUSHROOM_STATE_WALKING:
		vx = MUSHROOM_SPEED;
		break;
	}
	CGameObject::SetState(state);
}
