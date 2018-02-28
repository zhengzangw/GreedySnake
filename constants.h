#ifndef CONSTANTS_H
#define CONSTANTS_H

const int TILE_SIZE = 10;
const qreal SNAKE_SIZE = 10;
const qreal FOOD_RADIUS = 3;
const int MAP_SIZE = 100;
const int CRAZY = 1;
const int HARD = 4;
const int MIDDLE = 7;
const int EASY = 10;

enum GameObjectsData {
    GD_Type
};

enum GameObjectTypes {
    GO_Food,
    GO_Wall
};

#endif // CONSTANTS_H
