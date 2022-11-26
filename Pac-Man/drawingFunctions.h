#pragma once
#include <windows.h>

#include "enums.h"
#include "entities.h"
#include "constants.h"

RECT ClientRect;
HBITMAP BG;
HINSTANCE hInstance;

void virtualDrawing(HDC hdc);
