#pragma once
#include "GameObject.h"

#define BRICK_QUESTION_BBOX_WIDTH 16
#define BRICK_QUESTION_BBOX_HEIGHT 16

#define ID_ANI_QUESTION_BRICK 11100
#define ID_ANI_QUESTION_BRICK_EMPTY 11101
#define BRICK_QUESTION_SPEED_UP 0.04f

#define BRICK_QUESTION_MAX_HEIGHT 10
#define BRICK_QUESTION_SPEED_DOWN 0.04f

#define BRICK_QUESTION_ITEM 2
#define BRICK_QUESTION_MUSHROOM_GREEN 3
#define BRICK_QUESTION_BUTTON 4
#define BRICK_QUESTION_COIN 1

#define QUESTION_BRICK_STATE_UP 100

#define ADJUST_UP_DOWN 13

class CBrickQuestion : public CGameObject
{
	protected:
		int model;
		float ax, ay, startX, startY;
	public:
		CBrickQuestion(float x, float y, int model);

		virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
		virtual void Render();

		virtual int IsCollidable() { return 1; }
		virtual int IsBlocking() { return 1; }
};