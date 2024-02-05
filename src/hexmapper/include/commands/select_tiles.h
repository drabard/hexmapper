#pragma once

#include "commands.h"
#include "core.h"

#include <vector>

struct CommandSelectTiles {
    Command command;
};

Command* CommandSelectTilesCreate(void*);
void CommandSelectTilesExec(Command*, void*);
void CommandSelectTilesUndo(Command*, void*);
void CommandSelectTilesDestroy(Command*, void*);
