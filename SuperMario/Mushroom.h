#pragma once
#include "GameObject.h"


class CMushroom : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CMushroom();
	virtual void SetState(int state);
};
