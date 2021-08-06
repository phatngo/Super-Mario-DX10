#pragma once
#include "GameObject.h"

#define LEAF_ANI_SET_ID 36

#define LEAF_ANI_A 0
#define LEAF_ANI_B 1

#define LEAF_SPEED_Y 0.05f
#define LEAF_SPEED_X 0.05f

#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 14

#define LEAF_STATE_FLY_DOWN_LEFT 300
#define LEAF_STATE_FLY_DOWN_RIGHT 200
#define LEAF_STATE_FLY_UP 100

class CLeaf : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CLeaf();
	virtual void SetState(int state);
};
