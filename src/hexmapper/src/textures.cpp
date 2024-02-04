#include "textures.h"

Texture2D GetOrLoadTexture(TextureStorage* storage, const char* path) {
    TextureEntry* textures = storage->textures;

    // Try cache first.
    std::unordered_map<std::string, size_t>* texLut = &storage->texLut;
    if(texLut->find(path) != texLut->end()) {
        TextureEntry* texEntry = &textures[(*texLut)[path]];
        texEntry->used = true;
        return texEntry->texture;
    }

    size_t* freeSlots = storage->freeSlots;

    TextureEntry* texEntry = nullptr;
    if(storage->nfree) {
        texEntry = &textures[freeSlots[--storage->nfree]];
    }
    else if(storage->ntextures < MAX_STORED_TEXTURES) {
        texEntry = &textures[storage->ntextures];
        texLut->insert({path, storage->ntextures});
        ++storage->ntextures;
    }
    else {
        TraceLog(LOG_ERROR, "TextureStorage full - texture [%s] cannot be loaded.", path);
        return (Texture2D) {};
    }

    texEntry->used = true;
    texEntry->texture = LoadTexture(path);
    return texEntry->texture;
}

void SweepAndEvictTextures(TextureStorage* storage) {
    for(size_t i = 0; i < storage->ntextures; ++i) {
        TextureEntry* te = &storage->textures[i];
        if(te->texture.id == 0) continue; // This texture is already in the free list.

        if(te->used) {
            te->used = false;
        } else {
            UnloadTexture(te->texture);
            *te = (TextureEntry) {};
            assert(storage->nfree < MAX_STORED_TEXTURES);
            storage->freeSlots[storage->nfree++] = i;
        }
    }
}
