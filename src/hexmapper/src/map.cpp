#include "map.h"

#include "rlgl.h"
#include "textures.h"

constexpr size_t MAX_TILES_IN_MAP = 4096;

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

    if(texture) {
        DrawTexturePoly(*texture, (Vector2){hexX, hexY}, HEX_TRIANGLE_FAN_POSITIONS,
                        HEX_TRIANGLE_FAN_TEXCOORDS, 7, WHITE);
    }
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

    for (i32 i = startMapX; i < endMapX; ++i) {
        for (i32 j = startMapY; j < endMapY; ++j) {
            Tile* tile = FindTile(map, i, j);
            if(tile) {
                Texture2D texture = GetOrLoadTexture(textureStorage, tile->texturePath.c_str()); 
                DrawHexAtCoord(i, j, &texture, false);
            } else {
                DrawHexAtCoord(i, j, nullptr, false);
            }
        }
    }
}

void InitMap(Map* map) {
    map->tiles.clear();
    map->tiles.reserve(MAX_TILES_IN_MAP);
    map->tilesFree.clear();
    map->tilesFree.reserve(MAX_TILES_IN_MAP);
    map->idToTile.clear();
}

Tile* CreateTile(Map* map, int32_t x, int32_t y, const char* texturePath) {
    Tile* t = nullptr;

    if(!map->tilesFree.empty()) {
        size_t tidx = map->tilesFree.back();
        map->tilesFree.pop_back();
        t = &map->tiles[tidx];
    } else {
        if(map->tiles.size() == MAX_TILES_IN_MAP) {
            TraceLog(LOG_ERROR, "Cannot create a Tile at %d, %d (%s)- map is full.", x, y, texturePath);
            return nullptr;
        }
        map->tiles.emplace_back((Tile){ x, y, texturePath });
        t = &map->tiles.back();
    }

    t->tileId.x = x;
    t->tileId.y = y;
    t->texturePath = texturePath;

    map->idToTile[t->tileId] = t;

    return t;
}

Tile* FindTile(Map* map, int32_t x, int32_t y) {
    TileId tid = (TileId){ x, y };
    auto it = map->idToTile.find(tid);
    if(it != map->idToTile.end()) {
        return (*it).second;
    }
    return nullptr;
} 

bool operator==(const TileId& left, const TileId& right) {
    return left.x == right.x && left.y == right.y;
}
