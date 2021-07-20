#include "GameObject.h"

#define QUESTION_BRICK_STATE_SPINNING 602
#define QUESTION_BRICK_STATE_STOP 6021

#define QUESTION_BRICK_ANI_SPINNING 0
#define QUESTION_BRICK_ANI_STOP 1
#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CQuestionBrick : public CGameObject
{
	int currentState;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	CQuestionBrick();
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
#pragma once
