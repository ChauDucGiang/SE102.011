#include "SwitchBlock.h"

CSwitchBlock::CSwitchBlock(float x, float y) : CGameObject(x, y) {
	ay = -SWITCH_BLOCK_GRAVITY;
	startY = y;
}

void CSwitchBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CSwitchBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId;

	if (!wasCollected) aniId = ID_ANI_SWITCH_BLOCK_NORMAL;
	else aniId = ID_ANI_SWITCH_BLOCK_WAS_COLLECTED;

	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}
void CSwitchBlock::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};
void CSwitchBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SWITCH_BLOCK_BBOX_WIDTH / 2;
	t = y - SWITCH_BLOCK_BBOX_HEIGHT / 2;
	r = l + SWITCH_BLOCK_BBOX_WIDTH;
	b = t + SWITCH_BLOCK_BBOX_HEIGHT;
}