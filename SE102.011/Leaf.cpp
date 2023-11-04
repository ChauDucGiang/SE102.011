#include "Leaf.h"

CLeaf::CLeaf(float x, float y) : CGameObject(x, y) {
	this->ax = 0;
	this->ay = 0;

}

void CLeaf::Render() {
	CAnimations* animations = CAnimations::GetInstance();
	if (vx <= 0) animations->Get(ID_ANI_LEAF_LEFT)->Render(x, y);
	else if (vx > 0) animations->Get(ID_ANI_LEAF_RIGHT)->Render(50, y);
}


void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
}

void CLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

}