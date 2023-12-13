#pragma once

#include "core.h"
#include "raylib.h"

struct State {
    Camera2D camera;
    u32 screenWidth;
    u32 screenHeight;
};

void InitState(State *state, u32 screenWidth, u32 screenHeight);
void ApplyInput(State *state, Input *input);
void HandleScreenResize(State *state, u32 width, u32 height);
