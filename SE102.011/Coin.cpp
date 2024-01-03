#include "Coin.h"
#include "BrickCorlor.h"
#include "PlayScene.h"

void CCoin::Render()
{
	//if (!checkObjectInCamera(this)) return;

	CAnimations* animations = CAnimations::GetInstance();
	CAnimation* animation = animations->Get(ID_ANI_COIN);
	animations->Get(ID_ANI_COIN)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - COIN_BBOX_WIDTH / 2;
	top = y - COIN_BBOX_HEIGHT / 2;
	right = left + COIN_BBOX_WIDTH;
	bottom = top + COIN_BBOX_HEIGHT;
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (state == COIN_SUMMON_STATE) vy += ay * dt;

	if (vy > COIN_MAX_SPEED_FALL) {
		isDeleted = true;
		return;
	}

	if (!isDeleted && model == COIN_TURNED_INTO_BRICK  && GetTickCount64() - turnedIntoBrickStart > COIN_TURN_INTO_BRICK_TIME)
	{
		CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		CBrickColor* brick = new CBrickColor(x, y, 2);
		scene->AddObject(brick);
		Delete();
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCoin::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CCoin::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case COIN_SUMMON_STATE:
		vy = -COIN_OUT_BRICK_SPEED_Y;
		break;
	}
}