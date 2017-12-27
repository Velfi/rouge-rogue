#pragma once
#include "include\libtcod.hpp"

static const int MAX_NAME_LENGTH = 8;

class Actor
{
public:
    int x, y; // position on map
    int ch; // ascii char code
    char name[ MAX_NAME_LENGTH ];
    TCODColor col; // color

    Actor(int x, int y, int ch, const char *name, const TCODColor &col);
    void update();
    bool moveOrAttack(int x, int y);
    void render() const;
};

