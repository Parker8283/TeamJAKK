//Class to model a dungeon level. Includes method for fixed testing and procedural generation
//@author Cody Keilitz
//Last Changed Oct 25 2019
#include <stdlib.h>
#include <string>
#include "DungeonTile.h"
#include <vector>

class DungeonMap{
private:
  DungeonTile::DungeonTile** tiles;    //core structure of the map, MxN sizes independently variable
  std::string textureType;       //string points to the folder in which the textures for the individual tiles are stored
  int xSize;                //number of internal rows
  int ySize;                //number of internal columns

public:
  DungeonMap();
  DungeonMap(DungeonTile::DungeonTile** map, int x, int y);    //construct using existing matrix, x&y size set automatically
  ~DungeonMap();
  std::string toFile(std::string filepath);                  //export object to a text representation, see common/documentation/DungeonMap.toFile.txt
  DungeonTile::DungeonTile** testRoom();                         //set map to predefined 10x10 room
  DungeonTile::DungeonTile** generateMap(int rows, int cols);                      //use default procedural generation

  //setters & getters
  void setMap(DungeonTile::DungeonTile** map);
  DungeonTile** getMap();

  void setTextureType(std::string path);
  std::string getTextureType();

  int getRows();
  void setRows(int rows);

  int getCols();
  void setCols(int cols);

  std::vector<DungeonTile> getImpassableList();


};
