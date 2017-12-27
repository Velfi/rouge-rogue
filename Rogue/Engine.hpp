#pragma once
#include "include\libtcod.hpp"
#include "Actor.hpp"
#include "Map.hpp"

class Engine {
public:
    TCODList<Actor *> actors;
    Actor *player;
    Map *map;
    int fovRadius;

    Engine();
    ~Engine();
    void update();
    void render();
private:
    bool computeFov;
};

extern Engine engine;
