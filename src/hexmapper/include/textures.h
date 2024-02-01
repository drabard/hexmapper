#include <unordered_map>
#include <string>

struct TextureHandle {
    bool used;
    bool resident;
    Texture2D loadedTexture;
};

struct TextureStorage {
    std::vector<TextureState> textures;
    std::unordered_map<std::string, size_t> pathToTexState;
};

Texture2D GetOrLoadTexture(TextureStorage*, std::string* path);
