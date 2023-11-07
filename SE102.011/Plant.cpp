#include "Plant.h"


CPlant::CPlant(float x, float y, int model) :CGameObject(x, y) {
	this->startX = x;
	this->startY = y;
	this->model = model;
	startY = y;
	minY = startY - PLANT_BBOX_HEIGHT;
	SetState(PLANT_STATE_UP);
}

void CPlant::Render() {
	int aniId = 305;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (isUpping) {
		if (y > minY) {
			vy = -PLANT_SPEED_UP_DOWN;
		}
		else
		{
			vy = 0;
			y = minY;
			SetState(PLANT_STATE_DOWN);
		}
	}
	else if (isDowning) {
		if (model == PLANT_SHOOT_GREEN || model == PLANT_SHOOT_RED) {
			if ((y < startY + 2)) {
				vy = PLANT_SPEED_UP_DOWN;
			}
			else {
				vy = 0;
				y = startY + 2;
				SetState(PLANT_STATE_UP);
			}
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

}

void CPlant::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}


void CPlant::SetState(int state) {
	switch (state) {
	case PLANT_STATE_UP:
		isUpping = true;
		isDowning = false;
		isShooting = false;

		break;
	case PLANT_STATE_DOWN:
		isUpping = false;
		isDowning = true;
		isShooting = false;
		break;
	case PLANT_STATE_DEATH:
		isDeleted = true;
		break;
	}
	CGameObject::SetState(state);
}