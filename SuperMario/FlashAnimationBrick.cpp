#include "FlashAnimationBrick.h"

void CFlashAnimationBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
}

void CFlashAnimationBrick::Render() {
	int ani = FLASH_BRICK_ANI_FLASHING;
	if (currentState == FLASH_BRICK_STATE_FLASHING) {
		int ani = FLASH_BRICK_ANI_FLASHING;
	}
	animation_set->at(ani)->Render(x, y);
}

CFlashAnimationBrick::CFlashAnimationBrick() {
	SetState(FLASH_BRICK_STATE_FLASHING);
}

void CFlashAnimationBrick::SetState(int state) {
	if (state == FLASH_BRICK_STATE_FLASHING) {
		currentState = FLASH_BRICK_STATE_FLASHING;
	}
}

void CFlashAnimationBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

