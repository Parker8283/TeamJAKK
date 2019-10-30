//Class to model a (default 32x32p) tile in a map
//@author Cody Keilitz
//Last modified Oct 30 2019


class DungeonTile {
    private:
    bool passable;
    double worldX;
    double worldY;

    public:
    bool isPassable();
    void setPassable(bool p);

    double getWorldX();
    double getWorldY();

    void setWorldCoordCenter(double x, double y);

    DungeonTile();
    DungeonTile(bool p, double x, double y);
    bool moveOnEvent();
};