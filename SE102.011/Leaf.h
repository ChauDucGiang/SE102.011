#pragma once
#include "GameObject.h"

#define ID_ANI_LEAF_LEFT 11002
#define ID_ANI_LEAF_RIGHT 11003

class CLeaf : public CGameObject
{
	public:
		CLeaf(float x, float y);
		void Render();
		void Update(DWORD dt, vector<LPGAMEOBJECT>*coObjects);
		void GetBoundingBox(float &left, float &top, float &right, float &bottom);
		int IsBlocking() { return 0; };
};