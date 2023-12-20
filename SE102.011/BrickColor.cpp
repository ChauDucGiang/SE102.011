#include "BrickCorlor.h"
#include "Brick.h"
#include "PlayScene.h"
#include "Coin.h"
#include "SwitchBlock.h"

void CBrickColor::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK_COLOR)->Render(x, y);
	//RenderBoundingBox();
}

void CBrickColor::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + float(BRICK_BBOX_HEIGHT / 1.5);
}
void CBrickColor::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (!isUsedSwitchPBlock)
	{
		IsUsedSwitchPBlock();
	}
	else {
		if (!isCoin)
		{
			SetState(BRICK_STATE_TURNS_INTO_COIN);
			CCoin* coin = new CCoin(x, y);
			scene->AddObject(coin);
			Delete();
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CBrickColor::SetState(int state) {
	switch (state) {
	case BRICK_STATE_WAS_BROKEN:
		isBreak = true;
		break;
	case BRICK_STATE_TURNS_INTO_COIN:
		isCoin = true;
		break;
	}
	CGameObject::SetState(state);
}

void CBrickColor::Destroy() {
	SetState(BRICK_STATE_WAS_BROKEN);
	//CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	//CBrick* brick = new CBrick(x, y);
	//scene->AddObject(brick);
	Delete();
}

void CBrickColor::IsUsedSwitchPBlock() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CSwitchBlock* block = NULL;
	for (size_t i = 0; i < scene->GetObjects().size(); i++) {
		if (dynamic_cast<CSwitchBlock*>(scene->GetObjects()[i])) {
			block = dynamic_cast<CSwitchBlock*>(scene->GetObjects()[i]);
			if (block->WasCollected()) {
				isUsedSwitchPBlock = true;
			}
			block = NULL;
			break;
		}
	}
}

