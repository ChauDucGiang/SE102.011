#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "QuestionBlock.h"
#include "Koopa.h"
#include "Leaf.h"
#include "Plant.h"
#include "FireBullet.h"
#include "MushRoom.h"
#include "BrickCorlor.h"
#include "SwitchBlock.h"
#include "Pipe.h"
#include "BoxItem.h"

#include "Collision.h"

#include "PlayScene.h"
#include "Platform.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// count down time
	if (state != MARIO_STATE_DIE) {
		if (limitTimeMap1 > 0) {
			if (GetTickCount64() - gameStart > 1000) {
				limitTimeMap1--;
				gameStart = GetTickCount64();
			}
		}
		else {
			limitTimeMap1 = 0;
			SetState(MARIO_STATE_DIE);
		}
	};

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchableStart > MARIO_UNTOUCHABLE_TIME)
	{
		untouchableStart = 0;
		untouchable = 0;
	}

	//TailAttack
	if (isTailAttack) {
		if (GetTickCount64() - tailAttachStart > TIME_TAIL_ATTACK) {
			isTailAttack = false;
			tailAttachStart = 0;
		}
	}

	//Holding
	if (isHolding) {
		if (GetTickCount64() - holdingStart > MARIO_HOLDING_TIME) {
			isHolding = false;
			holdingStart = 0;
		}
	};

	//Prepare Fly
	if (isRunning)
	{
		if (level == MARIO_LEVEL_TAIL)
		{
			if (GetTickCount64() - prepareFlyStart > MARIO_PREPARE_FLY_TIME)
			{
				if (GetTickCount64() - levelRunningUpStart > MARIO_LEVEL_RUN_UP_TIME)
				{
					if (levelRunning < MARIO_LEVEL_RUN_MAX)
					{
						levelRunning++;
					}
					levelRunningUpStart = GetTickCount64();
				}
			}
		}
	}
	else
	{
		if (!isFlying)
		{
			if (GetTickCount64() - levelRunningDownStart > MARIO_LEVEL_RUN_DOWN_TIME)
			{
				if (levelRunning > 0)
				{
					levelRunning--;
				}
				levelRunningDownStart = GetTickCount64();
			}
			prepareFlyStart = GetTickCount64();
		}
	}

	//Flying
	if (isFlying)
	{
		if (isOnPlatform) {
			isFlying = false;
			ay = MARIO_GRAVITY;

		}
		if (GetTickCount64() - flyStart > MARIO_FLY_TIME)
		{
			EndFly();
		}
		if (GetTickCount64() - flyUpStart > MARIO_FLY_UP_TIME)
		{
			FlyDown();
		}
	}

	// UsingPipe
	if (isUsingPipe) {
		if (vy > 0) {
			if (!isOutPipe) {
				if (abs(y - startUsePiPeY) > MARIO_BIG_BBOX_HEIGHT / 2) {
					GoToHiddenMap();
					isOutPipe = true;
				}
			}
			else if (isOutPipe) {
				isUsingPipe = false;
			}
		}
		else {
			if (!isOutPipe) {
				if (abs(y - startUsePiPeY) > MARIO_BIG_BBOX_HEIGHT / 2) {
					ReturnToWorldMap();
					isOutPipe = true;
				}
			}
			else if (isOutPipe) {
				isUsingPipe = false;
			}
		}
	}
	else if(!isFlying)	 {
		isOutPipe = false;
		ay = MARIO_GRAVITY;
	}

	if (y <=0)
	{
		y = MARIO_BIG_BBOX_HEIGHT / 2;
	}
	isOnPlatform = false;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

#pragma region CollisionWithGameObject
void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) {
			isOnPlatform = true;
			//isFlying = false;
		}
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = 0;
		}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CPlant*>(e->obj))
		OnCollisionWithPlant(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CFireBullet*>(e->obj))
		OnCollisionWithFireBullet(e);
	else if (dynamic_cast<CMushRoom*>(e->obj))
		OnCollisionWithMushRoom(e);
	else if (dynamic_cast<CPlatform*>(e->obj))
		OnCollisionWithPlatfom(e);
	else if (dynamic_cast<CBrickColor*>(e->obj))
	{
		OnCollisionWithBrickColor(e);
	}
	else if (dynamic_cast<CSwitchBlock*>(e->obj))
	{
		OnCollisionWithSwitchBlock(e);
	}
	else if (dynamic_cast<CPipe*>(e->obj))
	{
		OnCollisionWithPipe(e);
	}
	else if (dynamic_cast<CBoxItem*>(e->obj))
	{
		OnCollisionWithBoxItem(e);
	}
}

