//Class to model a dungeon level. Includes methods for fixed testing and procedural generation
//@author: Cody Keilitz
//Last Changed Oct 25 2019

#include "DungeonMap.h"
#include <string>

#define DEFAULTTEXTURE "default"

DungeonMap::DungeonMap(){
  tiles=NULL;
  textureType="";
  xSize=0;
  ySize=0;
}

DungeonMap::DungeonMap(DungeonTile** map, int x, int y){
  tiles=map;
  textureType=DEFAULTTEXTURE;
  
  xSize=x;
  ySize=y;
}

DungeonMap::~DungeonMap(){
  //TODO: deconstruct when I have some idea wtf I'm doing
}

std::string DungeonMap::toFile(std::string filepath){
  //TODO
}

DungeonTile** DungeonMap::testRoom(){
  DungeonTile testRoom[10][10];

  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      if(i==0 || j==0 || i==9 || j==9){
        testRoom[i][j] = *(new DungeonTile(false, j+0.5,i+0.5));
      }
    }
  }
}

DungeonTile** DungeonMap::generateMap(int rows, int cols){
  //TODO
}

void DungeonMap::setMap(DungeonTile** map){
  tiles = map;
}

DungeonTile** DungeonMap::getMap(){
  return tiles;
}

void DungeonMap::setTextureType(std::string path){
  textureType=path;
}

std::string DungeonMap::getTextureType(){
  return textureType;
}

int DungeonMap::getRows(){
  return xSize;
}

void DungeonMap::setRows(int rows){
  xSize = rows;
}

int DungeonMap::getCols(){
  return ySize;
}

void DungeonMap::setCols(int cols){
  ySize = cols;
}

std::vector<DungeonTile> DungeonMap::getImpassableList(){

  std::vector<DungeonTile> ret;

  for(int i = 0; i < xSize ; i++){
    for(int j = 0; j < ySize ; j++) {
      if(!tiles[i][j].isPassable){
        ret.insert(ret.end(),tiles[i][j]);
      }
    }
  }
}

