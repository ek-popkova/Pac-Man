# :video_game: Pac-Man

![2023-06-22_23-14-48](https://github.com/ek-popkova/Pac-Man/assets/111788752/58fe3edc-b060-4049-ace2-106600a07f4c)


## :memo: The rules

- The goal of the game is to eat all the seeds and avoid the ghosts.
- The player has 3 lives, they are lost when the PacMan meets ghosts.
- After 3 collisions, the game ends.
- There are 2 wormholes on the field, which allow the Pac-Man to escape from the ghosts through the field boundary.
- The player controls the movement of the pac-man by pressing the arrows on the keyboard
- Using the ESC and SPACE keys, you can restart the game or exit the application

## :building_construction: The architecture

The code is devided into 3 modules:
- calculateFunctions – functions, that are independent from the <windows.h> library, and are used to calculate the coordinates
- drawingFunctions – functions, that are dependent on the <windows.h> library, and are responsible for representing the picture on the screen
- statusCheckSound – functions, that are dependent on <windows.h> and winmm.lib and are responsible for checking the state of cells and the game itself and playing the sound whenever it changes.

## :hammer_and_wrench: Main implementation features

### Memorizing the state

The playing field is stored in memory as an array of elements of type enum Cellstate:

      enum CellState {
          ZERO,
          SEED,
          BLOCK,
          CHANGE,
          CHANGESEED
      };

- ZERO - cell is empty
- SEED - there is a seed in the cell
- BLOCK - there is a wall in the cell
- CHANGE - a cell where ghost decides to change direction without a seed
- CHANGESEED - CHANGE with a seed

### Pacman and ghost movement

Pacman and ghosts are structures

      typedef struct entity {
          int x;
          int y;
          enum Direction current_direction;
          enum Direction next_direction;
      } entityWithCoordinates;

      enum Direction {
          LEFT,
          RIGHT,
          UP,
          DOWN,
          INIT
      };

Pacman and ghosts are moved by timer in the direction, that is memorized as thier current_direction. When a player presses an arrow on the keyboared, new direction is stored in next_direction till the Pac-Man reaches a cell, where he can turn. Ghosts don't use next_direction.

### Ghosts movement

- Green ghosts are stupid – they change their direction randomly on CHANGE-cells.
- Red one is clever – he chases Pacman by calculating the shortest direction to him on CHANGE-cells.
- If there is a BLOCK in front of a ghost, special function corrects its behavior.

## :link: Additional information

You can watch the gameplay video [here](https://drive.google.com/file/d/11vB8LE5XquB3O6VZePCvzALH4BGoazou/view?usp=share_link "Watch video on google drive").

The presentation about the structure of the game is available [here](https://www.slideshare.net/secret/Ac9ymbuOXFzJDI "See the slides on slideshare").
