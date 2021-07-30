#pragma once
#pragma once
#include "GameObject.h"

#define BLOCK_BBOX_WIDTH  16
#define BLOCK_BBOX_HEIGHT 7

class CBlock : public CGameObject
{
public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
