#pragma once

#include "core.h"
#include "raylib.h"

struct State {
    Camera2D camera;
    u32 viewportWidth;
    u32 viewportHeight;
};

void InitState(State *state);
void ApplyInput(State *state, Input *input);
void HandleScreenResize(State *state, u32 width, u32 height);
