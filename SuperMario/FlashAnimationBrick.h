#pragma once
#include "Brick.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16


class CFlashAnimationBrick : public CBrick
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	CFlashAnimationBrick();
	void SetState(int state);
}; 
