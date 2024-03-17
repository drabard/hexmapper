#include <stdio.h>
#include <string.h>

#include "map.h"
#include "textures.h"

bool checkInteractive(char** envv) {
    for(int i = 0; envv[i] != 0; ++i) {
        if(strncmp(envv[i], "INTERACTIVE=", 12) == 0) {
            return envv[i][12] == '1';
        }
    }
    return false;
}

void InteractiveDrawMap(Map* map, TextureStorage* texStorage, Vector2 viewportSize) {
    Camera2D camera = (Camera2D){
        viewportSize,
        (Vector2){0, 0},                        // target
        0.0f,                                   // rotation
        1.0f                                    // zoom
    };
    PollInputEvents();
    while(!IsKeyPressed(KEY_ESCAPE)) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);
        DrawMap(map, texStorage, (Vector2){}, viewportSize);
        EndMode2D();
        EndDrawing();
    }
}

int main(int argc, char** argv, char** envv) {
    InitWindow(800, 600, "test_texture_storage");
    TextureStorage textureStorage = {};
    Vector2 viewportSize = { 400.0f, 300.0f };

    bool isInteractive = checkInteractive(envv);

    { // Single tile in the center.
        Map map = {};
        InitMap(&map);

        CreateTile(&map, 0, 0, "resources/textures/test_texture0.png");

        if(isInteractive) {
            InteractiveDrawMap(&map, &textureStorage, viewportSize);
        }
    }

    { // tiles going in x and y direction.
        Map map = {};
        InitMap(&map);

        for(int i = 0; i < 9; ++i) {
            CreateTile(&map, i, 0, "resources/textures/test_texture0.png");
            CreateTile(&map, 0, i, "resources/textures/test_texture0.png");
        }

        if(isInteractive) {
            InteractiveDrawMap(&map, &textureStorage, viewportSize);
        }
    }

    return 0;
}
