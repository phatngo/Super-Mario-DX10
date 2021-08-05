#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Koopas.h"
#include "Portal.h"
#include "QuestionBrick.h"
#include "Block.h"
#include "Coin.h"
#include "Brick.h"
#include "PiranhaPlant.h"
#include "FirePiranhaPlant.h"
#include "FireBullet.h"
#include "Mushroom.h"

CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_SMALL;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);

	start_x = x; 
	start_y = y; 
	this->x = x; 
	this->y = y; 
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects, vector<LPGAMEOBJECT> *objects)
{
	
	// Calculate dx, dy 
	CGameObject::Update(dt);

	
	// Simple fall down
	vy += MARIO_GRAVITY*dt;


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state!=MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size()==0)
	{		
		x += dx; 
		y += dy;

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0; 
		float rdy = 0;

		float y0 = y;
		float x0 = x;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		//DebugOut(L"[INFO] e1 is goomba: %d \n", dynamic_cast<CGoomba*>(e1->obj) ? 1 : 0);
		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		if (rdx != 0 && rdx!=dx)
			x += nx*abs(rdx); 
		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty*dy + ny*0.4f;
		

		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{

				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState()!= GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable==0)
					{
						if (goomba->GetState()!=GOOMBA_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else 
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			} 
			else if (dynamic_cast<CKoopas*>(e->obj)) // if e->obj is Koopas
			{
				CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (koopas->GetState() != KOOPAS_STATE_DIE)
					{
						koopas->SetState(KOOPAS_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					//If mario is touchable
					if (untouchable == 0)
					{
						//If koopas is not dead
						if (koopas->GetState() != KOOPAS_STATE_DIE)
						{
							//If mario is not in the big size
							if (level > MARIO_LEVEL_SMALL)
							{
								//Makes mario become small
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else
								//Makes mario die
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			}
			else if (dynamic_cast<CBlock*>(e->obj)) 
			{
				CBlock* block = dynamic_cast<CBlock*>(e->obj);
				if (e->ny > 0)
				{
					//y -= (min_ty * dy + ny * 0.4f);
					float l, t, r, b;
					block->GetBoundingBox(l, t, r, b);

					if((y+dy)<b && (y+dy)<t){
						y += dy;
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
			}
			else if (dynamic_cast<CQuestionBrick*>(e->obj)) // if e->obj is Quesion Brick
			{
				CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e->obj);
				//Mario stays under question brick
				if (e->ny > 0)
				{
					if(e->obj->GetState()!= QUESTION_BRICK_STATE_STOP)
						questionBrick->SetState(QUESTION_BRICK_STATE_JUMPING);	
				}
			}
			else if (dynamic_cast<CCoin*>(e->obj)) 
			{
				CCoin* coin = dynamic_cast<CCoin*>(e->obj);
				float l, t, r, b;
				this->GetBoundingBox(l, t, r, b);
				float dy1 = y0 - y;
				if (dy1 > (-MARIO_JUMP_SPEED_Y * dt)) {
					DebugOut(L"[INFO] noCollisionDy: %f \n", noCollisionDy);
					float dy2 = (-MARIO_JUMP_SPEED_Y * dt) + dy1;
					float vy2 = dy2 / dt;
					vy = vy2;
				}
				coin->SetState(COIN_STATE_NON_EXIST);
			}
			else if (dynamic_cast<CPiranhaPlant*>(e->obj)
			|| dynamic_cast<CFirePiranhaPlant*>(e->obj)
			|| dynamic_cast<CFireBullet*>(e->obj)) {
				if (untouchable == 0)
				{
						//If mario is not in the big size
						if (level > MARIO_LEVEL_SMALL)
						{
							//Makes mario become small
							level = MARIO_LEVEL_SMALL;
							StartUntouchable();
						}
						else
							//Makes mario die
							SetState(MARIO_STATE_DIE);	
				}
            }
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMario::Render()
{
	int ani = -1;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
	if (level == MARIO_LEVEL_BIG)
	{
		if (vx == 0)
		{
			if (nx>0) ani = MARIO_ANI_BIG_IDLE_RIGHT;
			else ani = MARIO_ANI_BIG_IDLE_LEFT;
		}
		else if (vx > 0) 
			ani = MARIO_ANI_BIG_WALKING_RIGHT; 
		else ani = MARIO_ANI_BIG_WALKING_LEFT;
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		if (vx == 0)
		{
			if (nx>0) ani = MARIO_ANI_SMALL_IDLE_RIGHT;
			else ani = MARIO_ANI_SMALL_IDLE_LEFT;
		}
		else if (vx > 0)
			ani = MARIO_ANI_SMALL_WALKING_RIGHT;
		else ani = MARIO_ANI_SMALL_WALKING_LEFT;
	}

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);

	RenderBoundingBox();
}

void CMario::SetState(int state)
{
	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT: 
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		vy = -MARIO_JUMP_SPEED_Y;
		break; 
	case MARIO_STATE_IDLE: 
		vx = 0;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	}
	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 

	if (level==MARIO_LEVEL_BIG)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_SMALL);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

