#include "QuestionBrick.h"
#include "Leaf.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Switch.h"

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	y += dy;
}

void CQuestionBrick::Render() {
	int ani = -1;
	switch (this->state)
	{
	case QUESTION_BRICK_STATE_JUMPING:
		ani = QUESTION_BRICK_ANI_STOP;
		this->SetState(QUESTION_BRICK_STATE_FALLING);
		break;
	case QUESTION_BRICK_STATE_FALLING:
		ani = QUESTION_BRICK_ANI_STOP;
		this->SetState(QUESTION_BRICK_STATE_STOP);
		break;
	case QUESTION_BRICK_STATE_IDLE:
		ani = QUESTION_BRICK_ANI_SPINNING;
		break;
	case QUESTION_BRICK_STATE_STOP:
		ani = QUESTION_BRICK_ANI_STOP;
		break;
	default:
		break;
	}
	animation_set->at(ani)->Render(x, y);
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

CQuestionBrick::CQuestionBrick() {
	SetState(QUESTION_BRICK_STATE_IDLE);
}

void CQuestionBrick::SetState(int state) {
	switch (state) {
	case QUESTION_BRICK_STATE_JUMPING:
		vy = -QUESTION_BRICK_JUMP_SPEED;
		break;
	case QUESTION_BRICK_STATE_FALLING:
		vy = QUESTION_BRICK_JUMP_SPEED;
		break;
	case QUESTION_BRICK_STATE_IDLE:
		vy = 0;
		break;
	case QUESTION_BRICK_STATE_STOP:
		vy = 0;
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}

void CQuestionBrick::SetTag(float tag, CGameObject* obj) {
	this->tag_0 = tag;
	switch (tag_0)
	{
	case COIN_TAG:
		obj = new CCoin();
		break;
	case MUSHROOM_TAG:
		obj = new CMushroom();
		break;
	case LEAF_TAG:
		obj = new CLeaf();
		break;
	case SWITCH_TAG:
		obj = new CSwitch();
		break;
	default:
		break;
	}
}

