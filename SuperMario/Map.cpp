#include "Map.h"
#include "Utils.h"
#include "Textures.h"
#include "Game.h"

CMap::CMap(int TileSetID, int TotalRowsOfMap, int TotalColumnsOfMap, int TotalRowsOfTileSet, int  TotalColumnsOfTileSet, int TotalTiles)
{
	//Tileset is the image
	TileSet = CTextures::GetInstance()->Get(TileSetID);
	this->TotalRowsOfMap = TotalRowsOfMap;
	this->TotalColumnsOfMap = TotalColumnsOfMap;
	this->TotalRowsOfTileSet = TotalRowsOfTileSet;
	this->TotalColumnsOfTileSet = TotalColumnsOfTileSet;
	this->TotalTiles = TotalTiles;
	TileMap = NULL;
	//DebugOut(L"CMap contructor");
}

CMap::~CMap()
{
}

void CMap::Render()
{
	//Camera* cam = Camera::GetInstance();
	float mx, my;
	//mx = cam->GetCameraPosition().x;
	//my = cam->GetCameraPosition().y;
	mx = CGame::GetInstance()->GetCamPosX();
	my = CGame::GetInstance()->GetCamPosY();
	int FirstColumn = (int)floor(mx / TILE_WIDTH);
	int LastColumn = (int)ceil((mx + CGame::GetInstance()->GetScreenWidth()) / TILE_WIDTH);
	DebugOut(L"[INFO] Total column of maps: \n", TotalColumnsOfMap);
	if (LastColumn >= TotalColumnsOfMap)
		LastColumn = TotalColumnsOfMap - 1;

	int d = 0;
	for (int CurrentRow = 0; CurrentRow < TotalRowsOfMap; CurrentRow++)
		for (int CurrentColumn = FirstColumn; CurrentColumn <= LastColumn; CurrentColumn++)
		{
			int index = TileMap[CurrentRow][CurrentColumn] - 1;
			if (index < TotalTiles)
				Tiles.at(index)->Draw((float)(CurrentColumn * TILE_WIDTH), (float)(CurrentRow * TILE_HEIGHT/*- HUD_HEIGHT*/));
		}
}
void CMap::SetTileMapData(int** TileMapData)
{
	TileMap = TileMapData;
	DebugOut(L"CMap SetTileMapData");

}


void CMap::ExtractTileFromTileSet()
{
	for (int TileNum = 0; TileNum < TotalTiles; TileNum++)
	{
		int left = TileNum % TotalColumnsOfTileSet * TILE_WIDTH;
		int top = TileNum / TotalColumnsOfTileSet * TILE_HEIGHT;
		int right = left + TILE_WIDTH;
		int bottom = top + TILE_HEIGHT;
		//DebugOut(L"[DETAILS]	left %d top %d right %d bottom %d\n", left, top, right, bottom);
		LPSPRITE NewTile = new CSprite(TileNum, left, top, right, bottom, TileSet); // get tile from tileset
		this->Tiles.push_back(NewTile);
	}
	//DebugOut(L"CMap ExtractTileFromTileSet");

}

int CMap::GetMapWidth()
{
	//DebugOut(L"CMap GetMapWidth");

	return TotalColumnsOfMap * TILE_WIDTH;
}

int CMap::GetMapHeight()
{
	//DebugOut(L"CMap GetMapHeight");

	return TotalRowsOfMap * TILE_HEIGHT;
}
