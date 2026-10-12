#include <stdio.h>
#include <time.h>
#include "http_server.h"

// 打印访问日志
void log_access(const char *client_ip, const char *method,
                const char *path, int status) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    char timebuf[64];
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tm_info);

    printf("[%s] %s \"%s %s\" %d\n",
           timebuf, client_ip, method, path, status);
}
