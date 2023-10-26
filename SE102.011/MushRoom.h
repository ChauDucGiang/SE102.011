#pragma once
#include "GameObject.h"

class CMushRoom : public CGameObject {
	protected:
		float ax, ay, startX;
		int model;
		virtual void Render();
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
		virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};