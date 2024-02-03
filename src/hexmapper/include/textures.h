#pragma once

#include <unordered_map>
#include <string>

#include "raylib.h"

constexpr size_t MAX_STORED_TEXTURES = 100; 

struct TextureStorage {
    Texture2D textures[MAX_STORED_TEXTURES];
    size_t ntextures;
    size_t freeSlots[MAX_STORED_TEXTURES];
    size_t nfree;
    std::unordered_map<std::string, size_t> texLut;
};

// Returns a raylib Texture2D. Textures are not loaded twice, if they're already
// resident on the GPU. 
// @storage: TextureStorage pointer..
// @path: path to the file containing the texture. If file doesn't exist, invalid
//   Texture2D is returned (all zeros).
Texture2D GetOrLoadTexture(TextureStorage* storage, const char* path);
