#include "Portal.h"
#include "Game.h"


CPortal::CPortal(int scene_id, float start_x, float start_y)
{
	this->scene_id = scene_id;
	this->start_x = start_x;
	this->start_y = start_y;
}

void CPortal::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	
	CMario* mario = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
	float mLeft, mTop, mRight, mBottom;
	float oLeft, oTop, oRight, oBottom;

	if (mario != NULL)
	{
		mario->GetBoundingBox(mLeft, mTop, mRight, mBottom);
		GetBoundingBox(oLeft, oTop, oRight, oBottom);
		if (isColliding(floor(mLeft), floor(mTop), ceil(mRight), ceil(mBottom))
			//&& mario->isSitting
			&& mLeft >= oLeft && mRight <= oRight)
		{
			DebugOut(L"Touched with mario \n");
		}
	}
}

void CPortal::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	b = y + PORTAL_BBOX_HEIGHT;
	if (scene_id == 4)
		r = x + PORTAL_BBOX_WIDTH_1_3;
	else
		r = x + PORTAL_BBOX_WIDTH;
}