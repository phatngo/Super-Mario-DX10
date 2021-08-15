#include "Goomba.h"
#include "Brick.h"
#include "QuestionBrick.h"
#include "Game.h"
#include "Utils.h"
#include "PlayScence.h"

CGoomba::CGoomba(int tag)
{
	if (tag == GOOMBA_TAG_YELLOW) {
		SetState(GOOMBA_STATE_YELLOW_WALKING);
		this->SetTag(GOOMBA_TAG_YELLOW);
	}
	else {
		SetState(GOOMBA_STATE_FALLING_LOW);
		this->SetTag(GOOMBA_TAG_RED);
		lowFallingTime = 0;
		isOnGround = false;
	}
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (tag == GOOMBA_TAG_YELLOW) {
		right = x + GOOMBA_BBOX_YELLOW_WIDTH;

		if (state == GOOMBA_STATE_DIE || state == GOOMBA_STATE_NON_EXIST)
			bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
		else
			bottom = y + GOOMBA_BBOX_YELLOW_HEIGHT;
	}
	else {
		if (state == GOOMBA_STATE_RED_WALK_WING) {
			right = x + GOOMBA_BBOX_RED_WALK_WIDTH;
			bottom = y + GOOMBA_BBOX_RED_WALK_HEIGHT;
		}
		else {
			right = x + GOOMBA_BBOX_RED_UNWALK_WIDTH;
			bottom = y + GOOMBA_BBOX_RED_UNWALK_HEIGHT;
		}
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject* player = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
	float mario_X, mario_Y;
	player->GetPosition(mario_X, mario_Y);

	CGameObject::Update(dt);

	if (tag == GOOMBA_TAG_YELLOW) {
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		if (state != GOOMBA_STATE_DIE) {
			vy += ay * dt;
		}

		coEvents.clear();

		// turn off collision when die 
		if (state != GOOMBA_STATE_DIE) {
			CalcPotentialCollisions(coObjects, coEvents);
		}
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

			x += min_tx * dx + nx * PUSHBACK;
			y += min_ty * dy + ny * PUSHBACK;


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
	else {
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		// turn off collision when die 
		if (state != GOOMBA_STATE_DIE) {
			CalcPotentialCollisions(coObjects, coEvents);
		}
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

			x += min_tx * dx + nx * PUSHBACK;
			y += min_ty * dy + ny * PUSHBACK;


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
						if (state == GOOMBA_STATE_FALLING_LOW || state == GOOMBA_STATE_FALLING_HIGH) {
							lowFallingTime++;
						}
						vy = 0;
						ay = GOOMBA_GRAVITY;
						isOnGround = true;
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
						DebugOut(L"Here 1");
						vy = -vy;
						vx = -GOOMBA_FALLING_LOW_SPEED_X;
						/*if (mario_X < this->x) {
							vx = -GOOMBA_JUMPING_LOW_SPEED_X;
						}
						else {
							vx = GOOMBA_JUMPING_LOW_SPEED_X;
						}*/
						isOnGround = true;
						ay = GOOMBA_GRAVITY;
					}
					if (e->nx != 0)
					{
						if (ceil(mBottom) != oTop)
						{
							DebugOut(L"Here 2");
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
}

void CGoomba::Render()
{
	int ani = -1;
	if (tag == GOOMBA_TAG_YELLOW) {
		ani = GOOMBA_ANI_YELLOW_WALKING;
		if (state == GOOMBA_STATE_DIE) {
			if (this->transformTimer.ElapsedTime() >= GOOMBA_DELAY_TIME && this->transformTimer.IsStarted()) {
				this->SetState(GOOMBA_STATE_NON_EXIST);
			}
			ani = GOOMBA_ANI_YELLOW_DIE;
		}
		else
			ani = GOOMBA_ANI_YELLOW_WALKING;
	}
	else {
		ani = GOOMBA_ANI_RED_JUMPING;
		if (isOnGround) 
		{
			if (this->state == GOOMBA_STATE_FALLING_LOW) {
				if (lowFallingTime > 3) {
					lowFallingTime = 0;
					this->SetState(GOOMBA_STATE_JUMPING_HIGH);
				}
				else {
					this->SetState(GOOMBA_STATE_JUMPING_LOW);
				}
				isOnGround = false;
				ani = GOOMBA_ANI_RED_JUMPING;
			}
			else if(this->state == GOOMBA_STATE_FALLING_HIGH){
					this->SetState(GOOMBA_STATE_RED_WALK_WING);
				    ani = GOOMBA_ANI_RED_JUMPING;
			}
			else if (this->state == GOOMBA_STATE_RED_WALK_WING) {
				if (redWalkingTimer.ElapsedTime() >= GOOMBA_WALKING_TIME && redWalkingTimer.IsStarted()) {
					this->SetState(GOOMBA_STATE_JUMPING_LOW);
					isOnGround = false;
				}
				ani = GOOMBA_ANI_RED_WALK_WING;
			}
		}
		else {
			switch (this->state)
			{
			case GOOMBA_STATE_JUMPING_HIGH:			
				if (this->start_Y - this->y >= GOOMBA_MAX_JUMP_HIGH_DY)
				{
					this->SetState(GOOMBA_STATE_FALLING_HIGH);
				}
				ani = GOOMBA_ANI_RED_JUMPING;
				break;
			case GOOMBA_STATE_JUMPING_LOW:
				if (this->start_Y - this->y >= GOOMBA_MAX_JUMP_LOW_DY)
				{
					this->SetState(GOOMBA_STATE_FALLING_LOW);
				}
				ani = GOOMBA_ANI_RED_JUMPING;
				break;
			case GOOMBA_STATE_RED_WALKING:
				break;
			default:
				break;
			}
		}
	}

	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject* player = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
	float mario_X, mario_Y;
	player->GetPosition(mario_X, mario_Y);

	switch (state)
	{
	case GOOMBA_STATE_DIE:
		y += GOOMBA_BBOX_YELLOW_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		this->transformTimer.Start();
		break;
	case GOOMBA_STATE_YELLOW_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		ay = GOOMBA_GRAVITY;
		break;
	case GOOMBA_STATE_FALLING_LOW:
		if (mario_X < this->x) {
			vx = -GOOMBA_FALLING_LOW_SPEED_X;
			vy = GOOMBA_FALLING_LOW_SPEED_Y;
		}
		else {
			vx = GOOMBA_FALLING_LOW_SPEED_X;
			vy = GOOMBA_FALLING_LOW_SPEED_Y;
		}
		break;
	case GOOMBA_STATE_JUMPING_LOW:
		if (mario_X < this->x) {
			vx = -GOOMBA_JUMPING_LOW_SPEED_X;
			vy = -GOOMBA_JUMPING_LOW_SPEED_Y;
		}
		else {
			vx = GOOMBA_JUMPING_LOW_SPEED_X;
			vy = -GOOMBA_JUMPING_LOW_SPEED_Y;
		}
		break;
	case GOOMBA_STATE_FALLING_HIGH:
		if (mario_X < this->x) {
			vx = -GOOMBA_FALLING_HIGH_SPEED_X;
			vy = GOOMBA_FALLING_HIGH_SPEED_Y;
		}
		else {
			vx = GOOMBA_FALLING_HIGH_SPEED_X;
			vy = GOOMBA_FALLING_HIGH_SPEED_Y;
		}
		break;
	case GOOMBA_STATE_JUMPING_HIGH:
		if (mario_X < this->x) {
			vx = -GOOMBA_JUMPING_HIGH_SPEED_X;
			vy = -GOOMBA_JUMPING_HIGH_SPEED_Y;
		}
		else {
			vx = GOOMBA_JUMPING_HIGH_SPEED_X;
			vy = -GOOMBA_JUMPING_HIGH_SPEED_Y;
		}
		break;
	case GOOMBA_STATE_RED_WALK_WING:
	{
		y += GOOMBA_BBOX_RED_UNWALK_HEIGHT - GOOMBA_BBOX_RED_WALK_HEIGHT;
		redWalkingTimer.Start();
		if (mario_X < this->x) {
			vx = -GOOMBA_WALKING_SPEED;
		}
		else {
			vx = GOOMBA_WALKING_SPEED;
		}
		ay = GOOMBA_GRAVITY;
		break;
	}
	case GOOMBA_STATE_NON_EXIST:
		vx = 0;
		vy = 0;
		break;
	}
	CGameObject::SetState(state);
}