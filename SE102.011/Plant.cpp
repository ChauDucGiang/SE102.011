#include "Plant.h"
#include "FireBullet.h"
#include "PlayScene.h"


CPlant::CPlant(float x, float y, int model) :CGameObject(x, y) {
	this->startX = x;
	this->startY = y;
	this->model = model;
	this->minY = y - PLANT_BBOX_HEIGHT;
	SetState(PLANT_STATE_UP);
}

void CPlant::Render() {
	int aniId;
	switch (model)
	{
	case PLANT_FIRE_PIRAHA_RED:
		aniId = GetModelFirePirahaRedAnimation();
		break;
	case PLANT_FIRE_PIRAHA_GREEN:
		aniId = GetModelFirePirahaGreenAnimation();
		break;
	case PLANT_PIRAHA_GREEN:
		aniId = GetModelPirahaGreenAnimation();
		break;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

#pragma region Animations

int CPlant::GetModelFirePirahaGreenAnimation() {
	std::pair<int, int> position = PositionWithMario();

	int nx = position.first;
	int ny = position.second;

	int aniId;


	//mario on the left
	if (nx == -1)
	{
		//mario on the top
		if (ny == -1)
			if (!isShooting) aniId = ID_ANI_PLANT_FIRE_PIRAHA_GREEN_LEFT_UNDER_NOT_SHOOT;
			else aniId = ID_ANI_PLANT_FIRE_PIRAHA_GREEN_LEFT_UNDER_SHOOT;
		//mario on the top
		else if (ny == 1)
			if (!isShooting) aniId = ID_ANI_PLANT_FIRE_PIRAHA_GREEN_LEFT_TOP_NOT_SHOOT;
			else aniId = ID_ANI_PLANT_FIRE_PIRAHA_GREEN_LEFT_TOP_SHOOT;

	}
	//mario on the right
	else
	{
		if (ny == 1)
		{
			if (!isShooting) aniId = ID_ANI_PLANT_FIRE_PIRAHA_GREEN_RIGHT_TOP_NOT_SHOOT;
			else aniId = ID_ANI_PLANT_FIRE_PIRAHA_GREEN_RIGHT_TOP_SHOOT;
		}
		else
		{
			if (!isShooting) aniId = ID_ANI_PLANT_FIRE_PIRAHA_GREEN_RIGHT_UNDER_NOT_SHOOT;
			else aniId = ID_ANI_PLANT_FIRE_PIRAHA_GREEN_RIGHT_UNDER_SHOOT;
		}
	}

	return aniId;
}

int CPlant::GetModelFirePirahaRedAnimation() {
	std::pair<int, int> position = PositionWithMario();

	int nx = position.first;
	int ny = position.second;

	int aniId;

	//mario on the left
	if (nx == -1)
	{
		//mario on the top
		if (ny == -1)
			if (!isShooting) aniId = ID_ANI_PLANT_FIRE_PIRAHA_RED_LEFT_UNDER_NOT_SHOOT;
			else aniId = ID_ANI_PLANT_FIRE_PIRAHA_RED_LEFT_UNDER_SHOOT;
		//mario on the top
		else if (ny == 1)
			if (!isShooting) aniId = ID_ANI_PLANT_FIRE_PIRAHA_RED_LEFT_TOP_NOT_SHOOT;
			else aniId = ID_ANI_PLANT_FIRE_PIRAHA_RED_LEFT_TOP_SHOOT;

	}
	//mario on the right
	else
	{
		if (ny == 1)
		{
			if (!isShooting) aniId = ID_ANI_PLANT_FIRE_PIRAHA_RED_RIGHT_TOP_NOT_SHOOT;
			else aniId = ID_ANI_PLANT_FIRE_PIRAHA_RED_RIGHT_TOP_SHOOT;
		}
		else
		{
			if (!isShooting) aniId = ID_ANI_PLANT_FIRE_PIRAHA_RED_RIGHT_UNDER_NOT_SHOOT;
			else aniId = ID_ANI_PLANT_FIRE_PIRAHA_RED_RIGHT_UNDER_SHOOT;
		}
	}

	return aniId;
}

int CPlant::GetModelPirahaGreenAnimation() {
	return ID_ANI_PLANT_PIRAHA_GREEN;
}



#pragma endregion


void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (isUpping) {
		if (y > minY) {
			vy = -PLANT_SPEED_UP_DOWN;
		}
		else
		{
			shootStart = GetTickCount64();
			vy = 0;
			y = minY;
			if (GetTickCount64() - outPipeStart > TIME_OUT_PIPE) {
				SetState(PLANT_STATE_DOWN);
			}
			else
			{
				if (!isShooting && (GetTickCount64() - shootStart < TIME_SHOOT)) {
					Shoot();
				}
		
			}
		}
	}
	else if (isDowning) {
		if (y < startY) {
			vy = PLANT_SPEED_UP_DOWN;
		}
		else {
			vy = 0;
			y = startY;
			float distance = abs(mario->GetX() - x);
			if (GetTickCount64() - inPipeStart > TIME_IN_PIPE && distance > HIDE_DISTANCE) {
				SetState(PLANT_STATE_UP);
			}
		}
	}

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
		outPipeStart = GetTickCount64();
		inPipeStart = 0;

		break;
	case PLANT_STATE_DOWN:
		isUpping = false;
		isDowning = true;
		isShooting = false;
		outPipeStart = 0;
		inPipeStart = GetTickCount64();

		break;
	case PLANT_STATE_DIE:
		isDeleted = true;
		break;
	}
	CGameObject::SetState(state);
}

std::pair<int, int> CPlant::PositionWithMario() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int nx, ny;
	// 1: mario on the left
	nx = (mario->GetX() > x) ? 1 : -1;

	// 1: mario on the top
	ny = (mario->GetY() < y) ? 1 : -1;

	return std::make_pair(nx, ny);
}

void CPlant::Shoot() {
	std::pair<int, int> position = PositionWithMario();

	int nx = position.first;
	int ny = position.second;

	isShooting = true;
	// Create Bullet
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CFireBullet* bullet = new CFireBullet(x, y, nx, ny);
	scene->AddObject(bullet);
}