#include "Plant.h"


CPlant::CPlant(float x, float y, int model) :CGameObject(x, y) {
	this->startX = x;
	this->startY = y;
	this->model = model;
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
	CGameObject::SetState(state);
}