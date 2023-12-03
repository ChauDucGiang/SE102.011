#pragma once
#include "GameObject.h"

#define PLANT_SPEED_UP_DOWN 0.025f

#define TIME_OUT_PIPE 5000
#define TIME_SHOOT 100
#define TIME_IN_PIPE 3000


//Type
#define PLANT_FIRE_PIRAHA_RED 1
#define PLANT_FIRE_PIRAHA_GREEN 2
#define PLANT_PIRAHA_GREEN 3


#define PLANT_BBOX_WIDTH 12
#define PLANT_BBOX_HEIGHT_SMALL 24
#define PLANT_BBOX_HEIGHT 32

#define PLANT_STATE_UP 100
#define PLANT_STATE_DOWN 200
#define PLANT_STATE_DIE 300

//Fire Piraha Red
#define ID_ANI_PLANT_FIRE_PIRAHA_RED_LEFT_UNDER_NOT_SHOOT	301
#define ID_ANI_PLANT_FIRE_PIRAHA_RED_LEFT_UNDER_SHOOT 302
#define ID_ANI_PLANT_FIRE_PIRAHA_RED_LEFT_TOP_NOT_SHOOT 303
#define ID_ANI_PLANT_FIRE_PIRAHA_RED_LEFT_TOP_SHOOT 304
#define ID_ANI_PLANT_FIRE_PIRAHA_RED_RIGHT_UNDER_NOT_SHOOT	305
#define ID_ANI_PLANT_FIRE_PIRAHA_RED_RIGHT_UNDER_SHOOT 306
#define ID_ANI_PLANT_FIRE_PIRAHA_RED_RIGHT_TOP_NOT_SHOOT 307
#define ID_ANI_PLANT_FIRE_PIRAHA_RED_RIGHT_TOP_SHOOT 308

//Fire Piraha Green
#define ID_ANI_PLANT_FIRE_PIRAHA_GREEN_LEFT_UNDER_NOT_SHOOT	321
#define ID_ANI_PLANT_FIRE_PIRAHA_GREEN_LEFT_UNDER_SHOOT 322
#define ID_ANI_PLANT_FIRE_PIRAHA_GREEN_LEFT_TOP_NOT_SHOOT 323
#define ID_ANI_PLANT_FIRE_PIRAHA_GREEN_LEFT_TOP_SHOOT 324
#define ID_ANI_PLANT_FIRE_PIRAHA_GREEN_RIGHT_UNDER_NOT_SHOOT 325
#define ID_ANI_PLANT_FIRE_PIRAHA_GREEN_RIGHT_UNDER_SHOOT 326
#define ID_ANI_PLANT_FIRE_PIRAHA_GREEN_RIGHT_TOP_NOT_SHOOT 327
#define ID_ANI_PLANT_FIRE_PIRAHA_GREEN_RIGHT_TOP_SHOOT 328

//Piraha Green
#define ID_ANI_PLANT_PIRAHA_GREEN 311
#define DISTANCE_PIPE_LONG_SHORT 8

#define HIDE_DISTANCE 50

class  CPlant : public CGameObject
{
	protected:
		float startX, startY, minY;
		int model;
		ULONGLONG shootStart, outPipeStart, inPipeStart;
		bool isUpping, isDowning, isShooting = false;
		virtual void Render();
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
		virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

		virtual int IsCollidable() { return 1; };
		virtual int IsBlocking() { return 0; }
		virtual void OnNoCollision(DWORD dt);

		int GetModelFirePirahaGreenAnimation();
		int GetModelFirePirahaRedAnimation();
		int GetModelPirahaGreenAnimation();
	public :
		CPlant(float x, float y, int model);

		int GetModel() { return model; }
		void SetModel(int model) { this->model = model; };

		virtual void SetState(int state);
		int GetState() { return state; };
		std::pair<int, int> PositionWithMario();

		virtual void Shoot();
};