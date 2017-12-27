#include "BspListener.hpp"


bool BspListener::visitNode(TCODBsp *node, void *userData) {
    if (node->isLeaf()) {
        int x, y, w, h;
        TCODRandom *rng = TCODRandom::getInstance();
        w = rng->getInt(ROOM_MIN_SIZE, node->w - 2);
        h = rng->getInt(ROOM_MIN_SIZE, node->h - 2);
        x = rng->getInt(node->x + 1, node->x + node->w - w - 1);
        y = rng->getInt(node->y + 1, node->y + node->h - h - 1);
        map.createRoom(roomNum == 0, x, y, x + w - 1, y + h - 1);
        if (roomNum != 0) {
            // dig a corridor from last room
            map.dig(lastX, lastY, x + w / 2, lastY);
            map.dig(x + w / 2, lastY, x + w / 2, y + h / 2);
        }
        lastX = x + w / 2;
        lastY = y + h / 2;
        roomNum++;
    }
    return true;
}
