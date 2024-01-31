#pragma once

#include "core.h"
#include "raylib.h"

constexpr f32 HEX_RADIUS = 50.0f;
constexpr f32 HEX_RADIUS_1_5 = HEX_RADIUS * 1.5f;
constexpr f32 COS_30 = 0.8660254037844387f;
constexpr f32 COS_30_2 = 2.0f * COS_30;
constexpr f32 HALF_TAN_30 = 0.2886751345948129f;
constexpr f32 HEX_LONG_DIAMETER = HEX_RADIUS * COS_30_2;

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

struct Map {
    // Start here - sparse storage for hexes
    Texture2D texture;
};

Map CreateMap();

void DrawMap(Map *map, Vector2 cameraTarget, Vector2 viewportSize);
