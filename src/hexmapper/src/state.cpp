#include "state.h"

#include "fstree.h"

void InitState(State *state, u32 screenWidth, u32 screenHeight) {
    *state = (State){};
    state->screenWidth = screenWidth;
    state->screenHeight = screenHeight;
    state->zoomLevel = ZOOM_6_MILES;
    state->camera = (Camera2D){
        (Vector2){state->screenWidth * 0.5f,
                  state->screenHeight * 0.5f},  // offset
        (Vector2){0, 0},                        // target
        0.0f,                                   // rotation
        1.0f                                    // zoom
    };

    state->imagesRoot = ParseDirectory("resources/tiles/");
}

void ApplyInput(State *state, Input *input) {
    f32 cameraShiftX = input->cameraShift.x;
    f32 cameraShiftY = input->cameraShift.y;
    if (cameraShiftX || cameraShiftY) {
        state->camera.target.x += cameraShiftX;
        state->camera.target.y += cameraShiftY;
    }
    if (input->zoomIn) {
        i32 newZoomLevel = (i32)state->zoomLevel + 1;
        state->zoomLevel =
            (ZoomLevel)(newZoomLevel >= ZOOM_COUNT ? ZOOM_COUNT - 1
                                                   : newZoomLevel);
        input->zoomIn = false;
    } else if (input->zoomOut) {
        i32 newZoomLevel = (i32)state->zoomLevel - 1;
        state->zoomLevel = (ZoomLevel)(newZoomLevel < 0 ? 0 : newZoomLevel);
        input->zoomOut = false;
    }
}

void HandleScreenResize(State *state, u32 width, u32 height) {
    state->screenWidth = width;
    state->screenHeight = height;
    state->camera.offset =
        (Vector2){state->screenWidth * 0.5f, state->screenHeight * 0.5f};
}

