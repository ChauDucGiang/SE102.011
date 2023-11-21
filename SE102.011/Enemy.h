#pragma once
#include "GameObject.h"
#include "PlayScene.h"

class CEnemy : public CGameObject
{
protected:
	std::pair<int, int> PositionWithMario();
public:
	CEnemy(float x, float y) :CGameObject(x, y) {};
};