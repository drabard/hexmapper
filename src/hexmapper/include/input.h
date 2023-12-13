#pragma once
#include "raylib.h"

enum InputMode {
    INPUT_MODE_SELECT,
    INPUT_MODE_PAINT,
    INPUT_MODE_ROTATE,
    INPUT_MODE_ERASE
};

struct Input {
    InputMode mode;

    Vector2 cameraShift;
};

void InitInput(Input *input);
void CollectInput(Input *input);
