#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "http_server.h"

// 根据文件后缀返回 Content-Type
const char *get_content_type(const char *path) {
    char *ext = strrchr(path, '.');
    if (ext == NULL) return "application/octet-stream";

    if (strcmp(ext, ".html") == 0) return "text/html; charset=utf-8";
    if (strcmp(ext, ".css") == 0)  return "text/css; charset=utf-8";
    if (strcmp(ext, ".js") == 0)   return "application/javascript; charset=utf-8";
    if (strcmp(ext, ".json") == 0) return "application/json; charset=utf-8";
    if (strcmp(ext, ".png") == 0)  return "image/png";
    if (strcmp(ext, ".jpg") == 0)  return "image/jpeg";
    if (strcmp(ext, ".jpeg") == 0) return "image/jpeg";
    if (strcmp(ext, ".gif") == 0)  return "image/gif";
    if (strcmp(ext, ".ico") == 0)  return "image/x-icon";
    if (strcmp(ext, ".txt") == 0)  return "text/plain; charset=utf-8";

    return "application/octet-stream";
}

// 发送错误响应
void send_error(int client_fd, const char *status, const char *body) {
    char response[512];
    int len = snprintf(response, sizeof(response),
        "HTTP/1.1 %s\r\n"
        "Content-Type: text/plain; charset=utf-8\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
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

    struct stat st;
    if (stat(filepath, &st) < 0) {
        close(fd);
        send_error(client_fd, "404 Not Found", "404 Not Found\n");
        return;
    }

    // 如果路径是目录，返回 404
    if (S_ISDIR(st.st_mode)) {
        close(fd);
        send_error(client_fd, "404 Not Found", "404 Not Found\n");
        return;
    }

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

    char header[1024];
    int header_len = snprintf(header, sizeof(header),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %ld\r\n"
        "Connection: close\r\n"
        "\r\n",
        get_content_type(filepath), (long)st.st_size);

    write(client_fd, header, header_len);
    write(client_fd, filebuf, n);

    free(filebuf);
}
