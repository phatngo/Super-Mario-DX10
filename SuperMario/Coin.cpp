#include "Coin.h"
CCoin::CCoin()
{
	CGameObject::SetState(COIN_STATE_EXIST);
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
	
	
}

void CCoin::Render()
{
	if (state == COIN_STATE_EXIST) {
		animation_set->at(0)->Render(x, y);
		RenderBoundingBox();
	}
}

void CCoin::SetState(int state)
{
	CGameObject::SetState(state);
}
