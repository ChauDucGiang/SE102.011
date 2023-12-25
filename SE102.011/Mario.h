#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.345f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.00085f

#define MARIO_JUMP_DEFLECT_SPEED  0.2f

#define MARIO_FLY_UP_DOWN_SPEED_Y 0.0f
#define MARIO_FLY_UP_SPEED_Y 0.075f
#define MARIO_USE_PIPE_SPEED_Y -0.075f

#pragma region State

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_TAIL_ATTACK		800

#define MARIO_STATE_FLY				1000

#define MARIO_STATE_GOING_DOWN_PIPE 1100
#define MARIO_STATE_GOING_UP_PIPE 1200
#pragma endregion


//Time
#define TIME_TAIL_ATTACK 400


#pragma region ANIMATION_ID

#define ID_ANI_MARIO_DIE 999

// BIG MARIO
#define ID_ANI_MARIO_BIG_IDLE_RIGHT 401
#define ID_ANI_MARIO_BIG_IDLE_LEFT 400

#define ID_ANI_MARIO_BIG_WALKING_RIGHT 501
#define ID_ANI_MARIO_BIG_WALKING_LEFT 500

#define ID_ANI_MARIO_BIG_RUNNING_RIGHT 601
#define ID_ANI_MARIO_BIG_RUNNING_LEFT 600

#define ID_ANI_MARIO_BIG_RUNNING_PREPARE_RIGHT 603
#define ID_ANI_MARIO_BIG_RUNNING_PREPARE_LEFT 602

#define ID_ANI_MARIO_BIG_JUMP_WALK_RIGHT 701
#define ID_ANI_MARIO_BIG_JUMP_WALK_LEFT 700

#define ID_ANI_MARIO_BIG_JUMP_RUN_RIGHT 801
#define ID_ANI_MARIO_BIG_JUMP_RUN_LEFT 800

#define ID_ANI_MARIO_BIG_SIT_RIGHT 901
#define ID_ANI_MARIO_BIG_SIT_LEFT 900


#define ID_ANI_MARIO_BIG_BRACE_RIGHT 1001
#define ID_ANI_MARIO_BIG_BRACE_LEFT 1000

#define ID_ANI_MARIO_BIG_HOLD_RUNNING_RIGHT 1011
#define ID_ANI_MARIO_BIG_HOLD_RUNNING_LEFT 1010

#define ID_ANI_MARIO_BIG_HOLD_IDLE_RIGHT 1041
#define ID_ANI_MARIO_BIG_HOLD_IDLE_LEFT 1040

#define ID_ANI_MARIO_BIG_HOLD_JUMP_RIGHT 1051
#define ID_ANI_MARIO_BIG_HOLD_JUMP_LEFT 1050

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1102
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1100

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1201
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1200

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1301
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1300

#define ID_ANI_MARIO_SMALL_RUNNING_PREPARE_RIGHT 1303
#define ID_ANI_MARIO_SMALL_RUNNING_PREPARE_LEFT 1302

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1401
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1400

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1501
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1500

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1601
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1600

#define ID_ANI_MARIO_SMALL_HOLD_RUNNING_RIGHT 1611
#define ID_ANI_MARIO_SMALL_HOLD_RUNNING_LEFT 1610

#define ID_ANI_MARIO_SMALL_HOLD_RUNNING_RIGHT 1611
#define ID_ANI_MARIO_SMALL_HOLD_RUNNING_LEFT 1610

#define ID_ANI_MARIO_SMALL_HOLD_IDLE_RIGHT 1641
#define ID_ANI_MARIO_SMALL_HOLD_IDLE_LEFT 1640

#define ID_ANI_MARIO_SMALL_HOLD_JUMP_RIGHT 1651
#define ID_ANI_MARIO_SMALL_HOLD_JUMP_LEFT 1650

//	TAIL
#define ID_ANI_MARIO_TAIL_IDLE_RIGHT 2401
#define ID_ANI_MARIO_TAIL_IDLE_LEFT 2400

#define ID_ANI_MARIO_TAIL_WALKING_RIGHT 2501
#define ID_ANI_MARIO_TAIL_WALKING_LEFT 2500

#define ID_ANI_MARIO_TAIL_RUNNING_RIGHT 2601
#define ID_ANI_MARIO_TAIL_RUNNING_LEFT 2600

