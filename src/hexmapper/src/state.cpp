#include "state.h"

void InitState(State *state) {
    state->viewportWidth = 1920;
    state->viewportHeight = 1080;
    state->camera = (Camera2D){
        (Vector2){state->viewportWidth * 0.5f,
                  state->viewportHeight * 0.5f},  // offset
        (Vector2){0, 0},                          // target
        0.0f,                                     // rotation
        1.0f                                      // zoom
    };
}

void ApplyInput(State *state, Input *input) {
    f32 cameraShiftX = input->cameraShift.x;
    f32 cameraShiftY = input->cameraShift.y;
    if (cameraShiftX || cameraShiftY) {
        state->camera.target.x += cameraShiftX;
        state->camera.target.y += cameraShiftY;
    }
}

void HandleScreenResize(State *state, u32 width, u32 height) {
    state->viewportWidth = width;
    state->viewportHeight = height;
    state->camera.offset = (Vector2){state->viewportWidth * 0.5f,
                                      state->viewportHeight * 0.5f};
}

