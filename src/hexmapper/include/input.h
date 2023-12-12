#pragma once
#include "raylib.h"

struct Input {
    Vector2 cameraShift;
};

void CollectInput(Input *input);
