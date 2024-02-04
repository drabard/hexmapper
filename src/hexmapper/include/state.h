#pragma once

#include "core.h"
#include "raylib.h"

#include "input.h"
#include "fstree.h"
#include "textures.h"

enum ZoomLevel {
    ZOOM_6_MILES = 0,
    ZOOM_12_MILES,
    ZOOM_24_MILES,
    ZOOM_48_MILES,
    ZOOM_COUNT
};

struct State {
    Camera2D camera;
    u32 screenWidth;
    u32 screenHeight;

    ZoomLevel zoomLevel;

    FsNode imagesRoot;

    TextureStorage textureStorage;
};

void InitState(State *state, u32 screenWidth, u32 screenHeight);
void ApplyInput(State *state, Input *input);
void HandleScreenResize(State *state, u32 width, u32 height);
