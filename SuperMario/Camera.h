#pragma once
#include "Game.h"

#define MARIO_MINIMUM_POSITION_X 80
#define CAMERA_HEIGHT 215

class CCamera
{
	static CCamera* __instance;

public:

	static CCamera* GetInstance();
	void SetCameraPosition(int maxCx, int cx);
};

