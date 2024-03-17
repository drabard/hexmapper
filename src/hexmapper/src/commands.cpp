#include <stdlib.h>
#include "commands.h"

void ExecuteCommand(CommandBuffer* cmdBuf, CommandType type, CommandInput* input) {
    Command* cmd = (Command*)malloc(commandFuncs[type].size);
    cmd->type = type;
    commandFuncs[cmd->type].create(cmd, input);

    cmdBuf->end = (cmdBuf->end + 1) % MAX_COMMANDS;
    free(cmdBuf->commands[cmdBuf->end]);
    if(cmdBuf->end == cmdBuf->start) {
        cmdBuf->start = (cmdBuf->start + 1) % MAX_COMMANDS;
    }
    cmdBuf->commands[cmdBuf->end] = cmd;

    commandFuncs[cmd->type].execute(cmd);
}

void UndoCommand(CommandBuffer* cmdBuf) {
    if(cmdBuf->end == cmdBuf->start) return;

    Command* cmd = cmdBuf->commands[cmdBuf->end];
    commandFuncs[cmd->type].undo(cmd);
    cmdBuf->end = cmdBuf->end == 0 ? MAX_COMMANDS - 1 : cmdBuf->end - 1; 
}

void RedoCommand(CommandBuffer* cmdBuf) {
    size_t newEnd = (cmdBuf->end + 1) % MAX_COMMANDS;
    if(newEnd == cmdBuf->start || cmdBuf->commands[newEnd] == nullptr) return;

    cmdBuf->end = newEnd;
    Command* cmd = cmdBuf->commands[newEnd];
    commandFuncs[cmd->type].execute(cmd);
}
