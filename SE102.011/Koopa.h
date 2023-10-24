#pragma once
#include "GameObject.h"

#define KOOPA_GRAVITY 0.0001f	//trong luc
#define KOOPA_WALKING_SPEED 0.04f	//toc do di bo
#define KOOPA_IS_KICK_SPEED 0.18f	//toc do da
#define KOOPA_JUMP_DEATH 0.4f		//nhay
#define KOOPA_ADJUST_NOT_FAIL 0.1f	// dieu chinh khong that bai
#define KOOPA_ADJUST_KICKED_NOT_FAIL 0.1f // dieu chinh da khong that bai
#define KOOPA_KICKED_NOT_FAIL 0.04f

#define KOOPA_GRAVITY_WING 0.0005f
#define KOONPA_JUMP_SPEED 0.2f


#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 26
#define KOOPA_BBOX_HEIGHT_DEFINED 16

// GREEN
#define ID_ANI_GREEN_WALK_RIGHT 6001
#define ID_ANI_GREEN_WALK_LEFT 6002

// OBJECT
#define KOOPA_GREEN 1
#define KOOPA_RED 2
#define KOOPA_GREEN_WING 3 

//STATE
#define KOOPA_STATE_JUMP 100
#define KOOPA_STATE_WALKING 500


class CKoopa : public CGameObject 
{
	protected:
		float ax, ay;
		int model;

		ULONGLONG defend_start, die_start, comeback_start;

		bool walkingChek;
		bool isDead, isJump, isAttack, isUpside, isOnPlatform, isWing;

		virtual void Render();
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
		virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

		virtual int IsCollidable() { return 1; }
		virtual int IsBlocking() { return 0; }
		virtual int IsEnemy() { return 1; }

		virtual void OnNoCollision(DWORD dt);
		virtual void OnCollisionWithPlatform(LPCOLLISIONEVENT e);
		virtual void OnCollisionWith(LPCOLLISIONEVENT e);

		//Animations
	public:
		CKoopa(float x, float y , int model);

		// get
		bool GetIsDead() { return isDead; }
		int GetModel() { return model; }

		//set
		virtual void SetState(int state);
		void SetModel(int model) { this->model = model; }
		void SetLevel(int level);
};