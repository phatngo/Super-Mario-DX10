#include "Block.h"

void CBlock::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BLOCK_BBOX_WIDTH;
	bottom = y + BLOCK_BBOX_HEIGHT;
}

void CBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void CBlock::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

