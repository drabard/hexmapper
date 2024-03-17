#include "commands/select_tiles.h"

void CommandSelectTilesCreate(Command* cmd, CommandInput* input) {
}

void CommandSelectTilesExec(Command* cmd) {
    printf("CommandExecSelectTiles\n");
}

void CommandSelectTilesUndo(Command*) {
    printf("CommandUndoSelectTiles\n");
}

void CommandSelectTilesDestroy(Command*) {
    printf("CommandDestroySelectTiles\n");
}
