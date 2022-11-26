//#include "MyGreatHeader.h"
#include "calculationFunctions.h"

enum CellState KEEP_FIELD[FIELD_SIZE_HORIZONTAL][FIELD_SIZE_VERTICAL] = {{ZERO, SEED, SEED, CHANGESEED, SEED, SEED, BLOCK, BLOCK, BLOCK, SEED, BLOCK, BLOCK, SEED, SEED, SEED, BLOCK, SEED, SEED, SEED}, \
{ SEED, BLOCK, BLOCK, SEED, BLOCK, SEED, BLOCK, BLOCK, BLOCK, SEED, BLOCK, BLOCK, SEED, BLOCK, SEED, SEED, CHANGESEED, BLOCK, SEED }, \
{ SEED, BLOCK, BLOCK, SEED, BLOCK, SEED, BLOCK, BLOCK, BLOCK, SEED, BLOCK, BLOCK, SEED, BLOCK, BLOCK, BLOCK, SEED, BLOCK, SEED }, \
{ CHANGESEED, SEED, SEED, CHANGESEED, SEED, CHANGESEED, SEED, SEED, SEED, CHANGESEED, SEED, SEED, CHANGESEED, SEED, CHANGESEED, SEED, SEED, BLOCK, SEED }, \
{ SEED, BLOCK, BLOCK, SEED, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, SEED, BLOCK, BLOCK, SEED, BLOCK, SEED, BLOCK, BLOCK, BLOCK, SEED }, \
{ SEED, BLOCK, BLOCK, CHANGESEED, SEED, SEED, BLOCK, SEED, SEED, CHANGESEED, SEED, SEED, CHANGESEED, BLOCK, SEED, SEED, SEED, BLOCK, SEED }, \
{ SEED, BLOCK, BLOCK, SEED, BLOCK, SEED, BLOCK, SEED, BLOCK, BLOCK, SEED, BLOCK, SEED, BLOCK, SEED, BLOCK, SEED, BLOCK, SEED }, \
{ SEED, SEED, SEED, CHANGESEED, BLOCK, SEED, SEED, CHANGESEED, BLOCK, BLOCK, SEED, BLOCK, SEED, SEED, CHANGESEED, BLOCK, SEED, SEED, SEED }, \
{ BLOCK, BLOCK, BLOCK, SEED, BLOCK, BLOCK, BLOCK, SEED, BLOCK, BLOCK, SEED, BLOCK, BLOCK, BLOCK, SEED, BLOCK, BLOCK, BLOCK, SEED }, \
{ SEED, SEED, SEED, CHANGESEED, BLOCK, SEED, SEED, CHANGESEED, BLOCK, BLOCK, SEED, BLOCK, SEED, SEED, CHANGESEED, BLOCK, SEED, SEED, SEED }, \
{ SEED, BLOCK, BLOCK, SEED, BLOCK, SEED, BLOCK, SEED, BLOCK, BLOCK, SEED, BLOCK, SEED, BLOCK, SEED, BLOCK, SEED, BLOCK, SEED }, \
{ SEED, BLOCK, BLOCK, CHANGESEED, SEED, SEED, BLOCK, SEED, SEED, CHANGESEED, SEED, SEED, CHANGESEED, BLOCK, SEED, SEED, SEED, BLOCK, SEED }, \
{ SEED, BLOCK, BLOCK, SEED, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, SEED, BLOCK, BLOCK, SEED, BLOCK, SEED, BLOCK, BLOCK, BLOCK, SEED }, \
{ CHANGESEED, SEED, SEED, CHANGESEED, SEED, CHANGESEED, SEED, SEED, SEED, CHANGESEED, SEED, SEED, CHANGESEED, SEED, CHANGESEED, SEED, SEED, BLOCK, SEED }, \
{ SEED, BLOCK, BLOCK, SEED, BLOCK, SEED, BLOCK, BLOCK, BLOCK, SEED, BLOCK, BLOCK, SEED, BLOCK, BLOCK, BLOCK, SEED, BLOCK, SEED }, \
{ SEED, BLOCK, BLOCK, SEED, BLOCK, SEED, BLOCK, BLOCK, BLOCK, SEED, BLOCK, BLOCK, SEED, BLOCK, SEED, SEED, CHANGESEED, BLOCK, SEED }, \
{ SEED, SEED, SEED, CHANGESEED, SEED, SEED, BLOCK, BLOCK, BLOCK, SEED, BLOCK, BLOCK, SEED, SEED, SEED, BLOCK, SEED, SEED, SEED }};

