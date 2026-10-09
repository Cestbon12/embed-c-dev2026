#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFSIZE 1024

int main(void) {
    // 1. 创建 socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(1);
    }

    // 2. 设置地址和端口
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;           // IPv4
    addr.sin_addr.s_addr = INADDR_ANY;   // 监听所有网卡
    addr.sin_port = htons(PORT);         // 端口 8080

    // 3. bind
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    // 4. listen
    if (listen(server_fd, 5) < 0) {
        perror("listen");
        exit(1);
    }

    printf("服务器启动，监听端口 %d\n", PORT);

    // 5. accept 循环
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

        printf("客户端已连接\n");

        // 6. 读客户端发来的数据，回显给它
        char buf[BUFSIZE];
        ssize_t n;
        while ((n = read(client_fd, buf, BUFSIZE - 1)) > 0) {
            buf[n] = '\0';
            printf("收到: %s", buf);

            // 回显
            write(client_fd, buf, n);
        }

        printf("客户端断开\n");
        close(client_fd);
    }

    close(server_fd);
    return 0;
}
