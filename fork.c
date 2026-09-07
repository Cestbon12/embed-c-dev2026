#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork失败");
        return 1;
    } else if (pid == 0) {
        // 子进程执行的代码
        printf("我是子进程，我的PID是: %d，我父亲的PID是: %d\n", getpid(), getppid());
    } else {
        // 父进程执行的代码
        printf("我是父进程，我的PID是: %d，我儿子的PID是: %d\n", getpid(), pid);
    }

    return 0;
}
