#pragma once

#include "entities.h"
#include "enums.h"
#include "constants.h"

void initializeField();
void initializeCreatures();
int calculateScore();
void movement(entityWithCoordinates* creature);
void correctDirection(entityWithCoordinates* creature);
void packmanDirection();
void randomDirection(entityWithCoordinates* creature);
void cleverDirection(entityWithCoordinates* creature);
