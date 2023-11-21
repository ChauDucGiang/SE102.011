#include "Enemy.h"

std::pair<int, int> CEnemy::PositionWithMario() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int nx, ny;
	// 1: mario on the left
	nx = (mario->GetX() < x) ? 1 : -1;

	// 1: mario on the top
	ny = (mario->GetY() < y) ? 1 : -1;

	return std::make_pair(nx, ny);
}