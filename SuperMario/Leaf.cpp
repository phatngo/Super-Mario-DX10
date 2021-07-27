#include "Leaf.h"
CLeaf::CLeaf()
{

}

void CLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Leaf can interact with the world and to each of them too!
	// 


}

void CLeaf::Render()
{

}

void CLeaf::SetState(int state)
{
	CGameObject::SetState(state);

}
