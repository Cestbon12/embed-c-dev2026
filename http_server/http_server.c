#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFSIZE 4096

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
    if (listen(server_fd, 5) < 0) {
        perror("listen");
        exit(1);
    }

    printf("HTTP 服务器启动，访问 http://localhost:%d\n", PORT);

    // 6. 循环接受连接
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

        printf("\n=== 客户端已连接 ===\n");

        // 7. 读请求
        char buf[BUFSIZE];
        ssize_t n = read(client_fd, buf, BUFSIZE - 1);
        if (n <= 0) {
            close(client_fd);
            continue;
        }
        buf[n] = '\0';
        printf("收到请求：\n%s\n", buf);

        // 8. 解析请求行，提取路径
        char method[16];
        char path[256];
        char version[16];

        sscanf(buf, "%s %s %s", method, path, version);
        printf("方法: %s, 路径: %s, 版本: %s\n", method, path, version);

        // 9. 根据路径决定响应
        const char *body;
        const char *status;

        if (strcmp(path, "/") == 0) {
            status = "200 OK";
            body = "这是主页\n";
        } else if (strcmp(path, "/about") == 0) {
            status = "200 OK";
            body = "这是关于页\n";
        } else if (strcmp(path, "/hello") == 0) {
            status = "200 OK";
            body = "Hello!\n";
        } else {
            status = "404 Not Found";
            body = "404 Not Found\n";
        }

        // 10. 构造响应
        char response[1024];
        int len = snprintf(response, sizeof(response),
            "HTTP/1.1 %s\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: %zu\r\n"
            "\r\n"
            "%s",
            status, strlen(body), body);

        write(client_fd, response, len);
        close(client_fd);
        printf("=== 连接关闭 ===\n");
    }

    close(server_fd);
    return 0;
}
