#include "FirePiranhaPlant.h"
#include "Game.h"
#include "PlayScence.h"
#include "FireBullet.h"
#include "Utils.h"

CFirePiranhaPlant::CFirePiranhaPlant(int objTag)
{
	this->SetState(FIRE_PIRANHA_STATE_UP);
	if (objTag == TAG_FIRE_PIRANHA_RED)
		this->tag = TAG_FIRE_PIRANHA_RED;
	else
		this->tag = TAG_FIRE_PIRANHA_GREEN;
}

void CFirePiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FIRE_PIRANHA_BBOX_WIDTH;
	bottom = y + FIRE_PIRANHA_BBOX_HEIGHT;
}

void CFirePiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	y += dy;
}

void CFirePiranhaPlant::Render()
{
	CGameObject* player = CGame::GetInstance()->GetCurrentScene()->GetPlayer();

	if (player == NULL)
		return;
	float mario_X, mario_Y;
	player->GetPosition(mario_X, mario_Y);
	switch (state)
	{
	case FIRE_PIRANHA_STATE_UP:
	{
		if (mario_X < this->x) {

			if (mario_Y <= this->y) {
				this->ani = FIRE_PIRANHA_ANI_UP_LEFT;
			}
			else {
				this->ani = FIRE_PIRANHA_ANI_DOWN_LEFT;
			}

		}
		else {

			if (mario_Y <= this->y) {
				this->ani = FIRE_PIRANHA_ANI_UP_RIGHT;
			}
			else {
				this->ani = FIRE_PIRANHA_ANI_DOWN_RIGHT;
			}
		}

		switch (this->tag)
		{
		case TAG_FIRE_PIRANHA_RED:
			if (start_Y - y >= RED_FIRE_PIRANHA_HIGHEST_DY) {
				this->SetState(FIRE_PIRANHA_STATE_SHOOT);
			}
			break;
		case TAG_FIRE_PIRANHA_GREEN:
			if (start_Y - y >= GREEN_FIRE_PIRANHA_HIGHEST_DY) {
				this->SetState(FIRE_PIRANHA_STATE_SHOOT);
			}
			break;
		default:
			break;
		}
		break;
	}
	case FIRE_PIRANHA_STATE_SHOOT:
		this->SetState(FIRE_PIRANHA_STATE_DOWN);
		break;
	case FIRE_PIRANHA_STATE_DOWN:
		
		if (start_Y - y <= 0) {
			this->SetState(FIRE_PIRANHA_STATE_UP);
		}
		break;
	default:
		break;
	}
	animation_set->at(this->ani)->Render(x, y);
}

void CFirePiranhaPlant::SetState(int state)
{
	switch (state) {
	case FIRE_PIRANHA_STATE_UP:
		vy = -FIRE_PIRANHA_UP_SPEED;
		break;
	case FIRE_PIRANHA_STATE_DOWN:
		vy = FIRE_PIRANHA_UP_SPEED;
		break;
	case FIRE_PIRANHA_STATE_SHOOT:
		vy = 0;
		CreateFireBullet();
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}

void CFirePiranhaPlant::CreateFireBullet() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET tmp_ani_set = animation_sets->Get(FIRE_BULLET_ANI_SET_ID);
	CFireBullet* bullet = new CFireBullet(this->x, this->y, this->ani);
	bullet->SetAnimationSet(tmp_ani_set);
	scene->AddObjects(bullet);
}


