//Class to model a dungeon level. Includes method for fixed testing and procedural generation
//@author Cody Keilitz
//Last Changed Oct 25 2019
#ifndef DUNGEON_MAP_H
#define DUNGEON_MAP_H

#include <stdlib.h>
#include <string>
#include "DungeonTile.h"
#include <vector>
#include <glm/glm.hpp>
#include <list>

class DungeonMap{
private:
       //core structure of the map, MxN sizes independently variable
  std::string textureType; //string points to the folder in which the textures for the individual tiles are stored
  
  int xSize;               //number of internal rows
  int ySize;               //number of internal columns
  glm::vec2 tileDim;

  std::vector<DungeonTile> impassableList;
  std::vector<DungeonTile> passableList;

public:
	DungeonTile** tiles;
  DungeonMap();
  DungeonMap(DungeonTile** map, int x, int y);   //construct using existing matrix, x&y size set automatically
  ~DungeonMap();
  std::string toFile(std::string filepath);      //export object to a text representation, see common/documentation/DungeonMap.toFile.txt
  DungeonTile** generateMap(int rows, int cols); //use default procedural generation

  //setters & getters
  void setMap(DungeonTile** map);
  DungeonTile** getMap();

  void setTextureType(std::string path);
  std::string getTextureType();

  int getRows();
  void setRows(int rows);

  int getCols();
  void setCols(int cols);

  std::vector<DungeonTile> getImpassableList();
  std::vector<DungeonTile> getPassableList();
  std::vector<DungeonTile> getRoomFloor();

  glm::vec2 getTileDim(void);
};

DungeonTile* GenerateTestRoom(int, int); //set map to predefined 10x10 room
#endif
