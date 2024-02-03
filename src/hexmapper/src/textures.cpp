#include "textures.h"

Texture2D GetOrLoadTexture(TextureStorage* storage, const char* path) {
    Texture2D* textures = storage->textures;

    // Try cache first.
    std::unordered_map<std::string, size_t>* texLut = &storage->texLut;
    if(texLut->find(path) != texLut->end()) {
        return textures[(*texLut)[path]];
    }

    size_t* freeSlots = storage->freeSlots;

    Texture2D* tex = nullptr;
    if(storage->nfree) {
        tex = &textures[freeSlots[--storage->nfree]];
    }
    else if(storage->ntextures < MAX_STORED_TEXTURES) {
        tex = &textures[storage->ntextures];
        texLut->insert({path, storage->ntextures});
        ++storage->ntextures;
    }
    else {
        TraceLog(LOG_ERROR, "TextureStorage full - texture [%s] cannot be loaded.", path);
        return (Texture2D) {};
    }

    Texture2D loadedTexture = LoadTexture(path);
    *tex = loadedTexture;
    return *tex;
}
