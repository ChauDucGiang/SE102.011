#include "BrickCorlor.h"

void CBrickColor::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK_COLOR)->Render(x, y);
	//RenderBoundingBox();
}

void CBrickColor::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + float(BRICK_BBOX_HEIGHT / 1.5);
}
void CBrickColor::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CBrickColor::SetState(int state) {
	switch (state) {
	case BRICK_STATE_WAS_BROKEN:

		break;
	case BRICK_STATE_TURNS_INTO_GOLD:

		break;
	}
	CGameObject::SetState(state);
}