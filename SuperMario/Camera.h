#pragma once
#include "Game.h"


#define MARIO_MINIMUM_POSITION_X 80
#define CAMERA_POSITION_Y 215

class CCamera
{
	static CCamera* __instance;
	int cameraPositionX;
	int cameraPositionY;

public:
	D3DXVECTOR3 GetPositionInCamera(D3DXVECTOR3 position);
	static CCamera* GetInstance();
	void SetCameraPosition(int maxCx, int cx);
	int GetCameraX() { return this->cameraPositionX; }
};

