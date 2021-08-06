#include "QuestionBrick.h"
#include "Leaf.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Switch.h"
#include "Game.h"
#include "PlayScence.h"

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	if (state == QUESTION_BRICK_STATE_STOP)
		y = start_Y;
	else
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

CQuestionBrick::CQuestionBrick(int tag) {
	SetState(QUESTION_BRICK_STATE_IDLE);
	this->tag = tag;
}

void CQuestionBrick::SetState(int state) {
	switch (state) {
	case QUESTION_BRICK_STATE_JUMPING:
		vy = -QUESTION_BRICK_JUMP_SPEED;
		CreateObject();
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

void CQuestionBrick::CreateObject() {
	switch (tag)
	{
	case COIN_TAG: 
		CreateCoin();
		break;
	case MUSHROOM_TAG:
		CreateMushroom();
		break;
	case LEAF_TAG:
		CreateLeaf();
		break;
	default:
		break;
	}
}

void CQuestionBrick::CreateCoin() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET tmp_ani_set = animation_sets->Get(COIN_ANI_SET_ID);
	CCoin* coin = new CCoin(TAG_COIN_IN_BRICK);
	coin->SetPosition(this->x, this->y);
	coin->SetAnimationSet(tmp_ani_set);
	scene->AddObjects(coin);
}

void CQuestionBrick::CreateMushroom() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET tmp_ani_set = animation_sets->Get(MUSHROOM_ANI_SET_ID);
	CMushroom* mushroom = new CMushroom();
	mushroom->SetPosition(this->x, this->y);
	mushroom->SetAnimationSet(tmp_ani_set);
	scene->AddObjects(mushroom);
}

void CQuestionBrick::CreateLeaf() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET tmp_ani_set = animation_sets->Get(LEAF_ANI_SET_ID);
	CLeaf* leaf = new CLeaf();
	leaf->SetPosition(this->x, this->y);
	leaf->SetAnimationSet(tmp_ani_set);
	scene->AddObjects(leaf);
}



