#pragma once
#include "Game.h"

//Normal Height: 206
#define MARIO_MINIMUM_POSITION_X 80
#define CAMERA_POSITION_Y 238
#define CAMERA_FURTHEST_RIGHT_COORD 2894

class CCamera
{
	static CCamera* __instance;
	int cameraPositionX;
	int cameraPositionY;
	float playerStartX;

public:
	D3DXVECTOR3 GetPositionInCamera(D3DXVECTOR3 position);
	static CCamera* GetInstance();
	void SetCameraPosition(float marioX, int mapWidth);
	int GetCameraX() { return this->cameraPositionX; }
	int GetCameraY() { return this->cameraPositionY; }
	void SetPlayerStartX(float playerStartX) { this->playerStartX = playerStartX; }
};

