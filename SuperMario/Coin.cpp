#include "Coin.h"
CCoin::CCoin()
{
	this->SetState(COIN_STATE_EXIST);
}

CCoin::CCoin(int tag)
{
	this->tag = tag;
	this->SetState(COIN_STATE_JUMPING);
}

void CCoin::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + COIN_BBOX_WIDTH;
	bottom = y + COIN_BBOX_HEIGHT;
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (tag == TAG_COIN_IN_BRICK)
		y += dy;
}

void CCoin::Render()
{
	if (this->tag == TAG_COIN_IN_BRICK) {
		switch (this->state)
		{
		case COIN_STATE_JUMPING:
			if (start_Y - y >= COIN_JUMP_MAX_DY) {
				this->SetState(COIN_STATE_FALLING);
			}
			animation_set->at(0)->Render(x, y);
			RenderBoundingBox();
			break;
		case COIN_STATE_FALLING:
			if (start_Y - y <= COIN_JUMP_DISAPPEAR_DY) {
				this->SetState(COIN_STATE_NON_EXIST);
			}
			animation_set->at(0)->Render(x, y);
			RenderBoundingBox();
		default:
			break;
		}
	}
	else if (state == COIN_STATE_EXIST) {
		animation_set->at(0)->Render(x, y);
		RenderBoundingBox();
	}
}

void CCoin::SetState(int state)
{
	switch (state)
	{
	case COIN_STATE_JUMPING:
		vy = -COIN_JUMP_SPEED_Y;
		break;
	case COIN_STATE_FALLING:
		vy = COIN_JUMP_SPEED_Y;
		break;
	case COIN_STATE_NON_EXIST:
		vy = 0;
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
	
}
