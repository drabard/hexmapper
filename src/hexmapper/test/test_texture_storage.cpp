#include <stdio.h>
#include <assert.h>

#include <sstream>

#include "raylib.h"

#include "textures.h"

int main(int argc, char** argv) {
    InitWindow(800, 600, "test_texture_storage");

    // Test invalid path. 
    {
        TextureStorage texStorage{};
        Texture2D testTex = GetOrLoadTexture(&texStorage, "i/dont/exist");
        assert(!IsTextureReady(testTex));
    }

    {
        TextureStorage texStorage{};
        Texture2D testTex = GetOrLoadTexture(&texStorage, "resources/textures/test_texture0.png");
        assert(IsTextureReady(testTex));
    }

    {
        TextureStorage texStorage{};
        Texture2D testTex = GetOrLoadTexture(&texStorage, "resources/textures/test_texture0.png");
        assert(IsTextureReady(testTex));

        Texture2D testTexNew = GetOrLoadTexture(&texStorage, "resources/textures/test_texture0.png");
        assert(IsTextureReady(testTex));
        assert(testTexNew.id == testTex.id);
    }

    {
        TextureStorage texStorage{};

        // There are 200 test textures and we want to check full storage condition.
        // If this fails because MAX_STORED_TEXTURES has been increased, 
        // the test needs to be adjusted.
        assert(MAX_STORED_TEXTURES < 200 - 1);

        std::stringstream ss;
        for(size_t i = 0; i < MAX_STORED_TEXTURES; ++i) {
            ss << "resources/textures/test_texture" << i << ".png";
            Texture2D tex = GetOrLoadTexture(&texStorage, ss.str().c_str()); 
            ss.str("");
        }

        ss << "resources/textures/test_texture" << MAX_STORED_TEXTURES << ".png";
        Texture2D tex = GetOrLoadTexture(&texStorage, ss.str().c_str()); 
        assert(!IsTextureReady(tex));
    }

    return 0;
}
