#pragma once
#include "GameObject.h"


class CFirePiranhaPlant : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CFirePiranhaPlant();
	virtual void SetState(int state);
};
