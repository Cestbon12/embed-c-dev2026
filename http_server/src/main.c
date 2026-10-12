#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "http_server.h"

int main(void) {
    // 1. 创建 socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(1);
    }

    // 2. 允许端口重用
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 3. 设置地址
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    // 4. bind
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    // 5. listen
    if (listen(server_fd, 10) < 0) {
        perror("listen");
        exit(1);
    }

    printf("========================================\n");
    printf("  HTTP Server 已启动\n");
    printf("  访问: http://localhost:%d\n", PORT);
    printf("  静态文件目录: %s\n", WWW_ROOT);
    printf("========================================\n");

    // 6. 循环 accept
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        int client_fd = accept(server_fd,
                               (struct sockaddr *)&client_addr,
                               &client_len);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        // 打包参数传给线程
        struct ClientArg *arg = malloc(sizeof(struct ClientArg));
        if (arg == NULL) {
            perror("malloc");
            close(client_fd);
            continue;
        }
        arg->fd = client_fd;
        arg->addr = client_addr;

        // 创建线程
        pthread_t tid;
        if (pthread_create(&tid, NULL, handle_client, arg) != 0) {
            perror("pthread_create");
            free(arg);
            close(client_fd);
            continue;
        }

        // 线程自动回收
        pthread_detach(tid);
    }

    close(server_fd);
    return 0;
}
