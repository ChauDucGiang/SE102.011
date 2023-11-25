#include "Leaf.h"

CLeaf::CLeaf(float x, float y) : CGameObject(x, y) {
	this->ay = LEAF_GRAVITY;
	this->range = 20.0f;
	this->centerX = x;
	SetState(LEAF_STATE_FLY);
}

void CLeaf::Render() {
	CAnimations* animations = CAnimations::GetInstance();
	if (vx <= 0) animations->Get(ID_ANI_LEAF_LEFT)->Render(x, y);
	else if (vx > 0) animations->Get(ID_ANI_LEAF_RIGHT)->Render(x, y);
}


void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	if (y < LEAF_MIN_Y )
	{
		y  = LEAF_MIN_Y;
		SetState(LEAF_STATE_FALL);
	}
	else
	{
		if (abs(x - this->centerX) > this->range)
		{
			vx = -vx;
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

}
void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e) {

	if (!dynamic_cast<CGoomba*>(e->obj) && !dynamic_cast<CMario*>(e->obj)) {
		if (e->ny < 0)
		{
			vy = 0;
			ay = 0;
			isOnPlatform = true;
		}

	}
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}


void CLeaf::SetState(int state) {
	switch (state)
	{
	case LEAF_STATE_FALL:
		vy = LEAF_FALL_SPEED_Y;
		vx = -LEAF_FALL_SPEED_X;
		isFalling = true;
		break;
	case LEAF_STATE_FLY:
		vy = -LEAF_OUT_BRICK_SPEED_Y;
		isFalling = false;
		break;
	}

	CGameObject::SetState(state);
}