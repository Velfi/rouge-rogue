#pragma once
#include "include\libtcod.hpp"
#include "Map.hpp"
#include "Actor.hpp"
#include "Engine.hpp"

class BspListener : public ITCODBspCallback
{
public:
    BspListener(Map &map) : map(map), roomNum(0) {}
    bool visitNode(TCODBsp *node, void *userData);
private:
    Map & map;
    int roomNum;
    int lastX, lastY;
};

