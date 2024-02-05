#include "commands/select_tiles.h"

void CommandSelectTilesInit(Command*, InitCommandInput*) {
    printf("CommandCreateSelectTiles\n");
}

void CommandSelectTilesExec(Command*, ExecCommandInput*) {
    printf("CommandExecSelectTiles\n");
}

void CommandSelectTilesUndo(Command*, UndoCommandInput*) {
    printf("CommandUndoSelectTiles\n");
}

void CommandSelectTilesDestroy(Command*, DestroyCommandInput*) {
    printf("CommandDestroySelectTiles\n");
}
