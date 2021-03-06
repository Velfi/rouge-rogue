#include "include/libtcod.hpp"
#include "Map.hpp"
#include "Engine.hpp"
#include "BspListener.hpp"

Map::Map(int width, int height) : width(width), height(height) {
    tiles = new Tile[width * height];
    map = new TCODMap(width, height);
    TCODBsp bsp(0, 0, width, height);
    bsp.splitRecursive(NULL, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);
    BspListener listener(*this);
    bsp.traverseInvertedLevelOrder(&listener, NULL);
}

Map::~Map() {
    delete[] tiles;
    delete map;
}

bool Map::canWalk(int x, int y) const {
    if (isWall(x, y)) {
        return false;
    }
    for (Actor **iterator = engine.actors.begin();
        iterator != engine.actors.end(); iterator++) {
        Actor *actor = *iterator;
        if (actor->x == x && actor->y == y) {
            return false;
        }
    }
    return true;
}

bool Map::isWall(int x, int y) const {
    return !map->isWalkable(x, y);
}

bool Map::isExplored(int x, int y) const {
    return tiles[x + y * width].explored;
}

bool Map::isInFov(int x, int y) const {
    if (map->isInFov(x, y)) {
        tiles[x + y * width].explored = true;
        return true;
    }
    return false;
}

void Map::computeFov() {
    map->computeFov(engine.player->x, engine.player->y, engine.fovRadius);
}

void Map::addMonster(int x, int y) {
    TCODRandom *rng = TCODRandom::getInstance();
    if (rng->getInt(0, 100) < 80) {
        engine.actors.push(new Actor(x, y, 'o', "Orc", TCODColor::desaturatedGreen));
    }
    else {
        engine.actors.push(new Actor(x, y, 'T', "Troll", TCODColor::darkerGreen));
    }
}

void Map::dig(int x1, int y1, int x2, int y2) {
    if (x2 < x1) {
        int tmp = x2;
        x2 = x1;
        x1 = tmp;
    }
    if (y2 < y1) {
        int tmp = y2;
        y2 = y1;
        y1 = tmp;
    }
    for (int tileX = x1; tileX <= x2; tileX++) {
        for (int tileY = y1; tileY <= y2; tileY++) {
            map->setProperties(tileX, tileY, true, true);
        }
    }
}

void Map::createRoom(bool first, int x1, int y1, int x2, int y2) {
    dig(x1, y1, x2, y2);
    if (first) {
        // put the player in the first room
        engine.player->x = (x1 + x2) / 2;
        engine.player->y = (y1 + y2) / 2;
    }
    else {
        TCODRandom *rng = TCODRandom::getInstance();
        int nbMonsters = rng->getInt(0, MAX_ROOM_MONSTERS);
        while (nbMonsters > 0) {
            int x = rng->getInt(x1, x2);
            int y = rng->getInt(y1, y2);
            if (canWalk(x, y)) {
                addMonster(x, y);
            }
            nbMonsters--;
        }
    }
}

void Map::render() const {
    static const TCODColor lightWall(130, 110, 50);
    static const TCODColor lightGround(200, 180, 50);
    static const TCODColor darkWall(0, 0, 100);
    static const TCODColor darkGround(50, 50, 150);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (isInFov(x, y)) {
                TCODConsole::root->setCharBackground(x, y,
                    isWall(x, y) ? lightWall : lightGround);
            }
            else if (isExplored(x, y)) {
                TCODConsole::root->setCharBackground(x, y,
                    isWall(x, y) ? darkWall : darkGround);
            }
        }
    }
}
