#pragma once
#include "GameObject.h"

#define HAMMER_GRAVITY 0.0005f

#define HAMMER_SPEED 0.007f
#define HAMMER_BBOX_WIDTH 16
#define HAMMER_BBOX_HEIGHT 16

#define ID_ANIMATION_HAMMMER_LEFT 56700
#define ID_ANIMATION_HAMMMER_RIGHT 56701

class CHammer : public CGameObject {
	protected :
		float ax, ay, startX, startY;
		int model;
		virtual void Render();
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
		virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	public :
		CHammer(float x, float y, int model);

		//void SetState(int state);

		void SetModel(int model) { this->model = model; }
		int GetModel() { return model; }
};