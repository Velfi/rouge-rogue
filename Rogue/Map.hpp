#pragma once

static const int ROOM_MAX_SIZE = 12;
static const int ROOM_MIN_SIZE = 6;
static const int MAX_ROOM_MONSTERS = 3;

struct Tile {
    bool explored;
    Tile() : explored(false) {}
};

class Map
{
public:
    int width, height;
    Map(int width, int height);
    ~Map();
    bool canWalk(int x, int y) const;
    bool isWall(int y, int x) const;
    bool isInFov(int x, int y) const;
    bool isExplored(int x, int y) const;
    void addMonster(int x, int y);
    void computeFov();
    void render() const;
protected:
    Tile * tiles;
    TCODMap *map;
    friend class BspListener;

    void dig(int x1, int y1, int x2, int y2);
    void createRoom(bool first, int x1, int y1, int x2, int y2);
};

