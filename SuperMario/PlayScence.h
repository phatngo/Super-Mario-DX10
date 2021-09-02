#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Map.h"
#include "Camera.h"

class CPlayScene: public CScene
{
protected: 
	CMario *player;					// A play scene has to have player, right? 
	vector<LPGAMEOBJECT> objects;
	CMap* current_map = NULL;
	int maxCx; //maximum x coordinate that the camera can reach

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_TILEMAP_DATA(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	

	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual vector<LPGAMEOBJECT> GetSceneObjects();
	virtual void  SetSceneObjects(vector<LPGAMEOBJECT> objects);
	void AddObjects(CGameObject* gameObj) { this->objects.insert(this->objects.end()-2, gameObj);}

	virtual CMario * GetPlayer() { return player; } 

	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

