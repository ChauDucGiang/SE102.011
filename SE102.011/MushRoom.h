#pragma once
#include "GameObject.h"

#define ID_ANI_MUSHROOM_RED 11001
#define ID_ANI_MUSHROOM_GREEN 11008


#define	MUSHROOM_WIDTH 10
#define MUSHROOM_BBOX_WIDTH 10
#define MUSHROOM_BBOX_HEIGHT 16
#define MUSHROOM_STATE_WALKING 100
#define MUSHROOM_STATE_OUTSIDE 200

#define MUSHROOM_GREEN 2
#define MUSHROOM_RED 1

#define MUSHROOM_GRAVITY 0.001f
#define MUSHROOM_SPEED 0.055f
#define OUT_BRICK -0.016f

class CMushRoom : public CGameObject {
	protected:
		float ax, ay, startX, startY;
		int model;
		virtual void Render();
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
		virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	public:
		CMushRoom(float x, float y, int model);

		void Render();
		virtual int IsCollidable() { return 1; }
		void OnNoCollision(DWORD dt);
		int IsBlocking() { return 0; }

		virtual void SetState(int state);

		void SetModel(int model) { this->model = model; }
		int GetModel() { return model; }
};