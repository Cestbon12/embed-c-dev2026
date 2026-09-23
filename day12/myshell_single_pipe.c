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
        int pipe_index = -1;

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
                pipe_index = i + 1;
                args[i] = NULL;
                break;
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
        if (pipe_index != -1) {
            int pipefd[2];
            if (pipe(pipefd) < 0) {
                perror("pipe");
                continue;
            }

            // 左命令
            pid_t pid1 = fork();
            if (pid1 == 0) {
                dup2(pipefd[1], 1);   // stdout → 管道写端
                close(pipefd[0]);
                close(pipefd[1]);
                execvp(args[0], args);
                perror("execvp");
                exit(1);
            }

            // 右命令
            pid_t pid2 = fork();
            if (pid2 == 0) {
                dup2(pipefd[0], 0);   // stdin → 管道读端
                close(pipefd[0]);
                close(pipefd[1]);
                execvp(args[pipe_index], &args[pipe_index]);
                perror("execvp");
                exit(1);
            }

            // 父进程
            close(pipefd[0]);
            close(pipefd[1]);
            wait(NULL);
            wait(NULL);
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
