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

  std::vector<DungeonTile> ret;

  for (int i = 0; i < xSize ; i++) {
    for (int j = 0; j < ySize ; j++) {
      if (!tiles[i][j].isPassable()) {
        ret.insert(ret.end(), tiles[i][j]);
      }
    }
  }

  return ret;
}

DungeonTile* GenerateTestRoom(int width, int height) {
  DungeonTile* testRoom = new DungeonTile[width * height];

  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      int index = i + j * width;
      if (i == 0 || j == 0 || i == (width - 1) || j == (height - 1)) {
        testRoom[index] = DungeonTile(false, j*2 + 0.5f, 10 - i*2 + 0.5f);
      } else {
        testRoom[index] = DungeonTile(true , j*2 + 0.5f, 10 - i*2 + 0.5f);
      }
    }
  }

  return testRoom;
}

glm::vec2 DungeonMap::getTileDim()
{
	return tileDim;
}