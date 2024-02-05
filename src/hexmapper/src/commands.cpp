#include "commands.h"

Command* CreateCommand(CommandType type, InitCommandInput* input) {
    Command* cmd = (Command*)malloc(commandFuncs[type].size);
    commandFuncs[type].init(cmd, input);
    cmd->type = type;
    return cmd;
}

void ExecuteCommand(Command* command, ExecCommandInput* input) {
    commandFuncs[command->type].execute(command, input);
}

void DestroyCommand(Command* command, DestroyCommandInput* input) {
    commandFuncs[command->type].destroy(command, input);
    free(command);
}
