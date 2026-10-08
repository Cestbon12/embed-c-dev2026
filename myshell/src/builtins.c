#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "myshell.h"

// 返回 1 表示已处理，0 表示不是内建命令
int handle_builtin(struct Command *cmd) {
    if (strcmp(cmd->args[0], "exit") == 0) {
        exit(0);
    }

    if (strcmp(cmd->args[0], "cd") == 0) {
        if (cmd->args[1] == NULL) {
            chdir(getenv("HOME"));
        } else {
            if (chdir(cmd->args[1]) != 0) {
                perror("cd");
            }
        }
        return 1;
    }

    if (strcmp(cmd->args[0], "pwd") == 0) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        }
        return 1;
    }

    if (strcmp(cmd->args[0], "export") == 0) {
        if (cmd->args[1] == NULL) {
            printf("用法: export NAME=value\n");
            return 1;
        }

        char *eq = strchr(cmd->args[1], '=');
        if (eq == NULL) {
            printf("格式错误，应为 NAME=value\n");
            return 1;
        }

        *eq = '\0';
        char *name = cmd->args[1];
        char *value = eq + 1;

        if (setenv(name, value, 1) != 0) {
            perror("setenv");
        }
        return 1;
    }

    return 0;
}
