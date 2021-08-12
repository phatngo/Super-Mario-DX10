#pragma once
#include "GameObject.h"
#include "Utils.h"
#include "Timer.h"

#define GOOMBA_WALKING_SPEED 0.04f
#define GOOMBA_GRAVITY 0.001f
#define GOOMBA_DIE_DEFLECT_SPEED	0.35f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_NON_EXIST 300

#define GOOMBA_ANI_WALKING 0
#define GOOMBA_ANI_DIE 1
#define GOOMBA_DELAY_TIME 600

class CGoomba : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	Timer transformTimer;

public: 	
	CGoomba();
	virtual void SetState(int state);
};