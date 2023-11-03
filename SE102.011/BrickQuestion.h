#pragma once
#include "GameObject.h"

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
		virtual void OnNoCollision(DWORD dt);
};