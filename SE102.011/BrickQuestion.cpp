#include "BrickQuestion.h"


CBrickQuestion::CBrickQuestion(float x, float y, int model) :CGameObject(x, y)
{
	this->model = model;
	this->ay = 0;
	this->startY = y;
	this->startX = x;
}

void CBrickQuestion::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BRICK_QUESTION_BBOX_WIDTH / 2;
	top = y - BRICK_QUESTION_BBOX_HEIGHT / 2;
	right = left + BRICK_QUESTION_BBOX_WIDTH;
	bottom = top + BRICK_QUESTION_BBOX_HEIGHT;
}

void CBrickQuestion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBrickQuestion::Render(){

	int aniId;
	aniId = ID_ANI_QUESTION_BRICK;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}