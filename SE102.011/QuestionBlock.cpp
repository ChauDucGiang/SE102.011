#include "QuestionBlock.h"
#include "Coin.h"
#include "PlayScene.h"
#include "MushRoom.h"
#include "Leaf.h"


CQuestionBlock::CQuestionBlock(float x, float y, int model) :CGameObject(x, y)
{
	this->model = model;
	this->ay = 0;
	this->minY = y - BLOCK_QUESTION_BBOX_HEIGHT + ADJUST_UP_DOWN;
	this->startY = y;
	this->startX = x;
}

void CQuestionBlock::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BLOCK_QUESTION_BBOX_WIDTH / 2;
	top = y - BLOCK_QUESTION_BBOX_HEIGHT / 2;
	right = left + BLOCK_QUESTION_BBOX_WIDTH;
	bottom = top + BLOCK_QUESTION_BBOX_HEIGHT;
}

void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	if (x != startX) {
		x = startX;
	}
	if (!isEmpty) {
		if (y != startY) y = startY;
		if (x != startX) x = startX;
	}

	if (isOpened) {
		vy = 0;
		ay = 0;
		vx = 0;
		y = startY;
		x = startX;
	}
	else {
		vy += ay * dt;
		if (y <= minY)
		{
			vy = BLOCK_QUESTION_SPEED_DOWN;
		}
		if (y > startY + BLOCK_QUESTION_BBOX_HEIGHT - ADJUST_UP_DOWN)
		{
			y = startY;
			vy = 0;
			isEmpty = true;
			isOpened = true;
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CQuestionBlock::Render(){

	int aniId;
	aniId = ID_ANI_BLOCK_QUESTION;
	if (isEmpty) {
		aniId = ID_ANI_BLOCK_QUESTION_EMPTY;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CQuestionBlock::OnNoCollision(DWORD dt)
{
	y += vy * dt;
};

void CQuestionBlock::Unbox() {
	SetIsOpened(true);
	SetIsEmpty(true);

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (model == BLOCK_QUESTION_COIN) {
		mario->SetCoin();
		CCoin* coin = new CCoin(x, y);
		coin->SetState(COIN_SUMMON_STATE);
		scene->AddObject(coin);
	}
	else if (model == BLOCK_QUESTION_MUSHROOM_GREEN)
	{
		CMushRoom* mushroom = new CMushRoom(x, y, MUSHROOM_GREEN);
		scene->AddObject(mushroom);
	}
	else if (model == BLOCK_QUESTION_MUSHROOM_RED)
	{
		CMushRoom* mushroom = new CMushRoom(x, y, MUSHROOM_RED);
		scene->AddObject(mushroom);
	}
	else if (model == BLOCK_QUESTION_LEAF) {
		CLeaf* leaf = new CLeaf(x - 5, y - 5);
		scene->AddObject(leaf);
	}
}
