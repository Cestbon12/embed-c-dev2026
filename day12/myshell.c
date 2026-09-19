#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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
            break;   // Ctrl+D 退出
        }

        // 去掉末尾换行符
        line[strcspn(line, "\n")] = '\0';

        // 空行跳过
        if (strlen(line) == 0) {
            continue;
        }

        // 3. 解析命令（按空格切分）
        int argc = 0;
        char *token = strtok(line, " ");
        while (token != NULL && argc < MAX_ARGS - 1) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;   // execvp 需要 NULL 结尾

        // 4. 内建命令：exit
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        // 5. fork + exec + wait
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            continue;
        } else if (pid == 0) {
            // 子进程：执行命令
            execvp(args[0], args);
            // 如果 execvp 返回，说明命令没找到
            perror("execvp");
            exit(1);
        } else {
            // 父进程：等待子进程
            wait(NULL);
        }
    }

    printf("bye\n");
    return 0;
}

