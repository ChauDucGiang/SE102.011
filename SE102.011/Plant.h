#pragma once
#include "GameObject.h"

#define PLANT_SPEED_UP_DOWN 0.025f

#define TIME_OUT_PIPE 5000
#define TIME_SHOOT 100
#define TIME_DOWN_PIPE 3000

#define PLANT_SHOOT_RED 1
#define PLANT_SHOOT_GREEN 2
#define PLANT_NOT_SHOOT 3


#define PLANT_BBOX_WIDTH 12
#define PLANT_BBOX_HEIGHT_SMALL 24
#define PLANT_BBOX_HEIGHT 32

#define PLANT_STATE_UP 100
#define PLANT_STATE_DOWN 200
#define PLANT_STATE_DEATH 300

#define ID_ANI_PLANT_LEFT_UNDER_NOT_SHOOT	301
#define ID_ANI_PLANT_LEFT_UNDER_SHOOT 302
#define ID_ANI_PLANT_LEFT_TOP_NOT_SHOOT 303
#define ID_ANI_PLANT_LEFT_TOP_SHOOT 304
#define ID_ANI_PLANT_RIGHT_UNDER_NOT_SHOOT	305
#define ID_ANI_PLANT_RIGHT_UNDER_SHOOT 306
#define ID_ANI_PLANT_RIGHT_TOP_NOT_SHOOT 307
#define ID_ANI_PLANT_RIGHT_TOP_SHOOT 308

#define ID_ANI_PLANT_LEFT_UNDER_NOT_SHOOT_GREEN	321
#define ID_ANI_PLANT_LEFT_UNDER_SHOOT_GREEN 322
#define ID_ANI_PLANT_LEFT_TOP_NOT_SHOOT_GREEN 323
#define ID_ANI_PLANT_LEFT_TOP_SHOOT_GREEN 324
#define ID_ANI_PLANT_RIGHT_UNDER_NOT_SHOOT_GREEN 325
#define ID_ANI_PLANT_RIGHT_UNDER_SHOOT_GREEN 326
#define ID_ANI_PLANT_RIGHT_TOP_NOT_SHOOT_GREEN 327
#define ID_ANI_PLANT_RIGHT_TOP_SHOOT_GREEN 328

#define ID_ANI_PLANT_NOT_SHOOT 311
#define DISTANCE_PIPE_LONG_SHORT 8

class  CPlant : public CGameObject
{
	protected:
		float startX, startY, minY;
		int model;
		ULONGLONG defend_start, die_start, comeback_start;
		bool isUpping, isDowning, isShoottng = false;
		virtual void Render();
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
		virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

		virtual int IsCollidable() { return 1; };
		virtual int IsBlocking() { return 0; }
		virtual void OnNoCollision(DWORD dt);

	public :
		CPlant(float x, float y, int model);

		int GetModel() { return model; }
		void SetModel(int model) { this->model = model; };

		virtual void SetState(int state);
		int GetState() { return state; };
};