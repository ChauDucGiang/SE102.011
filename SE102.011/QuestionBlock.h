#pragma once
#include "GameObject.h"

#define BLOCK_QUESTION_BBOX_WIDTH 16
#define BLOCK_QUESTION_BBOX_HEIGHT 16

#define ID_ANI_BLOCK_QUESTION 11100
#define ID_ANI_BLOCK_QUESTION_EMPTY 11101
#define BLOCK_QUESTION_SPEED_UP 0.04f

#define BLOCK_QUESTION_MAX_HEIGHT 10
#define BLOCK_QUESTION_SPEED_DOWN 0.04f

#define BLOCK_QUESTION_COIN 1
#define BLOCK_QUESTION_ITEM 2
#define BLOCK_QUESTION_MUSHROOM_GREEN 3
#define QUESTION_SWITCH_BLOCK 4
#define BLOCK_QUESTION_MUSHROOM_RED 5
#define BLOCK_QUESTION_LEAF 6

#define BLOCK_QUESTION_STATE_UP 100

#define ADJUST_UP_DOWN 13

class CQuestionBlock : public CGameObject
{
	protected:
		int model;
		float ax, ay, startX, startY, minY;
		bool isEmpty = false, isOpened = false;
	
	public:
		CQuestionBlock(float x, float y, int model);

		virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
		virtual void Render();
		virtual void OnNoCollision(DWORD dt);

		virtual int IsCollidable() { return 1; }
		virtual int IsBlocking() { return 1; }

		bool GetIsOpened() { return isOpened; }
		void SetIsOpened(bool isOpened) { this->isOpened = isOpened; }

		bool GetIsEmpty() { return isEmpty; }
		void SetIsEmpty(bool isEmpty){ this->isEmpty = isEmpty; }

		void SetModel(int model) { this->model = model; }
		int GetModel() { return model; }
		float GetMinY() { return minY; }

		void Unbox();
};