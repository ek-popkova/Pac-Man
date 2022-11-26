#pragma once

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    INIT
};

enum CellState {
    ZERO,
    SEED,
    BLOCK,
    CHANGE,
    CHANGESEED
};

enum GameStat {
    WIN,
    LOSE,
    THREE,
    TWO,
    ONE
};