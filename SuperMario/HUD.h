#pragma once
#include"GameObject.h"
#include"Sprites.h"
#define FONT_BBOX_WIDTH						8
#define DEFAULT_TIME						300

#define SPRITE_ICONMARIO_ID					50003
#define SPRITE_ICONLUIGI_ID					50004
#define SPRITE_FILLARROW_ID					50005
#define ANI_P_ID							5006

#define PLAYSCENE_HUD	                    0
#define WORLDSCENE_HUD	                    1

#define CARD_ANI_SET_ID	                    58

#define HUD_HEIGHT                          32
#define HUD_CY                              395

class HUD:public CGameObject
{
	int type;
public:
	virtual void Render();
	virtual void Update(DWORD dt) {};
	virtual void GetBoundingBox(float& oLeft, float& oTop, float& oRight, float& oBottom) {};
	HUD();
};