void constructEntityWithCoordinates(entityWithCoordinates* creature, int x, int y, enum Direction current_direction, enum Direction next_direction)
{
    (*creature).x = x;
    (*creature).y = y;
    (*creature).current_direction = current_direction;
    (*creature).next_direction = next_direction;
}

void initializeField()
{
    for (int i = 0; i < FIELD_SIZE_HORIZONTAL; i++)
    {
        for (int j = 0; j < FIELD_SIZE_VERTICAL; j++)
        {
            FIELD[i][j] = KEEP_FIELD[i][j];
        }
    }
}

void initializeCreatures()
{
    constructEntityWithCoordinates(&Packman, 0, 0, INIT, INIT);

    constructEntityWithCoordinates(&Ghost[0], SQUARE_SIZE * (FIELD_SIZE_HORIZONTAL - 1), 0, DOWN, INIT);
    constructEntityWithCoordinates(&Ghost[1], 0, SQUARE_SIZE * (FIELD_SIZE_VERTICAL - 1), RIGHT, INIT);
    constructEntityWithCoordinates(&Ghost[2], SQUARE_SIZE * (FIELD_SIZE_HORIZONTAL - 1), SQUARE_SIZE * (FIELD_SIZE_VERTICAL - 1), RIGHT, INIT);
    constructEntityWithCoordinates(&Ghost[3], 8 * SQUARE_SIZE, 7 * SQUARE_SIZE, LEFT, INIT);

}

int calculateScore()
{
    int score = 0;
    for (int i = 0; i < FIELD_SIZE_HORIZONTAL; i++)
    {
        for (int j = 0; j < FIELD_SIZE_VERTICAL; j++)
        {
            if ((FIELD[i][j] == ZERO) || (FIELD[i][j] == CHANGE)) score++;
        }
    }
    return score;
}


void movement(entityWithCoordinates* creature)
{
    switch ((*creature).current_direction)
    {
    case RIGHT:
        if (((*creature).y % SQUARE_SIZE == 0) &&
            (FIELD[((*creature).x / SQUARE_SIZE) + 1][(*creature).y / SQUARE_SIZE] != BLOCK) &&
            (*creature).x != SQUARE_SIZE * (FIELD_SIZE_HORIZONTAL - 1))
        {
            (*creature).x++;
        }
        if (((*creature).x / SQUARE_SIZE == 16) && ((*creature).y / SQUARE_SIZE == 9))
        {
            if ((*creature).x < SQUARE_SIZE * (FIELD_SIZE_HORIZONTAL - 1)) (*creature).x++;
            else (*creature).x = 0;
        }
        break;
    case LEFT:
        if (((*creature).y % SQUARE_SIZE == 0) &&
            (FIELD[((*creature).x - 1) / SQUARE_SIZE][(*creature).y / SQUARE_SIZE] != BLOCK) &&
            (*creature).x != 0)
        {
            (*creature).x--;
        }
        if (((*creature).x / SQUARE_SIZE == 0) && ((*creature).y / SQUARE_SIZE == 9))
        {
            if ((*creature).x > 0) (*creature).x--;
            else (*creature).x = SQUARE_SIZE * (FIELD_SIZE_HORIZONTAL - 1);
        }
        break;
    case UP:
        if (((*creature).x % SQUARE_SIZE == 0) &&
            (FIELD[(*creature).x / SQUARE_SIZE][((*creature).y - 1) / SQUARE_SIZE] != BLOCK) &&
            (*creature).y != 0)
        {
            (*creature).y--;
        }
        break;
    case DOWN:
        if (((*creature).x % SQUARE_SIZE == 0) &&
            (FIELD[(*creature).x / SQUARE_SIZE][((*creature).y / SQUARE_SIZE) + 1] != BLOCK) &&
            (*creature).y != SQUARE_SIZE * (FIELD_SIZE_VERTICAL - 1))
        {
            (*creature).y++;
        }
        break;
    };
}

