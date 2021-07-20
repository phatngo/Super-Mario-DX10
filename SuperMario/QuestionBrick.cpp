#include "QuestionBrick.h"

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
}

void CQuestionBrick::Render() {
	int ani = QUESTION_BRICK_ANI_SPINNING;
	if (currentState == QUESTION_BRICK_STATE_STOP) {
		ani = QUESTION_BRICK_ANI_STOP;
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
	SetState(QUESTION_BRICK_STATE_SPINNING);
}

void CQuestionBrick::SetState(int state) {
	if (state == QUESTION_BRICK_STATE_SPINNING) {
		currentState = QUESTION_BRICK_STATE_SPINNING;
	}
	else if (state == QUESTION_BRICK_STATE_STOP) {
		currentState = QUESTION_BRICK_STATE_STOP;
	}
}

