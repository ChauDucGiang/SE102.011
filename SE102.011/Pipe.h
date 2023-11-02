#pragma once
#include "GameObject.h"

#define PIPE_BBOX_WIDTH 32
#define PIPE_BBOX_HEIGHT_SHORT 32 
#define	PIPE_BBOX_HEIGHT_LONG 48 

#define ID_ANI_PIPE_SHORT 201
#define ID_ANI_PIPE_LONG 202

#define PIPE_SHORT_MODEL 1
#define PIPE_LONG_MODEL	2

class CPipe : public CGameObject
{
	protected:
		int model, plantType;
	public:

		CPipe(float x, float y, int model, int typeFlower);
		void Render();
		void Update(DWORD dt) {}
		void GetBoundingBox(float& left, float& top, float& right, float& bottom);

		virtual int IsColliable() { return 0; }
		virtual int IsBlocking() { return 1; }
		void SetModel(int model) { this->model = model; }
		int GetModel() { return model; }
};