#pragma once
#include "Game.h"


#define CAMERA_EXTRA_Y 40

class CCamera
{
	static CCamera* __instance;
	int cameraPositionX;
	int cameraPositionY;
	float playerStartX;
	int standardCameraPositionY;
	int cameraFurthestPositionY;
	bool isAbove = false;
public:
	D3DXVECTOR3 GetPositionInCamera(D3DXVECTOR3 position);
	static CCamera* GetInstance();
	void SetCameraPosition(float marioX, int mapWidth);
	void SetStandardCameraPositionY(int standardCameraPositionY) { this->standardCameraPositionY = standardCameraPositionY; }
	void SetCameraFurthestPositionY(int cameraFurthestPositionY) { this->cameraFurthestPositionY = cameraFurthestPositionY; }
	int GetCameraX() { return this->cameraPositionX; }
	int GetCameraY() { return this->cameraPositionY; }
	void SetPlayerStartX(float playerStartX) { this->playerStartX = playerStartX; }
	bool IsAbove() { return this->isAbove; }
};

