#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork失败");
        return 1;
    } else if (pid == 0) {
        // 子进程
        printf("子进程开始，PID: %d，我将睡眠2秒\n", getpid());
        sleep(2);
        printf("子进程结束\n");
        exit(0);
    } else {
        // 父进程
        printf("父进程等待子进程结束...\n");
        int status;
        pid_t child_pid = wait(&status);  // 父进程阻塞，直到子进程结束
        printf("父进程检测到子进程 %d 已结束，退出状态: %d\n", child_pid, WEXITSTATUS(status));
    }

    return 0;
}