void correctDirection(entityWithCoordinates* creature)
{
    if (((*creature).y % SQUARE_SIZE == 0) &&
        (*creature).x % SQUARE_SIZE == 0 &&
        (FIELD[(*creature).x / SQUARE_SIZE][(*creature).y / SQUARE_SIZE] != CHANGE) &&
        (FIELD[(*creature).x / SQUARE_SIZE][(*creature).y / SQUARE_SIZE] != CHANGESEED))
    {
        if (((*creature).current_direction == LEFT) &&
            ((FIELD[((*creature).x - 1) / SQUARE_SIZE][(*creature).y / SQUARE_SIZE] == BLOCK) ||
                ((*creature).x == 0)))
        {
            if ((FIELD[(*creature).x / SQUARE_SIZE][((*creature).y - 1) / SQUARE_SIZE] == BLOCK) ||
                (*creature).y == 0)
            {
                (*creature).current_direction = DOWN;
            }
            if ((FIELD[(*creature).x / SQUARE_SIZE][((*creature).y / SQUARE_SIZE) + 1] == BLOCK) ||
                ((*creature).y == (FIELD_SIZE_VERTICAL - 1) * SQUARE_SIZE))
            {
                (*creature).current_direction = UP;
            }
        }
        else if (((*creature).current_direction == RIGHT) &&
            ((FIELD[((*creature).x / SQUARE_SIZE) + 1][(*creature).y / SQUARE_SIZE] == BLOCK) ||
                ((*creature).x == (FIELD_SIZE_HORIZONTAL - 1) * SQUARE_SIZE)))
        {
            if ((FIELD[(*creature).x / SQUARE_SIZE][((*creature).y - 1) / SQUARE_SIZE] == BLOCK) ||
                (*creature).y == 0)
            {
                (*creature).current_direction = DOWN;
            }
            if ((FIELD[(*creature).x / SQUARE_SIZE][((*creature).y / SQUARE_SIZE) + 1] == BLOCK) ||
                ((*creature).y == (FIELD_SIZE_VERTICAL - 1) * SQUARE_SIZE))
            {
                (*creature).current_direction = UP;
            }
        }
        else if (((*creature).current_direction == UP) &&
            ((FIELD[(*creature).x / SQUARE_SIZE][((*creature).y - 1) / SQUARE_SIZE] == BLOCK) ||
                (*creature).y == 0))
        {
            if ((FIELD[((*creature).x - 1) / SQUARE_SIZE][(*creature).y / SQUARE_SIZE] == BLOCK) ||
                ((*creature).x == 0))
            {
                (*creature).current_direction = RIGHT;
            }
            if ((FIELD[((*creature).x / SQUARE_SIZE) + 1][(*creature).y / SQUARE_SIZE] == BLOCK) ||
                ((*creature).x == (FIELD_SIZE_HORIZONTAL - 1) * SQUARE_SIZE))
            {
                (*creature).current_direction = LEFT;
            }
        }
        else if (((*creature).current_direction == DOWN) &&
            ((FIELD[(*creature).x / SQUARE_SIZE][((*creature).y / SQUARE_SIZE) + 1] == BLOCK) ||
                ((*creature).y == (FIELD_SIZE_VERTICAL - 1) * SQUARE_SIZE)))
        {
            if ((FIELD[((*creature).x - 1) / SQUARE_SIZE][(*creature).y / SQUARE_SIZE] == BLOCK) ||
                ((*creature).x == 0))
            {
                (*creature).current_direction = RIGHT;
            }
            if ((FIELD[((*creature).x / SQUARE_SIZE) + 1][(*creature).y / SQUARE_SIZE] == BLOCK) ||
                ((*creature).x == (FIELD_SIZE_HORIZONTAL - 1) * SQUARE_SIZE))
            {
                (*creature).current_direction = LEFT;
            }
        }
    }
}


