#pragma once

#include <unordered_map>
#include <string>

#include "raylib.h"

constexpr size_t MAX_STORED_TEXTURES = 100; 

struct TextureEntry {
    bool used;
    Texture2D texture;
};

struct TextureStorage {
    TextureEntry textures[MAX_STORED_TEXTURES];
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

// Iterates through all TextureEntries and checks the used flag. If the flag
// is false, the texture is unloaded and made available. If the flag is true,
// it's set to false.
// This should be periodically called to free up space for new textures and remove
// old ones.
void SweepAndEvictTextures(TextureStorage* storage);
