#include "Mushroom.h"
CMushroom::CMushroom()
{

}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Mushroom can interact with the world and to each of them too!
	// 


}

void CMushroom::Render()
{

}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);

}
