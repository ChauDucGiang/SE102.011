#include "GameObject.h"

#define BOX_ITEM_BBOX_HEIGHT 16
#define BOX_ITEM_BBOX_WIDTH 16


#define ID_ANI_ITEM_MUSHROOM 24781
#define ID_ANI_ITEM_FLOWER 24786
#define ID_ANI_ITEM_STAR 24791

class CBoxItem : public CGameObject
{

public:
	CBoxItem(float, float y);

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnNoCollision(DWORD dt);

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 1; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetState(int state);

};
