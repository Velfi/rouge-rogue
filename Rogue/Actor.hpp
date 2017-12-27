#pragma once
#include "include\libtcod.hpp"

class Actor
{
public:
    int x, y; // position on map
    int ch; // ascii char code
    TCODColor col; // color

    Actor(int x, int y, int ch, const TCODColor &col);
    void render() const;
};

