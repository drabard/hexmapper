#pragma once

#include "core.h"
#include "raylib.h"

constexpr f32 HEX_RADIUS = 50.0f;
constexpr f32 HEX_RADIUS_1_5 = HEX_RADIUS * 1.5f;
constexpr f32 COS_30 = 0.8660254037844387f;
constexpr f32 COS_30_2 = 2.0f * COS_30;
constexpr f32 HALF_TAN_30 = 0.2886751345948129f;
constexpr f32 HEX_LONG_DIAMETER = HEX_RADIUS * COS_30_2;

struct TextureStorage;

struct Map {
};

void DrawMap(Map *map, TextureStorage*, Vector2 cameraTarget, Vector2 viewportSize);
