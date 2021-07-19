#include "Brick.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16


class CQuestionBrick : public CBrick
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	CQuestionBrick();
	void SetState(int state);
};
#pragma once
