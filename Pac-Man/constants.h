#pragma once

#define FIELD_SIZE_VERTICAL 19
#define FIELD_SIZE_HORIZONTAL 17
#define SQUARE_SIZE 25
#define PIXEL_GAP1 1
#define PIXEL_GAP2 2
#define SEED_SIZE 8
#define MAX_SCORE 185



enum CellState FIELD[FIELD_SIZE_HORIZONTAL][FIELD_SIZE_VERTICAL];
enum GameStat gameStatus;

entityWithCoordinates Packman;
entityWithCoordinates Ghost[4];

