#include <stdio.h>
#include <string.h>
#include "myshell.h"

int parse_line(char *line, struct Command *cmd) {
    // 初始化
    cmd->argc = 0;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->pipe_count = 0;
    cmd->background = 0;

    // 去掉换行
    line[strcspn(line, "\n")] = '\0';

    // 空行
    if (strlen(line) == 0) {
        return -1;
    }

    // 按空格切分
    char *token = strtok(line, " ");
    while (token != NULL && cmd->argc < MAX_ARGS - 1) {
        cmd->args[cmd->argc++] = token;
        token = strtok(NULL, " ");
    }
    cmd->args[cmd->argc] = NULL;

    // 检测 > < | &
    for (int i = 0; cmd->args[i] != NULL; i++) {
        if (strcmp(cmd->args[i], ">") == 0) {
            cmd->outfile = cmd->args[i + 1];
            cmd->args[i] = NULL;
            break;
        } else if (strcmp(cmd->args[i], "<") == 0) {
            cmd->infile = cmd->args[i + 1];
            cmd->args[i] = NULL;
            break;
        } else if (strcmp(cmd->args[i], "|") == 0) {
            cmd->pipe_pos[cmd->pipe_count++] = i;
            cmd->args[i] = NULL;
        } else if (strcmp(cmd->args[i], "&") == 0) {
            cmd->background = 1;
            cmd->args[i] = NULL;
            break;
        }
    }

    return 0;
}
