#pragma once
#include "raylib.h"

enum InputMode {
    INPUT_MODE_SELECT,
    INPUT_MODE_PAINT,
    INPUT_MODE_ROTATE,
    INPUT_MODE_ERASE
};

struct Input {
    // Static properties - persist between frames
    InputMode mode;

    // Transient properties - change every frame
    Vector2 cameraShift;
    bool zoomIn;
    bool zoomOut;
};

void InitInput(Input *input);
void CollectInput(Input *input);
