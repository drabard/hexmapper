#pragma once

#include <filesystem>
#include <unordered_set>
#include <string>
#include <vector>

#include "raylib.h"

struct FsNode {
    std::vector<FsNode> dirs;
    std::vector<FsNode> files;
    std::string path;
    bool isDirectory;
};

FsNode ParseDirectory(const char* basePath);
