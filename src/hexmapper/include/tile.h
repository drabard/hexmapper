#pragma once

struct Tile {
    // Multiple layers have to be possible.
    std::vector<ImageHandle> images;
    std::string note;
};
