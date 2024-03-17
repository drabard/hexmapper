#pragma once

struct Command;
struct CommandBuffer;

enum CommandType {
    COMMAND_SELECT_TILES = 0,
    COMMAND_TYPE_COUNT
};

struct CommandInput {
};

using CreateCommandFunc = void (*)(Command*, CommandInput*);
using ExecCommandFunc = void (*)(Command*);
using UndoCommandFunc = void (*)(Command*);
using DestroyCommandFunc = void (*)(Command*);

struct CommandFuncs {
    CreateCommandFunc create;
    ExecCommandFunc execute;
    UndoCommandFunc undo;
    DestroyCommandFunc destroy;
    size_t size;
};

extern CommandFuncs commandFuncs[COMMAND_TYPE_COUNT];
