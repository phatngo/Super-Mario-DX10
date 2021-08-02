#include "GameObject.h"

#define PIRANHA_STATE_UP_LEFT 100
#define PIRANHA_STATE_UP_RIGHT 200
#define PIRANHA_STATE_DOWN_LEFT 300
#define PIRANHA_STATE_DOWN_RIGHT 400

#define PIRANHA_STATE_UP 101
#define PIRANHA_STATE_DOWN 301


#define PIRANHA_ANI_A 0
#define PIRANHA_ANI_B 1

#define PIRANHA_BBOX_WIDTH  16
#define PIRANHA_BBOX_HEIGHT 24
#define PIRANHA_UP_SPEED 0.01f
class CPiranhaPlant : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CPiranhaPlant();
	virtual void SetState(int state);
};