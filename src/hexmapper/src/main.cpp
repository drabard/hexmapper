#include <stdio.h>

#include <filesystem>
#include <unordered_set>
#include <vector>

#include "core.h"
#include "gui.h"
#include "input.h"
#include "map.h"
#include "math.h"
#include "raylib.h"
#include "rlImGui.h"
#include "rlgl.h"
#include "state.h"
#include "textures.h"

i32 main(int argc, char** argv) {
    u32 screenWidth = 1920;
    u32 screenHeight = 1024;

    InitWindow(screenWidth, screenHeight, "Hex Mapper");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetTargetFPS(60);

    InitGUI();

    State state;
    InitState(&state, screenWidth, screenHeight);

    Input input;
    InitInput(&input);

    Map map;

    while (!(WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))) {
        CollectInput(&input);
        ApplyInput(&state, &input);

        if (IsWindowResized()) {
            HandleScreenResize(&state, GetScreenWidth(), GetScreenHeight());
            TraceLog(LOG_INFO, "Window resized: %d, %d", GetScreenWidth(),
                     GetScreenHeight());
        }

        BeginDrawing();

        {
            BeginMode2D(state.camera);
            ClearBackground(RAYWHITE);

            DrawMap(&map, &state.textureStorage, state.camera.target,
                    (Vector2){(f32)state.screenWidth, (f32)state.screenHeight});

            EndMode2D();
        }

        ApplyGUI(state.screenWidth, state.screenHeight, &input, &state);

        EndDrawing();

        SweepAndEvictTextures(&state.textureStorage);
    }

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}
