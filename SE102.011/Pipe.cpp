#include "Pipe.h"
#include "Plant.h"
#include "PlayScene.h"

CPipe::CPipe(float x, float y, int model, int plantType) : CGameObject(x, y) {
	CPlayScene*  scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	this->x = x;
	this->y = y;
	this->model = model;
	this->plantType = plantType;

	/* Add Plant To Scence*/
	CPlant* plant = new CPlant(x, y - PLANT_BBOX_HEIGHT / 4 + 1, plantType);
	scene->AddObject(plant);
}

void CPipe::Render() {
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (model == PIPE_SHORT_MODEL) aniId = ID_ANI_PIPE_SHORT;
	if (model == PIPE_LONG_MODEL) aniId = ID_ANI_PIPE_LONG;

	animations->Get(aniId)->Render(x, y);
}



void CPipe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (model == PIPE_SHORT_MODEL) {
		left = x - PIPE_BBOX_WIDTH / 2;
		top = y - PIPE_BBOX_HEIGHT_SHORT / 2;
		right = left + PIPE_BBOX_WIDTH;
		bottom = top + PIPE_BBOX_HEIGHT_SHORT;
	}
	else {
		left = x - PIPE_BBOX_WIDTH / 2;
		top = y - PIPE_BBOX_HEIGHT_LONG / 2;
		right = left + PIPE_BBOX_WIDTH;
		bottom = top + PIPE_BBOX_HEIGHT_LONG;
	}
}