void packmanDirection()
{
    if ((Packman.y % SQUARE_SIZE == 0)
        && (Packman.x % SQUARE_SIZE == 0)
        && (Packman.current_direction != Packman.next_direction) &&
        (((Packman.next_direction == LEFT) && (FIELD[(Packman.x - 1) / SQUARE_SIZE][Packman.y / SQUARE_SIZE] != BLOCK) && (Packman.x != 0)) ||
            ((Packman.next_direction == RIGHT) && (FIELD[(Packman.x / SQUARE_SIZE) + 1][Packman.y / SQUARE_SIZE] != BLOCK) && (Packman.x != (FIELD_SIZE_HORIZONTAL - 1) * SQUARE_SIZE)) ||
            ((Packman.next_direction == UP) && (FIELD[Packman.x / SQUARE_SIZE][(Packman.y - 1) / SQUARE_SIZE] != BLOCK) && (Packman.y != 0)) ||
            ((Packman.next_direction == DOWN) && (FIELD[Packman.x / SQUARE_SIZE][(Packman.y / SQUARE_SIZE) + 1] != BLOCK) && (Packman.y != (FIELD_SIZE_VERTICAL - 1) * SQUARE_SIZE))))
    {
        Packman.current_direction = Packman.next_direction;
    }
}

void randomDirection(entityWithCoordinates* creature)
{
    if (((*creature).y % SQUARE_SIZE == 0) &&
        (*creature).x % SQUARE_SIZE == 0 &&
        ((FIELD[(*creature).x / SQUARE_SIZE][(*creature).y / SQUARE_SIZE] == CHANGE) ||
            (FIELD[(*creature).x / SQUARE_SIZE][(*creature).y / SQUARE_SIZE] == CHANGESEED)))
    {
        if (((*creature).current_direction == UP) || ((*creature).current_direction == DOWN))
        {

        }
        switch (rand() % 2)
        {
        case 0:
        {
            if (((*creature).current_direction == UP) || ((*creature).current_direction == DOWN))
            {
                (*creature).current_direction = LEFT;
            }
            else
            {
                (*creature).current_direction = UP;
            }
            break;
        }
        case 1:
        {
            if (((*creature).current_direction == UP) || ((*creature).current_direction == DOWN))
            {
                (*creature).current_direction = RIGHT;
            }
            else
            {
                (*creature).current_direction = DOWN;
            }
            break;
        }
        };
    }
    correctDirection(creature);
}

void cleverDirection(entityWithCoordinates* creature)
{
    if (((*creature).y % SQUARE_SIZE == 0) &&
        (*creature).x % SQUARE_SIZE == 0 &&
        ((FIELD[(*creature).x / SQUARE_SIZE][(*creature).y / SQUARE_SIZE] == CHANGE) ||
            (FIELD[(*creature).x / SQUARE_SIZE][(*creature).y / SQUARE_SIZE] == CHANGESEED)))
    {
        int deltaX = Packman.x - (*creature).x;
        int deltaY = Packman.y - (*creature).y;
        if ((abs(deltaX) > abs(deltaY)) && (deltaX < 0) &&
            (FIELD[((*creature).x - 1) / SQUARE_SIZE][(*creature).y / SQUARE_SIZE] != BLOCK))
            (*creature).current_direction = LEFT;
        else if ((abs(deltaX) > abs(deltaY)) && (deltaX > 0) &&
            (FIELD[((*creature).x / SQUARE_SIZE) + 1][(*creature).y / SQUARE_SIZE] != BLOCK))
            (*creature).current_direction = RIGHT;
        else if ((abs(deltaX) < abs(deltaY)) && (deltaY < 0) &&
            (FIELD[(*creature).x / SQUARE_SIZE][((*creature).y - 1) / SQUARE_SIZE] != BLOCK))
            (*creature).current_direction = UP;
        else if ((abs(deltaX) < abs(deltaY)) && (deltaY > 0) &&
            (FIELD[(*creature).x / SQUARE_SIZE][((*creature).y / SQUARE_SIZE) + 1] != BLOCK))
            (*creature).current_direction = DOWN;
        else randomDirection(creature);
    }
    correctDirection(creature);
}

