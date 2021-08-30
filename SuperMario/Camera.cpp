#include "Camera.h"
#include "HUD.h"


CCamera* CCamera::__instance = NULL;

CCamera* CCamera::GetInstance() {
	if (__instance == NULL) __instance = new CCamera();
	return __instance;
}

void CCamera::SetCameraPosition(int maxCX, int cx) {
	if (cx < MARIO_MINIMUM_POSITION_X) {
		cameraPositionX = 0;
		cameraPositionY = CAMERA_POSITION_Y;
		
	}
	else if (cx >= MARIO_MINIMUM_POSITION_X && cx < maxCX) {
		cameraPositionX = (int)cx - MARIO_MINIMUM_POSITION_X;
		cameraPositionY = CAMERA_POSITION_Y;
		
	}
	else if (cx >= maxCX) {
		cameraPositionX = (int)maxCX;
		cameraPositionY = CAMERA_POSITION_Y;
		
	}

	CGame::GetInstance()->SetCamPos(cameraPositionX,cameraPositionY);
}

D3DXVECTOR3 CCamera::GetPositionInCamera(D3DXVECTOR3 position)
{
	D3DXVECTOR3 pos;
	pos.x = position.x - cameraPositionX;
	pos.y = position.y - cameraPositionY;
	return D3DXVECTOR3(pos.x, pos.y, 0);
}