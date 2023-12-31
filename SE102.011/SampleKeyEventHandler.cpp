#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	switch (KeyCode)
	{
	case DIK_DOWN:
		if (mario->CanDown())
		{
			mario->SetState(MARIO_STATE_GOING_DOWN_PIPE);
		}
		else {
			mario->SetState(MARIO_STATE_SIT);
		}
		break;
	case DIK_S:
		if (mario->CanFly() && !mario->IsFlying()) {
			if (mario->GetLevel() == MARIO_LEVEL_TAIL)
			{
				mario->SetState(MARIO_STATE_FLY);
			}
		}
		else if (mario->IsFlying())
		{
			if (mario->GetLevel() == MARIO_LEVEL_TAIL)
			{
				mario->FlyUp();
			}
		}else{
			mario->SetState(MARIO_STATE_JUMP);
		}
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_4:
		mario->SetLevel(MARIO_LEVEL_TAIL);
		break;
	case DIK_5:
		mario->GoToHiddenMap(); // Go To Hidden Map
		break;
	case DIK_6:
		mario->ReturnToWorldMap(); // Out Hidden Map
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	case DIK_A:
		if (mario->GetLevel() == MARIO_LEVEL_TAIL) mario->SetState(MARIO_STATE_TAIL_ATTACK);
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetState() != MARIO_STATE_END_SCENE)
	{
		if (game->IsKeyDown(DIK_RIGHT))
		{
			if (game->IsKeyDown(DIK_A))
				mario->SetState(MARIO_STATE_RUNNING_RIGHT);
			else
				mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			if (game->IsKeyDown(DIK_A))
				mario->SetState(MARIO_STATE_RUNNING_LEFT);
			else
				mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
		else
			mario->SetState(MARIO_STATE_IDLE);
	}
}