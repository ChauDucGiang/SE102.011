#pragma once
#include "GameObject.h"
#include "PlayScene.h"

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
#define MUSHROOM_OUT_BRICK_SPEED_Y -0.016f

class CMushRoom : public CGameObject {
	protected:
		float ax, ay, startX, startY;
		int model;
		virtual void Render();
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
		virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

		int IsBlocking() { return 0; }
		virtual int IsCollidable() { return 1; }
		void OnNoCollision(DWORD dt);
		virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	public:
		CMushRoom(float x, float y, int model);

		virtual void SetState(int state);

		void SetModel(int model) { this->model = model; }
		int GetModel() { return model; }

		std::pair<int, int> PositionWithMario();

};