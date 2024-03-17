#pragma once

#include "core.h"
#include "commands/types.h"

constexpr size_t MAX_COMMANDS = 8;

struct Command {
    CommandType type;
};

struct CommandBuffer {
    Command* commands[MAX_COMMANDS];
    size_t start;
    size_t end;
};

void ExecuteCommand(CommandBuffer*, CommandType, CommandInput*);
void RedoCommand(CommandBuffer*);
void UndoCommand(CommandBuffer*);
