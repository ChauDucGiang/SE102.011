#include "BrickQuestion.h"


CBrickQuestion::CBrickQuestion(float x, float y, int model) :CGameObject(x, y)
{
	this->model = model;
	this->ay = 0;
	this->startY = y;
	this->startX = x;
}