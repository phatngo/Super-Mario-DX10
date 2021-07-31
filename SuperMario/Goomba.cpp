#include "Goomba.h"
#include "Brick.h"
#include "QuestionBrick.h"
CGoomba::CGoomba()
{
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else 	
		bottom = y + GOOMBA_BBOX_HEIGHT;
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
	CGameObject::Update(dt);
	DebugOut(L"Goomba VX: %f \n", vx);
	DebugOut(L"Goomba DX: %f \n", dx);
	DebugOut(L"Goomba X: %f \n", x);
	DebugOut(L"Goomba Y: %f \n", y);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vy += ay*dt;

	coEvents.clear();

	// turn off collision when die 
	if (state != GOOMBA_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		DebugOut(L"Goomba not collided \n");
		x += dx;
		y += dy;	
	}
	else
	{
		DebugOut(L"Goomba collided \n");
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
			if (dynamic_cast<CBrick*>(e->obj))
			{
				float oLeft, oTop, oRight, oBottom;
				CBrick* object = dynamic_cast<CBrick*>(e->obj);
				object->GetBoundingBox(oLeft, oTop, oRight, oBottom);
				
				if (e->ny != 0)
				{
					vy = 0;
					ay = GOOMBA_GRAVITY;
				}
				if (e->nx != 0)
				{
					if (ceil(mBottom) != oTop)
					{
						vx = -vx;
						this->nx = -this->nx;
					}
				}
				
			}
			else if (dynamic_cast<CQuestionBrick*>(e->obj)) {
				float oLeft, oTop, oRight, oBottom;
				CQuestionBrick* object = dynamic_cast<CQuestionBrick*>(e->obj);
				object->GetBoundingBox(oLeft, oTop, oRight, oBottom);

				if (e->ny != 0)
				{
					vy = 0;
					ay = GOOMBA_GRAVITY;
				}
				if (e->nx != 0)
				{
					if (ceil(mBottom) != oTop)
					{
						vx = -vx;
						this->nx = -this->nx;
					}
				}
			}
			else if (dynamic_cast<CGoomba*>(e->obj)) {
				//When goomba touches each other
				if (e->nx != 0) {
					x += dx;
				}
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CGoomba::Render()
{
	int ani = GOOMBA_ANI_WALKING;
	if (state == GOOMBA_STATE_DIE) {
		ani = GOOMBA_ANI_DIE;
	}

	animation_set->at(ani)->Render(x,y);

	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
			vx = 0;
			vy = 0;
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
			ay = GOOMBA_GRAVITY;
			break;
	}
}
