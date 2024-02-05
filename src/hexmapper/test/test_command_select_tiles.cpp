#include "commands.h"
#include "commands/select_tiles.h"

int main(int argc, char** argv) {
    Command* cmd = CreateCommand(COMMAND_SELECT_TILES, nullptr);
    ExecuteCommand(cmd, nullptr);
    DestroyCommand(cmd, nullptr);
    return 0;
}
