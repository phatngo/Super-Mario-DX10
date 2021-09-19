#include "Camera.h"
#include "HUD.h"


CCamera* CCamera::__instance = NULL;

CCamera* CCamera::GetInstance() {
	if (__instance == NULL) __instance = new CCamera();
	return __instance;
}

void CCamera::SetCameraPosition(float marioX, int mapWidth) {

	if ((int)marioX < playerStartX) {
		cameraPositionX = 0;
		cameraPositionY = CAMERA_POSITION_Y;

	}
	else if ((int)marioX + CGame::GetInstance()->GetScreenWidth() <= CAMERA_FURTHEST_RIGHT_COORD) {
		cameraPositionX = (int)marioX - playerStartX;
		cameraPositionY = CAMERA_POSITION_Y;

	}
	else {
		cameraPositionX = CAMERA_FURTHEST_RIGHT_COORD - CGame::GetInstance()->GetScreenWidth() - (CAMERA_FURTHEST_RIGHT_COORD - mapWidth);
		cameraPositionY = CAMERA_POSITION_Y;
	}

	CGame::GetInstance()->SetCamPos(cameraPositionX, cameraPositionY);
}

D3DXVECTOR3 CCamera::GetPositionInCamera(D3DXVECTOR3 position)
{
	D3DXVECTOR3 pos;
	pos.x = position.x - cameraPositionX;
	pos.y = position.y - cameraPositionY;
	return D3DXVECTOR3(pos.x, pos.y, 0);
}