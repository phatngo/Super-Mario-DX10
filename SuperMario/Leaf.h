#pragma once
#include "GameObject.h"


class CLeaf : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CLeaf();
	virtual void SetState(int state);
};
