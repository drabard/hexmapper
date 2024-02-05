#pragma once

struct Command;
enum CommandType {
    COMMAND_SELECT_TILES = 0,
    COMMAND_TYPE_COUNT
};

struct InitCommandInput {
};

struct ExecCommandInput {
};

struct UndoCommandInput {
};

struct DestroyCommandInput {
};

using InitCommandFunc = void (*)(Command*, InitCommandInput*);
using ExecCommandFunc = void (*)(Command*, ExecCommandInput*);
using UndoCommandFunc = void (*)(Command*, UndoCommandInput*);
using DestroyCommandFunc = void (*)(Command*, DestroyCommandInput*);

struct CommandFuncs {
    InitCommandFunc init;
    ExecCommandFunc execute;
    UndoCommandFunc undo;
    DestroyCommandFunc destroy;
    size_t size;
};

extern CommandFuncs commandFuncs[COMMAND_TYPE_COUNT];
