#include "GameObject.h"

#define ID_ANI_0	30010
#define ID_ANI_1	30011
#define ID_ANI_2	30012
#define ID_ANI_3	30013
#define ID_ANI_4	30014
#define ID_ANI_5	30015
#define ID_ANI_6	30016
#define ID_ANI_7	30017
#define ID_ANI_8	30018
#define ID_ANI_9	30019

class CFont : public CGameObject {
private:
	ULONGLONG start_delete;
	int model;
public:
	CFont(float x, float y, int model) : CGameObject(x, y) {
		this->model = model;
	}
	void Render();
	void Update(DWORD dt);
	virtual int IsCollidable() { return 0; }
};