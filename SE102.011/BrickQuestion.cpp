#include "BrickQuestion.h"


CBrickQuestion::CBrickQuestion(float x, float y, int model) :CGameObject(x, y)
{
	this->model = model;
	this->ay = 0;
	this->minY = y - BRICK_QUESTION_BBOX_HEIGHT + ADJUST_UP_DOWN;
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

	if (x != startX) {
		x = startX;
	}
	if (!isEmpty) {
		if (y != startY) y = startY;
		if (x != startX) x = startX;
	}

	if (isOpened) {
		vy = 0;
		ay = 0;
		vx = 0;
		y = startY;
		x = startX;
	}
	else {
		vy += ay * dt;
		if (y <= minY)
		{
			vy = BRICK_QUESTION_SPEED_DOWN;
		}
		if (y > startY + BRICK_QUESTION_BBOX_HEIGHT - ADJUST_UP_DOWN)
		{
			y = startY;
			vy = 0;
			isEmpty = true;
			isOpened = true;
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBrickQuestion::Render(){

	int aniId;
	aniId = ID_ANI_QUESTION_BRICK;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CBrickQuestion::OnNoCollision(DWORD dt)
{
	y += vy * dt;
};