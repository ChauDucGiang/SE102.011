#pragma once
#include "GameObject.h"

//Property
#define PLANT_SPEED 0.025f
#define PLANT_BBOX_WIDTH 16
#define PLANT_BBOX_HEIGHT 32

//types
#define PLANT_SHOOT_RED 1
#define PLANT_SHOOT_GREEN 2
#define PLANT_NOT_SHOOT 3

//State
#define PLANT_STATE_UP 100
#define PLANT_STATE_DOWN 200
#define PLANT_STATE_DEATH 300

// Animations
#define ID_ANI_PLANT_NOT_SHOOT 311

class  CPlant : public CGameObject
{
	protected:
		float startX, startY;
		bool isShoot = false;
		int model;
		ULONGLONG defend_start, die_start, comeback_start;
		bool isDead, isJump, isAttack, isUpside, isOnPlatform, isWing;
		virtual void Render();
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
		virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	public :
		CPlant(float x, float y, int model);

		//get 
		bool GetIsDead() { return isDead; }
		int GetModel() { return model; }


		//set 
		virtual void SetState(int state);
		void SetModel(int model);
		void SetLevel(int levelo);
};