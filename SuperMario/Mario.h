#pragma once
#include "GameObject.h"
#include "Timer.h"

#define MARIO_WALKING_SPEED		0.15f 
#define MARIO_JUMP_SPEED_Y		0.6f //0.5f
#define MARIO_JUMP_DEFLECT_SPEED 0.5f //0.2f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_DIE				400
#define MARIO_STATE_TRANSFORMING    500

#define MARIO_ANI_BIG_IDLE_RIGHT		14
#define MARIO_ANI_BIG_IDLE_LEFT			22
#define MARIO_ANI_BIG_WALKING_RIGHT		15
#define MARIO_ANI_BIG_WALKING_LEFT		23

#define MARIO_ANI_SMALL_IDLE_RIGHT		0
#define MARIO_ANI_SMALL_IDLE_LEFT	    7
#define MARIO_ANI_SMALL_WALKING_RIGHT	1
#define MARIO_ANI_SMALL_WALKING_LEFT	8

#define MARIO_ANI_TAIL_IDLE_RIGHT		30
#define MARIO_ANI_TAIL_IDLE_LEFT		38
#define MARIO_ANI_TAIL_WALKING_RIGHT	31
#define MARIO_ANI_TAIL_WALKING_LEFT	    39

#define MARIO_ANI_TRANSFORM_BIG_RIGHT	    115
#define MARIO_ANI_TRANSFORM_BIG_LEFT	    116
#define MARIO_ANI_TRANSFORM_TAIL 	        117


#define MARIO_ANI_DIE		8

#define MARIO_LEVEL_TRANSFORM_BIG 0
#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_TAIL	3
#define MARIO_LEVEL_TRANSFORM_TAIL 5

#define MARIO_TAIL_BBOX_WIDTH  21
#define MARIO_TAIL_BBOX_HEIGHT 28

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_SMALL_BBOX_WIDTH  12
#define MARIO_SMALL_BBOX_HEIGHT 16

#define MARIO_UNTOUCHABLE_TIME 5000
#define MARIO_TRANSFORMING_TIME		400


class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	DWORD marioDT;

	float start_x;			// initial position of Mario at scene
	float start_y; 
	Timer transformTimer;
public: 
	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT>* objects=NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	int GetLevel() { return level; }
	void Reset();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};