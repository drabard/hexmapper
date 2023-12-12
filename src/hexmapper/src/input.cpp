#include "input.h"

void CollectInput(Input *input) {
    constexpr f32 cameraSpeed = 10.0f;
    input->cameraShift = (Vector2){0, 0};
    if (IsKeyDown(KEY_W)) {
        input->cameraShift.y -= cameraSpeed;
    }
    if (IsKeyDown(KEY_S)) {
        input->cameraShift.y += cameraSpeed;
    }
    if (IsKeyDown(KEY_A)) {
        input->cameraShift.x -= cameraSpeed;
    }
    if (IsKeyDown(KEY_D)) {
        input->cameraShift.x += cameraSpeed;
    }
}
