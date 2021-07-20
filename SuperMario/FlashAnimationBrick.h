#pragma once
#include "Brick.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16
#define FLASH_BRICK_STATE_FLASHING 606
#define FLASH_BRICK_ANI_FLASHING 0

class CFlashAnimationBrick : public CGameObject
{
	int currentState;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	CFlashAnimationBrick();
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
}; 
