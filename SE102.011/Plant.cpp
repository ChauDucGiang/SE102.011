#include "Plant.h"
#include "FireBullet.h"
#include "PlayScene.h"


CPlant::CPlant(float x, float y, int model) :CGameObject(x, y) {
	this->startX = x;
	this->startY = y;
	this->model = model;
	startY = y;
	minY = startY - PLANT_BBOX_HEIGHT;
	SetState(PLANT_STATE_UP);
}

void CPlant::Render() {
	std::pair<int, int> position = PositionWithMario();

	int nx = position.first;
	int ny = position.second;

	int aniId = -1;
	//mario on the left
	if (nx == 1)
	{
		//mario on the top
		if (ny == -1)
			if (!isShooting) aniId = ID_ANI_PLANT_LEFT_UNDER_NOT_SHOOT;
			else aniId = ID_ANI_PLANT_LEFT_UNDER_SHOOT;
		//mario on the bottom
		else if (ny == 1)
			if (!isShooting) aniId = ID_ANI_PLANT_LEFT_TOP_NOT_SHOOT;
			else aniId = ID_ANI_PLANT_LEFT_TOP_SHOOT;

	}
	//mario on the right
	else
	{
		if (ny == -1)
		{
			if (!isShooting) aniId = ID_ANI_PLANT_RIGHT_TOP_NOT_SHOOT;
			else aniId = ID_ANI_PLANT_RIGHT_TOP_SHOOT;
		}
		else
		{
			if (!isShooting) aniId = ID_ANI_PLANT_RIGHT_UNDER_NOT_SHOOT;
			else aniId = ID_ANI_PLANT_RIGHT_UNDER_SHOOT;
		}
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	std::pair<int, int> position = PositionWithMario();

	int nx = position.first;
	int ny = position.second;

	if (isUpping) {
		if (y > minY) {
			vy = -PLANT_SPEED_UP_DOWN;
		}
		else
		{
			vy = 0;
			y = minY;
			SetState(PLANT_STATE_DOWN);
		}
	}
	else if (isDowning) {
		if (model == PLANT_SHOOT_GREEN || model == PLANT_SHOOT_RED) {
			if ((y < startY + 2)) {
				vy = PLANT_SPEED_UP_DOWN;
			}
			else {
				vy = 0;
				y = startY + 2;
				SetState(PLANT_STATE_UP);
			}
		}
	}

	// Create Bullet
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CFireBullet* fire = new CFireBullet(50, y, nx, ny);
	scene->AddObject(fire);

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

}

void CPlant::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}


void CPlant::SetState(int state) {
	switch (state) {
	case PLANT_STATE_UP:
		isUpping = true;
		isDowning = false;
		isShooting = false;

		break;
	case PLANT_STATE_DOWN:
		isUpping = false;
		isDowning = true;
		isShooting = false;
		break;
	case PLANT_STATE_DEATH:
		isDeleted = true;
		break;
	}
	CGameObject::SetState(state);
}

std::pair<int, int> CPlant::PositionWithMario() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int nx, ny;

	// -1: mario on the left
	nx = (mario->GetX() < x) ? 1 : -1;

	// -1: mario on the top
	ny = (mario->GetY() < y) ? 1 : -1;

	return std::make_pair(nx, ny);
}