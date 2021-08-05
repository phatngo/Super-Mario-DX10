#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "QuestionBrick.h"
#include "FlashAnimationBrick.h"
#include "Map.h"
#include "Block.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "Switch.h"
#include "Goomba.h"
#include "Koopas.h"
#include "PiranhaPlant.h"
#include "FirePiranhaPlant.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
	
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 1
#define SCENE_SECTION_TILEMAP_DATA 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_QUESTION_BRICK	142
#define OBJECT_TYPE_BRICK_WITH_FLASH_ANIMATION	112
#define OBJECT_TYPE_BLOCK 4
#define OBJECT_TYPE_PIRANHA_PLANT 7
#define OBJECT_TYPE_FIRE_PIRANHA_PLANT 70
#define OBJECT_TYPE_COIN 6



#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024


void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_TILEMAP_DATA(string line)
{

	int ID, rowMap, columnMap, columnTile, rowTile, totalTiles;
	LPCWSTR path = ToLPCWSTR(line);
	ifstream f;
	f.open(path);
	f >> ID >> rowMap >> columnMap >> rowTile >> columnTile >> totalTiles;
	DebugOut(L"[INFO] _ParseSection_TILEMAP %d, %d \n", ID, rowMap);
	//Init Map Matrix
	int** TileMapData = new int* [rowMap];
	for (int i = 0; i < rowMap; i++)
	{
		TileMapData[i] = new int[columnMap];
		int j;
		for (j = 0; j < columnMap; j++) {
			f >> TileMapData[i][j];
			DebugOut(L"[INFO] _ParseSection_TILEMAP %d \n", TileMapData[i][j]);
		}
	}
	f.close();

	current_map = new CMap(ID, rowMap, columnMap, rowTile, columnTile, totalTiles);
	current_map->ExtractTileFromTileSet();
	current_map->SetTileMapData(TileMapData);
	maxCx = current_map->GetMapWidth() - CGame::GetInstance()->GetScreenWidth();
	DebugOut(L"[INFO] _ParseSection_TILEMAP_DATA done:: \n");

}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{

	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());
		
		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}


void CPlayScene::_ParseSection_OBJECTS(string line)
{
	wstring path = ToWSTR(line);

	ifstream f;
	DebugOut(L"[INFO] Start object resources from : %s \n", path.c_str());
	f.open(path.c_str());
	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);
		if (line[0] == '#') continue;

		vector<string> tokens = split(line);

		if (tokens.size() <= 3) continue;

		int object_type = atoi(tokens[0].c_str());
		float x = atof(tokens[1].c_str());
		float y = atof(tokens[2].c_str());
		int ani_set_id = atoi(tokens[3].c_str());
		
		CAnimationSets* animation_sets = CAnimationSets::GetInstance();

		CGameObject* obj = NULL;
		CGameObject* obj_of_questionBrick = NULL;
		LPANIMATION_SET ani_set_of_obj;

		switch(object_type) 
		{
		case OBJECT_TYPE_MARIO:
			if (player != NULL)
			{
				DebugOut(L"[ERROR] MARIO object was created before!\n");
				return;
			}
			obj = new CMario(x, y);
			player = (CMario*)obj;
			DebugOut(L"[INFO] Player object created!\n");
			break;
		case OBJECT_TYPE_BRICK:
			obj = new CBrick();
			DebugOut(L"[INFO] Brick created!\n");
			break;
		case OBJECT_TYPE_COIN:
			obj = new CCoin();
			DebugOut(L"[INFO] Coin created!\n");
			break;
		case OBJECT_TYPE_BLOCK:
			obj = new CBlock();
			DebugOut(L"[INFO] Block created!\n");
			break;
		case OBJECT_TYPE_GOOMBA: 
		{
			obj = new CGoomba();
			DebugOut(L"[INFO] Goomba created!\n");
			break;
		}
		case OBJECT_TYPE_KOOPAS: 
			obj = new CKoopas(); 
			DebugOut(L"[INFO] Koopas created!\n"); 
			break;
		case OBJECT_TYPE_QUESTION_BRICK:
		{
			int tag = atoi(tokens[5].c_str());
			obj = new CQuestionBrick(tag);
			DebugOut(L"[INFO] Question Brick created!\n");
			break;
		}
		case OBJECT_TYPE_BRICK_WITH_FLASH_ANIMATION:
			obj = new CFlashAnimationBrick();
			DebugOut(L"[INFO] Question Brick created!\n");
		    break;
		case OBJECT_TYPE_PIRANHA_PLANT:
			obj = new CPiranhaPlant();
			DebugOut(L"[INFO] Piranha Plant created!\n");
			break;
		case OBJECT_TYPE_FIRE_PIRANHA_PLANT: {
			int objTag = atoi(tokens[4].c_str());
			obj = new CFirePiranhaPlant(objTag);
			DebugOut(L"[INFO] Fire Piranha Plant created!\n");
			break;
		}
		default:
			obj = new CBrick();
			DebugOut(L"[INFO] Other object created!\n");
			break;
		}

		obj->SetPosition(x, y);

		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		objects.push_back(obj);

		if (obj_of_questionBrick != NULL) {
			obj_of_questionBrick->SetPosition(x, y);
			objects.push_back(obj_of_questionBrick);
		}
	}
	f.close();
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[TILEMAP DATA]") { section = SCENE_SECTION_TILEMAP_DATA; continue; }
		if (line == "[SPRITES]") { 
			section = SCENE_SECTION_SPRITES; continue; }
		if (line == "[ANIMATIONS]") { 
			section = SCENE_SECTION_ANIMATIONS; continue; }
		if (line == "[ANIMATION_SETS]") { 
			section = SCENE_SECTION_ANIMATION_SETS; continue; }
		if (line == "[OBJECTS]") { 
			section = SCENE_SECTION_OBJECTS; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
			case SCENE_SECTION_TILEMAP_DATA: _ParseSection_TILEMAP_DATA(line); break;
			case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
			case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	player->Update(dt, &coObjects, &objects);
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CCamera::GetInstance()->SetCameraPosition(maxCx,cx);
}

void CPlayScene::Render()
{
	if (player == NULL) return;
	current_map->Render();
	player->Render();
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->Render();
		if (dynamic_cast<CGoomba*>(objects[i])&&objects[i]->GetState()==GOOMBA_STATE_DIE) {
			objects.erase(objects.begin() + i);
		}
		else if (dynamic_cast<CCoin*>(objects[i]) && objects[i]->GetState() == COIN_STATE_NON_EXIST) {
			objects.erase(objects.begin() + i);
		}
		
	}
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

vector<LPGAMEOBJECT> CPlayScene::GetSceneObjects()
{
	return this->objects;
}

void CPlayScene::SetSceneObjects(vector<LPGAMEOBJECT> newObjects)
{
	this->objects = newObjects;
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMario *mario = ((CPlayScene*)scence)->GetPlayer();
	float speedX, speedY;
	mario->GetSpeed(speedX, speedY);
	switch (KeyCode)
	{
	case DIK_S:
		if (mario->GetState() != MARIO_STATE_JUMP) {
			mario->SetState(MARIO_STATE_JUMP);
		}
		break;
	case DIK_A: 
		mario->Reset();
		break;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CMario *mario = ((CPlayScene*)scence)->GetPlayer();

	// disable control key when Mario die 
	if (mario->GetState() == MARIO_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
		mario->SetState(MARIO_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		mario->SetState(MARIO_STATE_WALKING_LEFT);
	else
		mario->SetState(MARIO_STATE_IDLE);
}

