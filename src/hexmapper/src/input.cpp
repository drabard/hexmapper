#include "input.h"

void CollectInput(Input *input) {
    input->cameraShift = (Vector2){0, 0};
    {  // Camera shift - keyboard
        f32 cameraSpeed = 10.0f;

        if (IsKeyDown(KEY_LEFT_CONTROL)) {
            cameraSpeed *= 0.1f;
        } else if (IsKeyDown(KEY_LEFT_SHIFT)) {
            cameraSpeed *= 2.0f;
        }

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

    {  // Camera shift - mouse
        if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON)) {
            Vector2 mouseDelta = GetMouseDelta();
            input->cameraShift.x -= mouseDelta.x;
            input->cameraShift.y -= mouseDelta.y;
        }
    }
}
