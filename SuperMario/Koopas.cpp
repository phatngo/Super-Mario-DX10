#include "Koopas.h"
#include "Utils.h"
#include "Brick.h"
#include "QuestionBrick.h"
#include "Block.h"

CKoopas::CKoopas(int tag)
{
	if (tag == KOOPAS_TAG_RED) {
		SetState(KOOPAS_STATE_WALKING_LEFT);
		this->tag = tag;
		currentHeight = KOOPAS_BBOX_RED_HEIGHT_1;
		ax = KOOPAS_GRAVITY;
	}
}

void CKoopas::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	if (tag == KOOPAS_TAG_RED) {
		right = x + KOOPAS_BBOX_RED_WIDTH;
		if (state == KOOPAS_STATE_DIE)
			bottom = y + KOOPAS_BBOX_RED_HEIGHT_DIE;
		else {
			if (timer.IsStarted() && timer.ElapsedTime() >= 200) {
				if (currentHeight == KOOPAS_BBOX_RED_HEIGHT_1) {
					currentHeight = KOOPAS_BBOX_RED_HEIGHT_2;
				}
				else if(currentHeight == KOOPAS_BBOX_RED_HEIGHT_2){
					currentHeight = KOOPAS_BBOX_RED_HEIGHT_1;
				}
				timer.Reset();
				timer.Start();
			}
			bottom = y + currentHeight;
		}
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	if (this->tag == KOOPAS_TAG_RED) {
		UpdateRedKoopas(dt, coObjects);
	}
}

void CKoopas::UpdateRedKoopas(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	//vy += ay * dt;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);


	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		//DebugOut(L"Koopas no collied \n");
		//DebugOut(L"No collied - x: %f, y: %f \n", x, y);
		//DebugOut(L"No collied vx: %f \n", this->vx);
		//x += dx;
		//y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * PUSHBACK;
		y += min_ty * dy + ny * PUSHBACK;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			float kLeft, kTop, kRight, kBottom;
			GetBoundingBox(kLeft, kTop, kRight, kBottom);
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBlock*>(e->obj))
			{
				CBlock* block = dynamic_cast<CBlock*>(e->obj);
				float oLeft, oTop, oRight, oBottom;
				block->GetBoundingBox(oLeft, oTop, oRight, oBottom);

				if (e->ny < 0) {

					DebugOut(L"Block with x: %f, y: %f \n", oLeft, oTop);
					DebugOut(L"Collied - x: %f, y: %f \n", x, y);

					vy = 0;
					//ay = KOOPAS_GRAVITY;
					vx += ax * dt;
					DebugOut(L"vx: %f \n", vx);
				}
				if (oTop==kBottom)
				{
					DebugOut(L"X: %f \n", x);
					DebugOut(L"Y: %f \n", y);
				}
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CKoopas::Render()
{
	int ani = KOOPAS_ANI_RED_WALKING_LEFT;
	if (state == KOOPAS_STATE_DIE) {
		ani = KOOPAS_ANI_RED_DIE;
	}
	else if (vx < 0) {

		ani = KOOPAS_ANI_RED_WALKING_LEFT;
	}
	else if (vx > 0) {
		
		ani = KOOPAS_ANI_RED_WALKING_RIGHT;
	}
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	switch (state)
	{
	case KOOPAS_STATE_DIE:
		y += currentHeight - KOOPAS_BBOX_RED_HEIGHT_DIE;
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_WALKING_LEFT:
		vx = -KOOPAS_WALKING_SPEED; 
		ay =  KOOPAS_GRAVITY;
		timer.Start();
		nx = -1;
		break;
	case KOOPAS_STATE_WALKING_RIGHT:
		vx = KOOPAS_WALKING_SPEED;
		ay = KOOPAS_GRAVITY;
		timer.Start();
		nx = 1;
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}