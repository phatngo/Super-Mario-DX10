#include "Mushroom.h"
#include "Brick.h"
#include "Game.h"
#include "Mario.h"
#include "QuestionBrick.h"
#include "Utils.h"

CMushroom::CMushroom()
{
	this->SetState(MUSHROOM_STATE_IDLE);
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + MUSHROOM_BBOX_WIDTH;
	bottom = y + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		vy += ay * dt;
		coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);
		// No collision occured, proceed normally
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;

			if (ny != 0) vy = 0;

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				float mLeft, mTop, mRight, mBottom;
				GetBoundingBox(mLeft, mTop, mRight, mBottom);
				if (dynamic_cast<CBrick*>(e->obj)||dynamic_cast<CQuestionBrick*>(e->obj))
				{
					if (e->ny != 0)
					{
						vy = 0;
						ay = MUSHROOM_GRAVITY;
					}
				}
			}
		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMushroom::Render()
{
	int ani = MUSHROOM_ANI_NORMAL;
	switch (this->state) {
	case MUSHROOM_STATE_IDLE:
		if (start_Y - y >= MUSHROOM_BBOX_HEIGHT) {
			this->SetState(MUSHROOM_STATE_MOVING);
		}
		animation_set->at(ani)->Render(x, y);
		RenderBoundingBox();
		break;
	case MUSHROOM_STATE_MOVING:
		animation_set->at(ani)->Render(x, y);
		RenderBoundingBox();
		break;
	default:
		break;
	}
}

void CMushroom::SetState(int state)
{
	switch (state)
	{
	case MUSHROOM_STATE_IDLE:
		vy = -MUSHROOM_Y_VELOCITY;
		vx = 0;
		break;
	case MUSHROOM_STATE_MOVING:
		vx = -MUSHROOM_X_VELOCITY;
		ay = MUSHROOM_GRAVITY;
		vy = 0;
		break;
	case MUSHROOM_STATE_NOT_EXIST:
		vx = 0;
		vy = 0;
	default:
		break;
	}
	CGameObject::SetState(state);

}
