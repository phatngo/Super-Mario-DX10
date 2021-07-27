#pragma once
#include "GameObject.h"

#define COIN_BBOX_WIDTH  16
#define COIN_BBOX_HEIGHT 5
#define COIN_JUMP_SPEED_Y	0.6f
#define COIN_STATE_NON_EXIST 0
#define COIN_STATE_EXIST 1


class CCoin : public CGameObject
{
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CCoin();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
}; 
