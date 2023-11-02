#include "Plant.h"


CPlant::CPlant(float x, float y, int model) :CGameObject(x, y) {
	this->startX = x;
	this->startY = y;
	this->model = model;
}

void CPlant::Render() {
	int aniId = ID_ANI_PLANT_LEFT_UNDER_NOT_SHOOT;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

}

void CPlant::SetState(int state) {

}