#include "FlashAnimationBrick.h"
#include "Game.h"
#include "PlayScence.h"
#include "Piece.h"
#include "FireBullet.h"

void CFlashAnimationBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
}

void CFlashAnimationBrick::Render() {
	if (this->state == FLASH_BRICK_STATE_FLASHING) {
		animation_set->at(FLASH_BRICK_ANI_FLASHING)->Render(x, y);
		RenderBoundingBox();
	}
}

CFlashAnimationBrick::CFlashAnimationBrick() {
	SetState(FLASH_BRICK_STATE_FLASHING);
}

void CFlashAnimationBrick::SetState(int state) {
	switch (state)
	{
	case FLASH_BRICK_STATE_FLASHING:
		break;
	case FLASH_BRICK_STATE_NON_EXIST:
		CreatePieces();
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}

void CFlashAnimationBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

void CFlashAnimationBrick::CreatePieces() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET tmp_ani_set = animation_sets->Get(PIECE_ANI_SET_ID);

	CPiece* piece_1 = new CPiece(PIECE_LEFT, PIECE_UP);
	piece_1->SetPosition(x, y);
	piece_1->SetAnimationSet(tmp_ani_set);
	scene->AddObjects(piece_1);

	CPiece* piece_2 = new CPiece(PIECE_LEFT, PIECE_DOWN);
	piece_2->SetPosition(x, y + PIECE_BBOX_HEIGHT);
	piece_2->SetAnimationSet(tmp_ani_set);
	scene->AddObjects(piece_2);

	CPiece* piece_3 = new CPiece(PIECE_RIGHT, PIECE_UP);
	piece_3->SetPosition(x+PIECE_BBOX_WIDTH, y);
	piece_3->SetAnimationSet(tmp_ani_set);
	scene->AddObjects(piece_3);

	CPiece* piece_4 = new CPiece(PIECE_RIGHT, PIECE_DOWN);
	piece_4->SetPosition(x + PIECE_BBOX_WIDTH, y + PIECE_BBOX_HEIGHT);
	piece_4->SetAnimationSet(tmp_ani_set);
	scene->AddObjects(piece_4);
}

