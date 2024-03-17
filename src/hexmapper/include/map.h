#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#include "core.h"
#include "raylib.h"

constexpr f32 HEX_RADIUS = 33.0f;
constexpr f32 HEX_RADIUS_1_5 = HEX_RADIUS * 1.5f;
constexpr f32 COS_30 = 0.8660254037844387f;
constexpr f32 COS_30_2 = 2.0f * COS_30;
constexpr f32 HALF_TAN_30 = 0.2886751345948129f;
constexpr f32 HEX_LONG_DIAMETER = HEX_RADIUS * COS_30_2;

struct TextureStorage;

// ================================================================================

struct TileId {
    int32_t x;
    int32_t y;

    explicit operator uint64_t() const {
        return ((uint64_t)x << 32) & (uint64_t)y; 
    }

};

bool operator==(const TileId& left, const TileId& right);

// --------------------------------------------------------------------------------

template<>
struct std::hash<TileId> {
    std::size_t operator()(const TileId& tid) const {
        return hash<uint64_t>()((uint64_t)tid);
    }
};

// ================================================================================

struct Tile {
    TileId tileId;
    std::string texturePath;
};

// ================================================================================

struct Map {
    std::vector<Tile> tiles;
    std::vector<size_t> tilesFree;
    std::unordered_map<TileId, Tile*> idToTile;
};

void InitMap(Map* map);
Tile* CreateTile(Map* map, int32_t x, int32_t y, const char* texturePath);
Tile* FindTile(Map* map, int32_t x, int32_t y);

void DrawMap(Map *map, TextureStorage*, Vector2 cameraTarget, Vector2 viewportSize);

// ================================================================================
