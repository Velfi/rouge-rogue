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
    enum GameStatus {
        STARTUP,
        IDLE,
        NEW_TURN,
        VICTORY,
        DEFEAT
    } gameStatus;

    Engine();
    ~Engine();
    void update();
    void render();
private:
    bool computeFov;
};

extern Engine engine;
