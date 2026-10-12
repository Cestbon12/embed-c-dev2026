#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "http_server.h"

// 处理一个客户端连接（线程函数）
void *handle_client(void *arg) {
    struct ClientArg *client = (struct ClientArg *)arg;
    int client_fd = client->fd;
    struct sockaddr_in client_addr = client->addr;
    free(client);

    // 获取客户端 IP
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));

    // 读请求
    char buf[BUFSIZE];
    ssize_t n = read(client_fd, buf, BUFSIZE - 1);
    if (n <= 0) {
        close(client_fd);
        return NULL;
    }
    buf[n] = '\0';

    // 解析请求行
    struct HttpRequest req;
    if (sscanf(buf, "%15s %255s %15s", req.method, req.path, req.version) != 3) {
        send_error(client_fd, "400 Bad Request", "400 Bad Request\n");
        log_access(client_ip, "?", "?", 400);
        close(client_fd);
        return NULL;
    }

    // 只支持 GET
    if (strcmp(req.method, "GET") != 0) {
        send_error(client_fd, "405 Method Not Allowed", "405\n");
        log_access(client_ip, req.method, req.path, 405);
        close(client_fd);
        return NULL;
    }

    // 访问 / 默认返回 index.html
    if (strcmp(req.path, "/") == 0) {
        strcpy(req.path, "/index.html");
    }

    // 拼文件路径
    char filepath[512];
    snprintf(filepath, sizeof(filepath), "%s%s", WWW_ROOT, req.path);

    // 判断状态码（用于日志）
    int status = 200;
    if (access(filepath, F_OK) != 0) {
        status = 404;
    }

    // 发送文件
    send_file(client_fd, filepath);
    log_access(client_ip, req.method, req.path, status);

    close(client_fd);
    return NULL;
}
