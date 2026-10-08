#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include "myshell.h"

// Ctrl+C 处理函数：只打印换行
void sigint_handler(int sig) {
    (void)sig;
    write(1, "\n", 1);
}

int main(void) {
    signal(SIGINT, sigint_handler);

    char line[MAX_LINE];
    struct Command cmd;

    while (1) {
        printf("myshell> ");
        fflush(stdout);

        errno = 0;
        if (fgets(line, MAX_LINE, stdin) == NULL) {
            if (errno == EINTR) {
                continue;   // 被 Ctrl+C 中断，重新循环
            }
            printf("\n");
            break;          // 真正的 EOF（Ctrl+D）
        }

        if (parse_line(line, &cmd) < 0) {
            continue;       // 空行
        }

        if (handle_builtin(&cmd)) {
            continue;       // 内建命令已处理
        }

        execute_command(&cmd);
    }

    printf("bye\n");
    return 0;
}
