#ifndef DUNGEONTILE_H
#define DUNGEONTILE_H


//Class to model a (default 32x32p) tile in a map
//@author Cody Keilitz
//Last modified Oct 30 2019


class DungeonTile {
    private:
    bool passable;
    
    float worldX;
    float worldY;

    public:

    DungeonTile(void) : passable(false), worldX(0), worldY(0) { }
    DungeonTile(bool p, float x, float y);
    
    void Draw(void);
    void setPassable(bool p);
    void setWorldCoordCenter(float x, float y);
    
    bool isPassable();
    bool moveOnEvent();

    float getWorldX();
    float getWorldY();


};
#endif