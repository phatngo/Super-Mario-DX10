#pragma once

#include "GameObject.h"
#include "Timer.h"

#define KOOPAS_WALKING_SPEED         0.02f;
#define KOOPAS_GRAVITY               0.001f

#define KOOPAS_TAG_RED               1
#define KOOPAS_TAG_GREEN             2

#define KOOPAS_BBOX_RED_WIDTH        16
#define KOOPAS_BBOX_RED_HEIGHT_1     27
#define KOOPAS_BBOX_RED_HEIGHT_2     26
#define KOOPAS_BBOX_RED_HEIGHT_DIE   16

#define KOOPAS_STATE_WALKING_LEFT    100
#define KOOPAS_STATE_WALKING_RIGHT   200
#define KOOPAS_STATE_DIE             300

#define KOOPAS_ANI_RED_WALKING_LEFT  2
#define KOOPAS_ANI_RED_WALKING_RIGHT 0
#define KOOPAS_ANI_RED_DIE           6

class CKoopas : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	void UpdateRedKoopas(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int tag;
	Timer timer;
	int currentHeight;
public:
	CKoopas(int tag);
	virtual void SetState(int state);
};