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
        // 1. 打印提示符
        printf("myshell> ");
        fflush(stdout);

        // 2. 读取输入
        if (fgets(line, MAX_LINE, stdin) == NULL) {
            printf("\n");
            break;
        }

        // 去掉换行
        line[strcspn(line, "\n")] = '\0';

        // 空行跳过
        if (strlen(line) == 0) {
            continue;
        }

        // 3. 解析命令
        int argc = 0;
        char *token = strtok(line, " ");
        while (token != NULL && argc < MAX_ARGS - 1) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;

        // 4. 检测重定向符号
        char *infile = NULL;
        char *outfile = NULL;

        for (int i = 0; args[i] != NULL; i++) {
            if (strcmp(args[i], ">") == 0) {
                outfile = args[i + 1];
                args[i] = NULL;
                break;
            } else if (strcmp(args[i], "<") == 0) {
                infile = args[i + 1];
                args[i] = NULL;
                break;
            }
        }

        // 5. 内建命令：exit
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        // 6. 内建命令：cd
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                chdir(getenv("HOME"));
            } else {
                if (chdir(args[1]) != 0) {
                    perror("cd");
                }
            }
            continue;
        }

        // 7. 内建命令：pwd
        if (strcmp(args[0], "pwd") == 0) {
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);
            }
            continue;
        }

        // 8. fork + exec + wait
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            continue;
        } else if (pid == 0) {
            // 子进程：处理重定向
            if (infile != NULL) {
                int fd = open(infile, O_RDONLY);
                if (fd < 0) {
                    perror("open");
                    exit(1);
                }
                dup2(fd, 0);
                close(fd);
            }

            if (outfile != NULL) {
                int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) {
                    perror("open");
                    exit(1);
                }
                dup2(fd, 1);
                close(fd);
            }

            execvp(args[0], args);
            perror("execvp");
            exit(1);
        } else {
            // 父进程
            wait(NULL);
        }
    }

    printf("bye\n");
    return 0;
}
