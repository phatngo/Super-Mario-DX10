#include "HUD.h"
#include "Utils.h"
#include "Game.h"
#include "Camera.h"
#include "Font.h"
#include "Mario.h"



HUD::HUD() {

}

void HUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	//Mario's point update
	for (int i = 0; i < POINT_DIGIT_NUMBER; i++) {
		Font* font;
		if (i == 0) {
			font = new Font(
				CCamera::GetInstance()->GetCameraX() + FIRST_POINT_DIGIT_POSITION_FROM_HUD_X, 
				this->start_Y + POINT_DIGIT_POSITION_FROM_HUD_Y
			);
		}
		else {
			float last_font_X, last_font_Y;
			pointDigits[i-1]->GetPosition(last_font_X, last_font_Y);
			font = new Font(last_font_X + FONT_WIDTH, this->start_Y + POINT_DIGIT_POSITION_FROM_HUD_Y);
		}
		pointDigits.push_back(font);
	}
	CMario* player = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
	int totalPoint = player->GetPoint();
	for (int i = POINT_DIGIT_NUMBER - 1 ; i >= 0; i--) {
		int digit = totalPoint % 10;
		totalPoint = totalPoint / 10;
		switch (digit)
		{
		case DIGIT_0:
			pointDigits[i]->SetAni(ANI_0);
			break;
		case DIGIT_1:
			pointDigits[i]->SetAni(ANI_1);
			break;
		case DIGIT_2:
			pointDigits[i]->SetAni(ANI_2);
			break;
		case DIGIT_3:
			pointDigits[i]->SetAni(ANI_3);
			break;
		case DIGIT_4:
			pointDigits[i]->SetAni(ANI_4);
			break;
		case DIGIT_5:
			pointDigits[i]->SetAni(ANI_5);
			break;
		case DIGIT_6:
			pointDigits[i]->SetAni(ANI_6);
			break;
		case DIGIT_7:
			pointDigits[i]->SetAni(ANI_7);
			break;
		case DIGIT_8:
			pointDigits[i]->SetAni(ANI_8);
			break;
		case DIGIT_9:
			pointDigits[i]->SetAni(ANI_9);
			break;
		default:
			break;
		}
	}
}

void HUD::Render() {
	animation_set->at(0)->Render(this->x+CCamera::GetInstance()->GetCameraX(),this->start_Y);
	for (int i = 0; i < POINT_DIGIT_NUMBER; i++) {
		pointDigits[i]->Render();
	}
}


