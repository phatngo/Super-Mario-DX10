#include "HUD.h"
#include "Utils.h"
#include "Game.h"
#include "HUD.h"
#include "Camera.h"



HUD::HUD() {

}
void HUD::Render() {
	animation_set->at(0)->Render(CCamera::GetInstance()->GetCameraX(),this->start_Y);
}


