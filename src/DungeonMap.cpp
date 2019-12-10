//Class to model a dungeon level. Includes methods for fixed testing and procedural generation
//@author: Cody Keilitz
//Last Changed Oct 25 2019

#include "DungeonMap.h"
#include <string>

#define DEFAULTTEXTURE "default"


DungeonMap::DungeonMap() {
  tiles = NULL;
  textureType = "";
  xSize = 0;
  ySize = 0;

  tileDim = glm::vec2(2, 2);
}

DungeonMap::DungeonMap(DungeonTile** map, int x, int y) {
  tiles = map;
  textureType = DEFAULTTEXTURE;
  xSize = x;
  ySize = y;

  for (int i = 0; i < xSize * ySize; i++) {
		if (!tiles[0][i].isPassable()) {
			impassableList.push_back(tiles[0][i]);
		} else {
			passableList.push_back(tiles[0][i]);
		}
  }

}

DungeonMap::~DungeonMap() {
  //TODO: deconstruct when I have some idea wtf I'm doing
}

//std::string DungeonMap::toFile(std::string filepath) {
//TODO

//return;
//}

//DungeonTile** DungeonMap::generateMap(int rows, int cols) {
//TODO
//}

void DungeonMap::setMap(DungeonTile** map) {
  tiles = map;
}

DungeonTile** DungeonMap::getMap() {
  return tiles;
}

void DungeonMap::setTextureType(std::string path) {
  textureType = path;
}

std::string DungeonMap::getTextureType() {
  return textureType;
}

int DungeonMap::getRows() {
  return xSize;
}

void DungeonMap::setRows(int rows) {
  xSize = rows;
}

int DungeonMap::getCols() {
  return ySize;
}

void DungeonMap::setCols(int cols) {
  ySize = cols;
}

std::vector<DungeonTile> DungeonMap::getImpassableList() {
	return impassableList;
}

std::vector<DungeonTile> DungeonMap::getRoomFloor() {
	return getPassableList();
}

std::vector<DungeonTile> DungeonMap::getPassableList() {
	return passableList;
}

DungeonTile* GenerateTestRoom(int width, int height) {
  DungeonTile* testRoom = new DungeonTile[width * height];
  float lastx;
  float lasty;

  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      int index = i + j * width;
      if (i == 0 || j == 0 || i == (width - 1) || j == (height - 1)) {
        testRoom[index] = DungeonTile(false, j*2 + 1.0f, (height - i*2) + 1.0f);
      } else {
        testRoom[index] = DungeonTile(true , j*2 + 1.0f, (height - i*2) + 1.0f);
      }
	  lastx = j * 2 + 1.0f;
	  lasty = height - i * 2 + 1.0f;
    }
  }
  return testRoom;
}

DungeonTile* Doomsday() {
	int width = 20;
	int height = 20;
	DungeonTile* testRoom = new DungeonTile[width * height];
	float lastx;
	float lasty;

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			int index = i + j * width;
			if (i == 0 || j == 0 || i == (width - 1) || j == (height - 1)) {
				testRoom[index] = DungeonTile(false, j * 2 + 1.0f, (height - i * 2) + 1.0f);
			}
			else if ( (i == 6 && j ==6) || (i == 6 && j == 5) || (i == 5 && j == 6) || (i == 5 && j == 5) ||
				(i == 6 && j == 14) || (i == 6 && j == 13) || (i == 5 && j == 14) || (i == 5 && j == 13) || 
				(i == 14 && j == 6) || (i == 14 && j == 5) || (i == 13 && j == 6) || (i == 13 && j == 5) || 
				(i == 14 && j == 14) || (i == 14 && j == 13) || (i == 13 && j == 14) || (i == 13 && j == 13) ) {
				testRoom[index] = DungeonTile(false, j * 2 + 1.0f, (height - i * 2) + 1.0f);
			}
			else {
				testRoom[index] = DungeonTile(true, j * 2 + 1.0f, (height - i * 2) + 1.0f);
			}
			lastx = j * 2 + 1.0f;
			lasty = height - i * 2 + 1.0f;
		}
	}
	return testRoom;
}

glm::vec2 DungeonMap::getTileDim()
{
	return tileDim;
}