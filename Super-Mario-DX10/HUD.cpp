#include "HUD.h"
#include "Utils.h"
#include "Game.h"
#include "HUD.h"
#include "Camera.h"



HUD::HUD() {

}
void HUD::Render() {
	animation_set->at(0)->Render(this->x+CGame::GetInstance()->GetCamPosX(),this->start_Y);
}


