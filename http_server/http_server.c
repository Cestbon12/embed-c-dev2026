#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFSIZE 4096
#define WWW_ROOT "./www"

// 根据文件后缀返回 Content-Type
const char *get_content_type(const char *path) {
    char *ext = strrchr(path, '.');
    if (ext == NULL) return "application/octet-stream";

    if (strcmp(ext, ".html") == 0) return "text/html; charset=utf-8";
    if (strcmp(ext, ".css") == 0)  return "text/css; charset=utf-8";
    if (strcmp(ext, ".js") == 0)   return "application/javascript; charset=utf-8";
    if (strcmp(ext, ".png") == 0)  return "image/png";
    if (strcmp(ext, ".jpg") == 0)  return "image/jpeg";
    if (strcmp(ext, ".jpeg") == 0) return "image/jpeg";
    if (strcmp(ext, ".gif") == 0)  return "image/gif";
    if (strcmp(ext, ".txt") == 0)  return "text/plain; charset=utf-8";

    return "application/octet-stream";
}

// 发送错误响应（404 等）
void send_error(int client_fd, const char *status, const char *body) {
    char response[512];
    int len = snprintf(response, sizeof(response),
        "HTTP/1.1 %s\r\n"
        "Content-Type: text/plain; charset=utf-8\r\n"
        "Content-Length: %zu\r\n"
        "\r\n"
        "%s",
        status, strlen(body), body);
    write(client_fd, response, len);
}

// 发送文件内容
void send_file(int client_fd, const char *filepath) {
    int fd = open(filepath, O_RDONLY);
    if (fd < 0) {
        send_error(client_fd, "404 Not Found", "404 Not Found\n");
        return;
    }

    // 获取文件大小
    struct stat st;
    if (stat(filepath, &st) < 0) {
        close(fd);
        send_error(client_fd, "404 Not Found", "404 Not Found\n");
        return;
    }

    // 分配缓冲区读文件
    char *filebuf = malloc(st.st_size);
    if (filebuf == NULL) {
        close(fd);
        send_error(client_fd, "500 Internal Server Error", "500\n");
        return;
    }

    ssize_t n = read(fd, filebuf, st.st_size);
    close(fd);
    if (n < 0) {
        free(filebuf);
        send_error(client_fd, "500 Internal Server Error", "500\n");
        return;
    }

    // 构造响应头
    char header[1024];
    int header_len = snprintf(header, sizeof(header),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %ld\r\n"
        "\r\n",
        get_content_type(filepath), (long)st.st_size);

    // 先发头，再发文件内容
    write(client_fd, header, header_len);
    write(client_fd, filebuf, n);

    free(filebuf);
}

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

        // 7. 读请求
        char buf[BUFSIZE];
        ssize_t n = read(client_fd, buf, BUFSIZE - 1);
        if (n <= 0) {
            close(client_fd);
            continue;
        }
        buf[n] = '\0';

        // 8. 解析请求行
        char method[16];
        char path[256];
        char version[16];
        sscanf(buf, "%s %s %s", method, path, version);

        printf("请求: %s %s\n", method, path);

        // 9. 路径处理
        // 访问 "/" 时默认返回 index.html
        if (strcmp(path, "/") == 0) {
            strcpy(path, "/index.html");
        }

        // 拼成实际文件路径
        char filepath[512];
        snprintf(filepath, sizeof(filepath), "%s%s", WWW_ROOT, path);

        printf("文件路径: %s\n", filepath);

        // 10. 发送文件
        send_file(client_fd, filepath);

        close(client_fd);
    }

    close(server_fd);
    return 0;
}
