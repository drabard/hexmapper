#include "commands/types.h"

#include "commands/select_tiles.h"

CommandFuncs commandFuncs[COMMAND_TYPE_COUNT] = {
    {CommandSelectTilesInit, CommandSelectTilesExec, CommandSelectTilesUndo,
     CommandSelectTilesDestroy, sizeof(CommandSelectTiles)}};
