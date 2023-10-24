#include "Hammer.h"

CHammer::CHammer(float x, float y, int model): CGameObject(x, y) {
	this->ax = 0;
	this->ay = HAMMER_GRAVITY;
	this->model = model;
	startX = x;
	startY = y;
}

void CHammer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CHammer::Render() {
	CAnimations* animations = CAnimations::GetInstance();
	if (vx > 0)
	{
		animations->Get(ID_ANIMATION_HAMMMER_RIGHT)->Render(x, y);
	}
	else {
		animations->Get(ID_ANIMATION_HAMMMER_LEFT)->Render(x, y);
	}
}

void CHammer::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - HAMMER_BBOX_WIDTH / 2;
	top = y - HAMMER_BBOX_HEIGHT / 2;
	right = left + HAMMER_BBOX_WIDTH;
	bottom = top + HAMMER_BBOX_HEIGHT - 2;
}