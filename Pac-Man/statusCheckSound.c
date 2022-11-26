#include "statusCheckSound.h"

void checkStatus()
{
    if (calculateScore() == MAX_SCORE) gameStatus = WIN;

    int deltaX;
    int deltaY;
    for (int i = 0; i < 4; i++)
    {
        deltaX = abs(Packman.x - Ghost[i].x);
        deltaY = abs(Packman.y - Ghost[i].y);
        if ((deltaX < SQUARE_SIZE - 5) && (deltaY < SQUARE_SIZE - 5))
        {
            switch (gameStatus)
            {
            case THREE:
            {
                gameStatus = TWO;
                Packman.x = 0;
                Packman.y = 0;
                PlaySoundW(TEXT(".\\injured.wav"), NULL, SND_FILENAME | SND_ASYNC);
                break;
            }
            case TWO:
            {
                gameStatus = ONE;
                Packman.x = 0;
                Packman.y = 0;
                PlaySoundW(TEXT(".\\injured.wav"), NULL, SND_FILENAME | SND_ASYNC);
                break;
            }
            case ONE:
            {
                gameStatus = LOSE;
                PlaySoundW(TEXT(".\\died.wav"), NULL, SND_FILENAME | SND_ASYNC);
                break;
            }
            };
        }
    }
}

void checkSeed()
{
    for (int i = 0; i < FIELD_SIZE_HORIZONTAL; i++)
    {
        for (int j = 0; j < FIELD_SIZE_VERTICAL; j++)
        {
            if (FIELD[i][j] == SEED &&
                (Packman.x > i * SQUARE_SIZE - SEED_SIZE) &&
                (Packman.x < i * SQUARE_SIZE + SEED_SIZE) &&
                (Packman.y > j * SQUARE_SIZE - SEED_SIZE) &&
                (Packman.y < j * SQUARE_SIZE + SEED_SIZE))
            {
                FIELD[i][j] = ZERO;
                /*Beep(800, 10);
                Beep(600, 10);*/
                PlaySoundW(TEXT(".\\eat.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            if (FIELD[i][j] == CHANGESEED &&
                (Packman.x > i * SQUARE_SIZE - SEED_SIZE) &&
                (Packman.x < i * SQUARE_SIZE + SEED_SIZE) &&
                (Packman.y > j * SQUARE_SIZE - SEED_SIZE) &&
                (Packman.y < j * SQUARE_SIZE + SEED_SIZE))
            {
                FIELD[i][j] = CHANGE;
                /*Beep(800, 10);
                Beep(600, 10);*/
                PlaySoundW(TEXT(".\\eat.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
        }
    }
}