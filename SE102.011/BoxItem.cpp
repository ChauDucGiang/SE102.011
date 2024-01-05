#include "BoxItem.h"

CBoxItem::CBoxItem(float x, float y) : CGameObject(x, y) {
	model = BOX_ITEM_MUSHROOM;
	isCollected = false;

}

void CBoxItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	if (!isCollected) {
		if (GetTickCount64() - switchModelStart > BOX_ITEM_SWITCH_MODEL_TIME) {
			SwitchModel();
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CBoxItem::Render()
{
	if (!checkObjectInCamera(this)) return;

	int aniId = ID_ANI_ITEM_MUSHROOM;
	CAnimations* animations = CAnimations::GetInstance();

	if (model == BOX_ITEM_MUSHROOM) aniId = ID_ANI_ITEM_MUSHROOM;
	else if (model == BOX_ITEM_FLOWER) aniId = ID_ANI_ITEM_FLOWER;
	else if (model == BOX_ITEM_STAR) aniId = ID_ANI_ITEM_STAR;

	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CBoxItem::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CBoxItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BOX_ITEM_BBOX_WIDTH / 2;
	t = y - BOX_ITEM_BBOX_HEIGHT / 2;
	r = l + BOX_ITEM_BBOX_WIDTH;
	b = t + BOX_ITEM_BBOX_HEIGHT;
}

void CBoxItem::SetState(int state) {
	switch (state) {
	case BOX_ITEM_STATE_COLLECTED:
		isCollected = true;
		vy = -BOX_ITEM_SPEED_Y;
		break;
	}
	CGameObject::SetState(state);
}

void CBoxItem::SwitchModel() {

	if (model >= 3)
	{
		model = 1;
	}
	else
	{
		model++;
	}

	switchModelStart = GetTickCount64();
}