#define ID_ANI_MARIO_TAIL_RUNNING_PREPARE_RIGHT 2603
#define ID_ANI_MARIO_TAIL_RUNNING_PREPARE_LEFT 2602

#define ID_ANI_MARIO_TAIL_JUMP_WALK_RIGHT 2701
#define ID_ANI_MARIO_TAIL_JUMP_WALK_LEFT 2700

#define ID_ANI_MARIO_TAIL_JUMP_RUN_RIGHT 2801
#define ID_ANI_MARIO_TAIL_JUMP_RUN_LEFT 2800

#define ID_ANI_MARIO_TAIL_SIT_RIGHT 2901
#define ID_ANI_MARIO_TAIL_SIT_LEFT 2900

#define ID_ANI_MARIO_TAIL_BRACE_RIGHT 3001
#define ID_ANI_MARIO_TAIL_BRACE_LEFT 3000

#define ID_ANI_MARIO_TAIL_HOLD_RUNNING_RIGHT 3011
#define ID_ANI_MARIO_TAIL_HOLD_RUNNING_LEFT 3010

#define ID_ANI_MARIO_TAIL_KICK_RIGHT 3021
#define ID_ANI_MARIO_TAIL_KICK_LEFT 3020

#define ID_ANI_MARIO_TAIL_ATTACK 3100

#define ID_ANI_MARIO_TAIL_HOLD_IDLE_RIGHT 3041
#define ID_ANI_MARIO_TAIL_HOLD_IDLE_LEFT 3040

#define ID_ANI_MARIO_TAIL_HOLD_JUMP_RIGHT 3051
#define ID_ANI_MARIO_TAIL_HOLD_JUMP_LEFT 3050

// FLY
#define ID_ANI_MARIO_TAIL_FLY_UP_RIGHT 3300
#define ID_ANI_MARIO_TAIL_FLY_UP_LEFT 3200
#define ID_ANI_MARIO_TAIL_FLY_DOWN_RIGHT 3061
#define ID_ANI_MARIO_TAIL_FLY_DOWN_LEFT 3060

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_FIRE    3
#define MARIO_LEVEL_TAIL	4

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO__HOLDING_TIME 6000
#define MARIO_FLY_TIME 10000

//Map position
#define POSITION_X_HIDDEN_MAP 3340
#define POSITION_Y_HIDDEN_MAP 0
#define POSITION_X_RETURN_WORLD_MAP 2325
#define POSITION_Y_RETURN_WORLD_MAP 366

class CMario : public CGameObject
{
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	float adjustX = 0.0f;

	ULONGLONG untouchableStart, tailAttachStart, holdingStart, flyStart;
	BOOLEAN isSitting, isOnPlatform, isTailAttack = false, isHolding, isFlying = true, isUsingPipe = false, isUsingPipeDown = false, isUsingPipeUp = false;
	int coin, score, level, untouchable;
#pragma region CollisionWithGameObject
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithFireBullet(LPCOLLISIONEVENT e);
	void OnCollisionWithMushRoom(LPCOLLISIONEVENT e);
	void OnCollisionWithPlatfom(LPCOLLISIONEVENT e);
	void OnCollisionWithBrickColor(LPCOLLISIONEVENT e);
	void OnCollisionWithSwitchBlock(LPCOLLISIONEVENT e);
#pragma  endregion

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdTail();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchableStart = -1;
		isOnPlatform = false;
		coin = 0;
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	int GetLevel() { return this->level; };
	void StartUntouchable() { untouchable = 1; untouchableStart = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int GetCoin() { return coin; }
	void SetCoin(int coin = 1) { this->coin += coin; }

	int GetScore() { return coin; }
	void SetScore(int score = 1) { this->score += score; }

	void SetIsHold(bool isHolding) { this->isHolding = isHolding; };
	bool IsHolding() { return this->isHolding; };

	bool IsOnPlatform() { return this->isOnPlatform; };

	float GetMaxVx() { return MARIO_RUNNING_SPEED; };

	void FlyUp();

	void GoToHiddenMap() {
		SetPosition(POSITION_X_HIDDEN_MAP, POSITION_Y_HIDDEN_MAP);
	}
	void ReturnToWorldMap() {
		SetPosition(POSITION_X_RETURN_WORLD_MAP, POSITION_Y_RETURN_WORLD_MAP);
	}
};