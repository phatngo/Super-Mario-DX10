#include "Camera.h"


CCamera* CCamera::__instance = NULL;
CCamera *CCamera::GetInstance() {
	if (__instance == NULL) __instance = new CCamera();
	return __instance;
}

void CCamera::SetCameraPosition(int maxCX, int cx) {
	if (cx < MARIO_MINIMUM_POSITION_X) {
		CGame::GetInstance()->SetCamPos(0, CAMERA_HEIGHT);
	}
	else if (cx >= MARIO_MINIMUM_POSITION_X && cx < maxCX) {
		CGame::GetInstance()->SetCamPos((int)cx - MARIO_MINIMUM_POSITION_X, CAMERA_HEIGHT);
	}
	else if (cx >= maxCX) {
		CGame::GetInstance()->SetCamPos((int)maxCX, CAMERA_HEIGHT);
	}
}