void CMario::OnCollisionWithPlatfom(LPCOLLISIONEVENT e)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	if (platform->IsBlocking()) {
		//isOnPlatform = true;

	}
	if (platform->IsCanDown())
	{
		DebugOut(L"[INFO] Mario MARIO_STATE_GOING_UP_PIPE 1\n");
		//isUsingPipe = true;
		canDown = true;
		if (e->ny < 0) {
			DebugOut(L"[INFO] Mario MARIO_STATE_GOING_DOWN_PIPE\n");
		}
		if (e->ny > 0)
		{
			DebugOut(L"[INFO] Mario MARIO_STATE_GOING_UP_PIPE 2\n");
			SetState(MARIO_STATE_GOING_UP_PIPE);
		}
	}
	else
	{
		//isUsingPipe = false;
		canDown = false;
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	DebugOut(L"[INFO] Mario OnCollisionWithGoomba\n");
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (isTailAttack) {
		SetScore(100);
		goomba->SetState(GOOMBA_STATE_DIE);
	}
	else
	{
		// jump on top >> kill Goomba and deflect a bit 
		if (e->ny < 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				goomba->SetState(GOOMBA_STATE_DIE);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
		else // hit by Goomba
		{
			//if (untouchable == 0)
			//{
			//	if (goomba->GetState() != GOOMBA_STATE_DIE)
			//	{
			//		if (level > MARIO_LEVEL_SMALL)
			//		{
			//			level = MARIO_LEVEL_SMALL;
			//			StartUntouchable();
			//		}
			//		else
			//		{
			//			DebugOut(L">>> Mario DIE >>> \n");
			//			SetState(MARIO_STATE_DIE);
			//		}
			//	}
			//}
		}
	}
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e) {
	DebugOut(L"[INFO] Mario OnCollisionWithKoopa nY: %d\n", e->ny);

	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (isTailAttack) {
		SetScore(100);
		koopa->SetState(KOOPA_STATE_UPSIDE);
	}
	else
	{

		if (koopa->GetState() == KOOPA_STATE_DEFEND || koopa->GetState() == KOOPA_STATE_UPSIDE)
		{
			LPGAME game = CGame::GetInstance();
			if (game->IsKeyDown(DIK_A))
			{
				if (koopa->GetState() == KOOPA_STATE_DEFEND || koopa->GetState() == KOOPA_STATE_UPSIDE)
				{
					isHolding = true;
					koopa->SetWasHeld(true);
					holdingStart = GetTickCount64();
					DebugOut(L"[INFO] Mario OnCollisionWithKoopa SetWasHeld\n");
				}
			}
			else
			{
				isHolding = false;
				koopa->SetWasHeld(false);
				koopa->SetState(KOOPA_STATE_WAS_KICKED);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
		else if (e->ny < 0) {
			//koopa->SetVy(-0.1f);
			if (koopa->GetState() == KOOPA_STATE_WALKING || koopa->GetState() == KOOPA_STATE_WAS_KICKED)
			{
				koopa->SetState(KOOPA_STATE_DEFEND);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
		else
		{
			if (untouchable == 0)
			{
				/*if (level > MARIO_LEVEL_SMALL)
					{
						level = MARIO_LEVEL_SMALL;
						StartUntouchable();
					}
					else
					{
						DebugOut(L">>> Mario DIE >>> \n");
						SetState(MARIO_STATE_DIE);
					}*/
			}
		}
	}
}

void CMario::OnCollisionWithPlant(LPCOLLISIONEVENT e) {
	DebugOut(L"[INFO] Mario OnCollisionWithPlant\n");
	CPlant* plant = dynamic_cast<CPlant*>(e->obj);

	if (isTailAttack) {
		SetScore(100);
		plant->Delete();
	}
	else
	{
		if (untouchable == 0) {
			if (level > MARIO_LEVEL_SMALL)
			{
				level = MARIO_LEVEL_SMALL;
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				//SetState(MARIO_STATE_DIE);
			}
		}
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e) {
	DebugOut(L"[INFO] Mario OnCollisionWithLeaf\n");
	CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);
	leaf->Delete();

	if (level  ==  MARIO_LEVEL_SMALL)
	{
		SetLevel(MARIO_LEVEL_BIG);
	}
	else {
		SetLevel(MARIO_LEVEL_TAIL);
	}

}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	DebugOut(L"[INFO] Mario OnCollisionWithCoin\n");
	e->obj->Delete();
	SetCoin();
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	//DebugOut(L"[INFO] Mario OnCollisionWithPortal\n");
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e) {
	DebugOut(L"[INFO] Mario OnCollisionWithQuestionBlock\n");
	CQuestionBlock* q = dynamic_cast<CQuestionBlock*>(e->obj);

	if (e->ny > 0)
	{
		if (!q->GetIsOpened() && !q->GetIsEmpty())
		{
			q->Unbox();
		}
	}

}

void CMario::OnCollisionWithFireBullet(LPCOLLISIONEVENT e) {
	DebugOut(L"[INFO] Mario OnCollisionWithFireBullet\n");
	CFireBullet* bullet = dynamic_cast<CFireBullet*>(e->obj);

	if (untouchable == 0){
		if (level > MARIO_LEVEL_SMALL)
		{
			if (level == MARIO_LEVEL_BIG)
			{
				level = MARIO_LEVEL_SMALL;
				StartUntouchable();
			}else if (level == MARIO_LEVEL_TAIL)
			{
				level = MARIO_LEVEL_BIG;
				StartUntouchable();
			}
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			//SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithMushRoom(LPCOLLISIONEVENT e)
{
	CMushRoom* mushroom = dynamic_cast<CMushRoom*>(e->obj);

	if (!mushroom->IsDeleted()) {
		if (level == MARIO_LEVEL_SMALL)
		{
			SetScore(100);
			SetLevel(MARIO_LEVEL_BIG);
		}
		mushroom->Delete();
	}

}

void CMario::OnCollisionWithBrickColor(LPCOLLISIONEVENT e)
{
	//DebugOut(L"[INFO] Mario OnCollisionWithBrickColor\n");

	CBrickColor* brick = dynamic_cast<CBrickColor*>(e->obj);
	if ((isTailAttack && e->nx != 0) || e->ny > 0) {
		DebugOut(L"[INFO] Mario OnCollisionWithBrickColor BRICK_STATE_WAS_BROKEN\n");
		//brick->SetState(BRICK_STATE_WAS_BROKEN);
		brick->Destroy();
	}
}

void CMario::OnCollisionWithSwitchBlock(LPCOLLISIONEVENT e) {

	if (isTailAttack || e->ny < 0 || e->nx != 0) {
		DebugOut(L"[INFO] Mario OnCollisionWithSwitchBlock\n");
		CSwitchBlock* block = dynamic_cast<CSwitchBlock*>(e->obj);
		block->SetWasCollected(true);
	}

}
void CMario::OnCollisionWithPipe(LPCOLLISIONEVENT e) {
	DebugOut(L"[INFO] Mario OnCollisionWithPipe\n");
	CPipe* pipe = dynamic_cast<CPipe*>(e->obj);
}
void CMario::OnCollisionWithBoxItem(LPCOLLISIONEVENT e) {
	DebugOut(L"[INFO] Mario OnCollisionWithBoxItem\n");
	CBoxItem* box = dynamic_cast<CBoxItem*>(e->obj);

	if (!box->IsCollected()) {
		box->SetState(BOX_ITEM_STATE_COLLECTED);

		int modelCollected = box->GetModel();
		SetCardId(modelCollected);
		SetState(MARIO_STATE_END_SCENE);

	}
}
#pragma  endregion

#pragma region Animations
//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_BIG_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_BIG_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_BIG_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_BIG_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_BIG_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_BIG_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_BIG_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_BIG_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_BIG_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_BIG_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BIG_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_BIG_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_BIG_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BIG_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_BIG_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_BIG_RUNNING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_BIG_IDLE_RIGHT;

	return aniId;
}

//
// Get animdation ID for tail Mario
//
int CMario::GetAniIdTail() {
	int aniId = -1;

	if (isFlying)
	{
		if (!isOnPlatform) {
			if (levelRunning >= MARIO_LEVEL_RUN_MAX) {
				if (nx > 0) {
					aniId = ID_ANI_MARIO_TAIL_FLY_UP_RIGHT;
				}
				else aniId = ID_ANI_MARIO_TAIL_FLY_UP_LEFT;
			}
			else {
				if (nx > 0) aniId = ID_ANI_MARIO_TAIL_FLY_DOWN_RIGHT;
				else aniId = ID_ANI_MARIO_TAIL_FLY_DOWN_LEFT;
			}
		}
		else {
			if (nx > 0) aniId = ID_ANI_MARIO_TAIL_IDLE_RIGHT;
			else aniId = ID_ANI_MARIO_TAIL_IDLE_LEFT;
		}
	}
	else {
		if (isTailAttack)
		{
			aniId = ID_ANI_MARIO_TAIL_ATTACK;
		}
		else
		{
			if (!isOnPlatform)
			{
				if (abs(ax) == MARIO_ACCEL_RUN_X)
				{
					if (nx >= 0)
						aniId = ID_ANI_MARIO_TAIL_JUMP_RUN_RIGHT;
					else
						aniId = ID_ANI_MARIO_TAIL_JUMP_RUN_LEFT;
				}
				else
				{
					if (nx >= 0)
						aniId = ID_ANI_MARIO_TAIL_JUMP_WALK_RIGHT;
					else
						aniId = ID_ANI_MARIO_TAIL_JUMP_WALK_LEFT;
				}
			}
			else
				if (isSitting)
				{
					if (nx > 0)
						aniId = ID_ANI_MARIO_TAIL_SIT_RIGHT;
					else
						aniId = ID_ANI_MARIO_TAIL_SIT_LEFT;
				}
				else
					if (vx == 0)
					{
						if (nx > 0) aniId = ID_ANI_MARIO_TAIL_IDLE_RIGHT;
						else aniId = ID_ANI_MARIO_TAIL_IDLE_LEFT;
					}
					else if (vx > 0)
					{
						if (ax < 0)
							aniId = ID_ANI_MARIO_TAIL_BRACE_RIGHT;
						else if (ax == MARIO_ACCEL_RUN_X)
							aniId = ID_ANI_MARIO_TAIL_RUNNING_RIGHT;
						else if (ax == MARIO_ACCEL_WALK_X)
							aniId = ID_ANI_MARIO_TAIL_WALKING_RIGHT;
					}
					else // vx < 0
					{
						if (ax > 0)
							aniId = ID_ANI_MARIO_TAIL_BRACE_LEFT;
						else if (ax == -MARIO_ACCEL_RUN_X)
							aniId = ID_ANI_MARIO_TAIL_RUNNING_LEFT;
						else if (ax == -MARIO_ACCEL_WALK_X)
							aniId = ID_ANI_MARIO_TAIL_RUNNING_LEFT;
					}

			if (aniId == -1) aniId = ID_ANI_MARIO_TAIL_IDLE_RIGHT;
		}
	}

	return aniId;
}
#pragma endregion


void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	DebugOutTitle(L">>> Mario Level Run %d>>> \n", levelRunning);
	//DebugOutTitle(L">>> Mario X %f>>> \n", x);
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_TAIL)
		aniId = GetAniIdTail();

	animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		isRunning = true;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		isRunning = true;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		isRunning = false;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		isRunning = false;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		isRunning = false;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	case MARIO_STATE_TAIL_ATTACK:
		isTailAttack = true;
		tailAttachStart = GetTickCount64();
		break;
	case MARIO_STATE_FLY:
		isFlying = true;
		flyStart = GetTickCount64();
		FlyUp(-MARIO_FLY_START_SPEED_Y);
		break;
	case MARIO_STATE_GOING_DOWN_PIPE:
		isUsingPipe = true;
		vx = 0;
		ay = 0;
		startUsePiPeY = y;
		y += 24;
		vy = MARIO_USE_PIPE_SPEED_Y;
		break;
	case MARIO_STATE_GOING_UP_PIPE:
		isUsingPipe = true;
		vx = 0;
		ay = 0;
		startUsePiPeY = y;
		vy = -MARIO_USE_PIPE_SPEED_Y;
		break;
	case MARIO_STATE_END_SCENE:
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		isRunning = false;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level !=MARIO_LEVEL_SMALL)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

void CMario::FlyUp(float vy)
{
	ay = 0;
	this->vy = vy;
	flyUpStart = GetTickCount64();
}

void CMario::FlyDown()
{
	ay = MARIO_GRAVITY / 5;
}

void CMario::EndFly()
{
	isFlying = false;
	ay = MARIO_GRAVITY;
}