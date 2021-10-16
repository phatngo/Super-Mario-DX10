#include "EffectPoint.h"
#include "Utils.h"

EffectPoint::EffectPoint() {
	SetState(EFFECT_POINT_STATE_EXIST);
}

void EffectPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	y += dy;
	if (this->state == EFFECT_POINT_STATE_EXIST) {
		if (start_Y - y >= POINT_FLYING_DY) {
			SetState(EFFECT_POINT_STATE_NON_EXIST);
		}
	}
}

void EffectPoint::Render() {
		
	animation_set->at(POINT_GENERAL_ANI)->Render(x, y);
}

void EffectPoint::SetState(int state) {
	switch (state)
	{
	case EFFECT_POINT_STATE_EXIST:
		vy = -POINT_SPEED_Y;
		break;
	case EFFECT_POINT_STATE_NON_EXIST:
		vy = 0;
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}
