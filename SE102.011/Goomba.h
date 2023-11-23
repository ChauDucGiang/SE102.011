#pragma once
#include "GameObject.h"
#include "PlayScene.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f
#define GOOMBA_JUMP_SPEED_Y 0.2f
#define TIME_ON_PLATFORM 2000
#define TIME_FLY 1000


#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_FLY 300

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001
#define ID_ANI_GOOMBA_UPSIDE 5002

#define ID_ANI_GOOMBA_RED 5003
#define ID_ANI_GOOMBA_RED_DIE 5004
#define ID_ANI_GOOMBA_RED_FLY_WALKING 5005
#define ID_ANI_GOOMBA_RED_FLY_JUMP 5006
#define ID_ANI_GOOMBA_RED_UPSIDE 5007

//type
#define GOOMBA_BROWN 1
#define GOOMBA_WING 2

class CGoomba : public CGameObject
{
protected:
	float ax, ay; 
	int model;

	ULONGLONG die_start, timeOnPlatform, timeFly;

	bool isOnPlatForm = false, isFlying = false;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	int GetModelBrownAnimation();
	int GetModelWingAnimation();

public: 	
	CGoomba(float x, float y, int model);
	virtual void SetState(int state);

	int GetModel() { return model; }
	void SetModel(int model) { this->model = model; }
};