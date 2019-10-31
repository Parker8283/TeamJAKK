//Class to model a (default 32x32p) tile in a map
//@author Cody Keilitz
//Last modified Oct 30 2019

#include <DungeonTile.h>

bool DungeonTile::isPassable(){
    return passable;
}

void DungeonTile::setPassable(bool p){
        passable = p;
}

double DungeonTile::getWorldX(){
    return worldX;
}
double DungeonTile::getWorldY(){
    return worldY;
}
void DungeonTile::setWorldCoordCenter(double x, double y){
    worldX=x;
    worldY=y;
}
DungeonTile::DungeonTile(bool p, double x, double y){
    passable=p;
    worldX=x;
    worldY=y;
}
bool DungeonTile::moveOnEvent(){
    return false;
}