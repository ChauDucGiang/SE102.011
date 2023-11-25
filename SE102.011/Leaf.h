#pragma once
#include "GameObject.h"
#include "PlayScene.h"

#define ADJUST_FALL_X 0.0001f
#define LEAF_GRAVITY 0.0002f

#define LEAF_BBOX_WIDTH 18
#define LEAF_BBOX_HEIGHT 16

#define ID_ANI_LEAF_LEFT 11002
#define ID_ANI_LEAF_RIGHT 11003

#define LEAF_STATE_FALL 100
#define LEAF_STATE_FLY 200

#define LEAF_OUT_BRICK_SPEED_Y 0.1f

#define LEAF_FALL_SPEED_X 0.025f
#define LEAF_FALL_SPEED_Y 0.01f

#define LEAF_MIN_Y 300

class CLeaf : public CGameObject
{
	protected:
		float ax, ay, range, centerX;
		bool isOnPlatform = false, isFalling = false;
	public:
		CLeaf(float x, float y);
		void Render();
		void Update(DWORD dt, vector<LPGAMEOBJECT>*coObjects);
		void GetBoundingBox(float &left, float &top, float &right, float &bottom);
		int IsBlocking() { return 0; };
		virtual void SetState(int state);
		void OnNoCollision(DWORD dt);
		virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};