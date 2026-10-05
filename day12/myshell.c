#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

int main(void) {
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    while (1) {
        printf("myshell> ");
        fflush(stdout);

        if (fgets(line, MAX_LINE, stdin) == NULL) {
            printf("\n");
            break;
        }

        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0) continue;

        // 解析命令
         int argc = 0;
        char *token = strtok(line, " ");
        while (token != NULL && argc < MAX_ARGS - 1) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;

        // 检测重定向和管道
        char *infile = NULL;
        char *outfile = NULL;
        int pipe_pos[MAX_ARGS];
        int pipe_count = 0;

        for (int i = 0; args[i] != NULL; i++) {
            if (strcmp(args[i], ">") == 0) {
                outfile = args[i + 1];
                args[i] = NULL;
                break;
            } else if (strcmp(args[i], "<") == 0) {
                infile = args[i + 1];
                args[i] = NULL;
                break;
            } else if (strcmp(args[i], "|") == 0) {
                pipe_pos[pipe_count++] = i;
                args[i] = NULL;
            }
        }

        // 内建命令
        if (strcmp(args[0], "exit") == 0) break;

        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                chdir(getenv("HOME"));
            } else {
                if (chdir(args[1]) != 0) perror("cd");
            }
            continue;
        }

        if (strcmp(args[0], "pwd") == 0) {
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);
            }
            continue;
        }

        // 管道处理
        if (pipe_count > 0) {
            int num_cmds = pipe_count + 1;
            int pipes[MAX_ARGS][2];

            // 1. 创建所有管道
            for (int i = 0; i < pipe_count; i++) {
                if (pipe(pipes[i]) < 0) {
                    perror("pipe");
                }
            }

            // 2. 逐个 fork 子进程
            int start = 0;
            for (int i = 0; i < num_cmds; i++) {
                pid_t pid = fork();
                if (pid == 0) {
                    if (i > 0) {
                        dup2(pipes[i - 1][0], 0);
                    }
                    if (i < pipe_count) {
                        dup2(pipes[i][1], 1);
                    }
                    for (int j = 0; j < pipe_count; j++) {
                        close(pipes[j][0]);
                        close(pipes[j][1]);
                    }
                    execvp(args[start], &args[start]);
                    perror("execvp");
                    exit(1);
                }
                if (i < pipe_count) {
                    start = pipe_pos[i] + 1;
                }
            }

            // 3. 父进程关闭所有管道
            for (int i = 0; i < pipe_count; i++) {
                close(pipes[i][0]);
                close(pipes[i][1]);
            }

            // 4. 等所有子进程
            for (int i = 0; i < num_cmds; i++) {
                wait(NULL);
            }
            continue;
        }

        // 普通外部命令
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            continue;
        } else if (pid == 0) {
            if (infile != NULL) {
                int fd = open(infile, O_RDONLY);
                if (fd < 0) { perror("open"); exit(1); }
                dup2(fd, 0);
                close(fd);
            }
            if (outfile != NULL) {
                int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) { perror("open"); exit(1); }
                dup2(fd, 1);
                close(fd);
            }
            execvp(args[0], args);
            perror("execvp");
            exit(1);
        } else {
            wait(NULL);
        }
    }

    printf("bye\n");
    return 0;
}
