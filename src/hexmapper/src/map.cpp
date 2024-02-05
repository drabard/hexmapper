#include "map.h"

#include "rlgl.h"
#include "textures.h"

Vector2 HEX_TRIANGLE_FAN_POSITIONS[] = {
    (Vector2){0.0f, HEX_RADIUS},
    (Vector2){HEX_RADIUS * COS_30, HEX_RADIUS * 0.5f},
    (Vector2){HEX_RADIUS * COS_30, -HEX_RADIUS * 0.5f},
    (Vector2){0.0f, -HEX_RADIUS},
    (Vector2){-HEX_RADIUS * COS_30, -HEX_RADIUS * 0.5f},
    (Vector2){-HEX_RADIUS * COS_30, HEX_RADIUS * 0.5f},
    (Vector2){0.0f, HEX_RADIUS}};

Vector2 HEX_TRIANGLE_FAN_TEXCOORDS[] = {
    (Vector2){0.5f, 1.0f},        (Vector2){0.0f, 1.0f - HALF_TAN_30},
    (Vector2){0.0f, HALF_TAN_30}, (Vector2){0.5f, 0.0f},
    (Vector2){1.0f, HALF_TAN_30}, (Vector2){1.0f, 1.0f - HALF_TAN_30},
    (Vector2){0.5f, 1.0f},
};

void DrawTexturePoly(Texture2D texture, Vector2 center, Vector2 *points,
                     Vector2 *texcoords, int pointCount, Color tint) {
    rlSetTexture(texture.id);

    // Texturing is only supported on RL_QUADS
    rlBegin(RL_QUADS);

    rlColor4ub(tint.r, tint.g, tint.b, tint.a);

    for (int i = 0; i < pointCount - 1; i++) {
        rlTexCoord2f(0.5f, 0.5f);
        rlVertex2f(center.x, center.y);

        rlTexCoord2f(texcoords[i].x, texcoords[i].y);
        rlVertex2f(points[i].x + center.x, points[i].y + center.y);

        rlTexCoord2f(texcoords[i + 1].x, texcoords[i + 1].y);
        rlVertex2f(points[i + 1].x + center.x, points[i + 1].y + center.y);

        rlTexCoord2f(texcoords[i + 1].x, texcoords[i + 1].y);
        rlVertex2f(points[i + 1].x + center.x, points[i + 1].y + center.y);
    }
    rlEnd();

    rlSetTexture(0);
}

void DrawHexAtCoord(i32 mapX, i32 mapY, Texture2D *texture, bool isSelected) {
    constexpr f32 hexXIncrement = HEX_LONG_DIAMETER;
    constexpr f32 hexYIncrement = HEX_RADIUS * 1.5f;
    constexpr f32 hexRotation = 90.0f;
    f32 hexX = mapX * hexXIncrement;
    f32 hexY = mapY * hexYIncrement;
    bool hexIsOdd = bool(mapY & 1);
    ;
    if (hexIsOdd) {
        hexX += HEX_RADIUS * COS_30;
    }

    DrawTexturePoly(*texture, (Vector2){hexX, hexY}, HEX_TRIANGLE_FAN_POSITIONS,
                    HEX_TRIANGLE_FAN_TEXCOORDS, 7, WHITE);
    DrawPolyLines((Vector2){hexX, hexY}, 6, HEX_RADIUS, hexRotation, BLACK);
}

void DrawMap(Map *map, TextureStorage *textureStorage, Vector2 cameraTarget,
             Vector2 viewportSize) {
    i32 startMapX =
        (cameraTarget.x - viewportSize.x * 0.5f) / HEX_LONG_DIAMETER - 1;
    i32 endMapX = startMapX + (viewportSize.x / HEX_LONG_DIAMETER) + 3;
    i32 startMapY =
        (cameraTarget.y - viewportSize.y * 0.5f) / HEX_RADIUS_1_5 - 1;
    i32 endMapY = startMapY + (viewportSize.y / HEX_RADIUS_1_5) + 3;

    Texture2D texture = GetOrLoadTexture(textureStorage, "resources/tiles/mountains/mountains_test.png"); 
    for (i32 i = startMapX; i < endMapX; ++i) {
        for (i32 j = startMapY; j < endMapY; ++j) {
            DrawHexAtCoord(i, j, &texture, false);
        }
    }
}

