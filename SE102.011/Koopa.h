#pragma once
#include "GameObject.h"
#include "KoopaDetector.h"

#define KOOPA_GRAVITY 0.001f	//trong luc
#define KOOPA_WALKING_SPEED 0.015f	//toc do di bo
#define KOOPA_JUMP_DEATH 0.4f		//nhay
#define KOOPA_ADJUST_NOT_FALL 0.1f
#define KOOPA_KICKED_NOT_FAIL 0.04f
#define KOOPA_WAS_KICKED_SPEED_X 0.18f
#define KOOPA_JUMP_WAS_ATTACKED_SPEED_Y 0.4f
#define KOOPA_ADJUST_DETECTOR_X 3.0f
#define KOOPA_JUMP_SPEED_Y 0.2f

#define KOOPA_GRAVITY_WING 0.0005f
#define KOONPA_JUMP_SPEED 0.2f

#define KOOPA_DEFEND_TIME 8000
#define KOOPA_REVIVAL_TIME 6000
#define KOOPA_DIE_TIME 10000


#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 26
#define KOOPA_BBOX_HEIGHT_DEFEND 16

// GREEN
#define ID_ANI_GREEN_WALK_RIGHT 6001
#define ID_ANI_GREEN_WALK_LEFT 6002
#define ID_ANI_GREEN_DEFEND 6003
#define ID_ANI_GREEN_UPSIDE 6005
#define ID_ANI_GREEN_REVIVAL 6006
#define ID_ANI_GREEN_UPSIDE_KICKED 6007
#define ID_ANI_GREEN_UPSIDE_REVIVAL 6008
#define ID_ANI_GREEN_JUMP_RIGHT 6009
#define ID_ANI_GREEN_JUMP_LEFT 6010

//Red
#define ID_ANI_RED_WALK_RIGHT 6101
#define ID_ANI_RED_WALK_LEFT 6102
#define ID_ANI_RED_DEFEND 6103
#define ID_ANI_RED_UPSIDE 6105
#define ID_ANI_RED_REVIVAL 6106
#define ID_ANI_RED_UPSIDE_KICKED 6107
#define ID_ANI_RED_UPSIDE_REVIVAL 6108

// OBJECT
#define KOOPA_GREEN 1
#define KOOPA_RED 2
#define KOOPA_GREEN_WING 3 

//STATE
#define KOOPA_STATE_JUMP 100
#define KOOPA_STATE_WALKING 500
#define KOOPA_STATE_DEFEND 200
#define KOOPA_STATE_WAS_KICKED 300
#define KOOPA_STATE_UPSIDE 400


class CKoopa : public CGameObject 
{
	protected:
		float ax, ay;
		int model;

		CKoopaDetector* detector;

		ULONGLONG  dieStart, revivalStart, defendStart;

		bool isDead = false, isJump, isAttack, isUpside = false, isOnPlatform, isWing, isDefend = false, isRevival = false, wasHeld = false, needCheckDetector = false, wasKicked = false;

		virtual void Render();
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
		virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

		virtual int IsCollidable() { return 1; }
		virtual int IsBlocking() { return 0; }

		virtual void OnNoCollision(DWORD dt);
		virtual void OnCollisionWith(LPCOLLISIONEVENT e);
		virtual void OnCollisionWithPlatform(LPCOLLISIONEVENT e);
		virtual void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
		virtual void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
		virtual void OnCollisionWithPlant(LPCOLLISIONEVENT e);
		virtual void OnCollisionWithMario(LPCOLLISIONEVENT e);
		virtual void OnCollisionWithBrickColor(LPCOLLISIONEVENT e);

		int GetModelGreenAnimation();
		int GetModelRedAnimation();
		void DeleteDetector();

	public:
		CKoopa(float x, float y , int model);

		bool GetIsDead() { return isDead; }

		void SetModel(int model) { this->model = model; }
		int GetModel() { return this->model; }

		virtual void SetState(int state);
		void SetWasHeld(bool wasHeld) { this->wasHeld = wasHeld; };

		float CalculateDetectorX() {
			float detectorX;
			// go to right
			if (vx > 0)
			{
				detectorX = x +  (KOOPA_BBOX_WIDTH / 2 + KOOPA_DETECTOR_BBOX_WIDTH / 2) - KOOPA_ADJUST_DETECTOR_X;
			}
			else
			{
				detectorX = x - (KOOPA_BBOX_WIDTH / 2 + KOOPA_DETECTOR_BBOX_WIDTH / 2) + KOOPA_ADJUST_DETECTOR_X;
			}
			return detectorX;
		}
};