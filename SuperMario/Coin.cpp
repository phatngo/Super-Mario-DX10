#include "Coin.h"
CCoin::CCoin()
{
	
}

void CCoin::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Coin can interact with the world and to each of them too!
	// 

	
}

void CCoin::Render()
{

}

void CCoin::SetState(int state)
{
	CGameObject::SetState(state);
	
}
