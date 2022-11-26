#pragma once

typedef struct entity {
    int x;
    int y;
    enum Direction current_direction;
    enum Direction next_direction;
} entityWithCoordinates;
