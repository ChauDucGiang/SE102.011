#include "Coin.h"

void CCoin::Render()
{
	//if (!checkObjectInCamera(this)) return;

	CAnimations* animations = CAnimations::GetInstance();
	CAnimation* animation = animations->Get(ID_ANI_COIN);
	animations->Get(ID_ANI_COIN)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - COIN_BBOX_WIDTH / 2;
	top = y - COIN_BBOX_HEIGHT / 2;
	right = left + COIN_BBOX_WIDTH;
	bottom = top + COIN_BBOX_HEIGHT;
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}