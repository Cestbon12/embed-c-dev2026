#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include "myshell.h"

// 在子进程里处理重定向
static void setup_redirect(struct Command *cmd) {
    if (cmd->infile != NULL) {
        int fd = open(cmd->infile, O_RDONLY);
        if (fd < 0) {
            perror("open");
            exit(1);
        }
        dup2(fd, 0);
        close(fd);
    }

    if (cmd->outfile != NULL) {
        int fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) {
            perror("open");
            exit(1);
        }
        dup2(fd, 1);
        close(fd);
    }
}

// 管道处理
static void execute_pipe(struct Command *cmd) {
    int num_cmds = cmd->pipe_count + 1;
    int pipes[MAX_ARGS][2];

    // 创建所有管道
    for (int i = 0; i < cmd->pipe_count; i++) {
        if (pipe(pipes[i]) < 0) {
            perror("pipe");
            return;
        }
    }

    // 逐个 fork 子进程
    int start = 0;
    for (int i = 0; i < num_cmds; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            signal(SIGINT, SIG_DFL);

            if (i > 0) {
                dup2(pipes[i - 1][0], 0);
            }
            if (i < cmd->pipe_count) {
                dup2(pipes[i][1], 1);
            }
            for (int j = 0; j < cmd->pipe_count; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            execvp(cmd->args[start], &cmd->args[start]);
            perror("execvp");
            exit(1);
        }
        if (i < cmd->pipe_count) {
            start = cmd->pipe_pos[i] + 1;
        }
    }

    // 父进程关闭所有管道
    for (int i = 0; i < cmd->pipe_count; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // 等所有子进程
    for (int i = 0; i < num_cmds; i++) {
        wait(NULL);
    }
}

// 普通外部命令
static void execute_simple(struct Command *cmd) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return;
    } else if (pid == 0) {
        signal(SIGINT, SIG_DFL);
        setup_redirect(cmd);
        execvp(cmd->args[0], cmd->args);
        perror("execvp");
        exit(1);
    } else {
        if (cmd->background) {
            printf("[1]%d\n", pid);
        } else {
            wait(NULL);
        }
    }
}

void execute_command(struct Command *cmd) {
    if (cmd->pipe_count > 0) {
        execute_pipe(cmd);
    } else {
        execute_simple(cmd);
    }
}
