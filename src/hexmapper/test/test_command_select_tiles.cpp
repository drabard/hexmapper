#include <cassert>

#include "commands.h"
#include "commands/select_tiles.h"

int main(int argc, char** argv) {
    CommandBuffer cmdBuf = {};

    for(size_t i = 0; i < MAX_COMMANDS*12; ++i) {
        ExecuteCommand(&cmdBuf, COMMAND_SELECT_TILES, nullptr);
        assert(cmdBuf.start < MAX_COMMANDS);
        assert(cmdBuf.end < MAX_COMMANDS);
    }
    return 0;
}
