#include "FireBullet.h"
#include "FirePiranhaPlant.h"

CFireBullet::CFireBullet(float x, float y, int FirePiranhaPlant_CurrentState)
{
	CGameObject::SetPosition(x, y);
	
	switch (FirePiranhaPlant_CurrentState)
	{
	case FIRE_PIRANHA_ANI_UP_RIGHT:
		this->SetState(FIRE_BULLET_STATE_UP_RIGHT);
		break;
	case FIRE_PIRANHA_ANI_UP_LEFT:
		this->SetState(FIRE_BULLET_STATE_UP_LEFT);
		break;
	case FIRE_PIRANHA_ANI_DOWN_RIGHT:
		this->SetState(FIRE_BULLET_STATE_DOWN_RIGHT);
		break;
	case FIRE_PIRANHA_ANI_DOWN_LEFT:
		this->SetState(FIRE_BULLET_STATE_DOWN_LEFT);
		break;
	default:
		break;
	}
}

void CFireBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FIRE_BULLET_BBOX_WIDTH;
	bottom = y + FIRE_BULLET_BBOX_HEIGHT;
}

void CFireBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	y += dy;
	x += dx;
}

void CFireBullet::Render()
{
	animation_set->at(this->ani)->Render(x, y);
}

void CFireBullet::SetState(int state)
{
	switch (state)
	{
	case FIRE_BULLET_STATE_UP_RIGHT:
		this->SetPosition(x + FIRE_BULLET_BBOX_WIDTH, y + FIRE_BULLET_BBOX_HEIGHT);
		vx = FIRE_BULLET_X_VELOCITY;
		vy = -FIRE_BULLET_Y_VELOCITY;
		break;
	case FIRE_BULLET_STATE_UP_LEFT:
		vx = -FIRE_BULLET_X_VELOCITY;
		vy = -FIRE_BULLET_Y_VELOCITY;
		break;
	case FIRE_BULLET_STATE_DOWN_LEFT:
		vx = -FIRE_BULLET_X_VELOCITY;
		vy = FIRE_BULLET_Y_VELOCITY;
		break;
	case FIRE_BULLET_STATE_DOWN_RIGHT:
		this->SetPosition(x + FIRE_BULLET_BBOX_WIDTH, y + FIRE_BULLET_BBOX_HEIGHT);
		vx = FIRE_BULLET_X_VELOCITY;
		vy = FIRE_BULLET_Y_VELOCITY;
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}



