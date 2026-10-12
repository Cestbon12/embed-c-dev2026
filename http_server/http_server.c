#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
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

// 发送错误响应
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

    struct stat st;
    if (stat(filepath, &st) < 0) {
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
        "\r\n",
        get_content_type(filepath), (long)st.st_size);

    write(client_fd, header, header_len);
    write(client_fd, filebuf, n);

    free(filebuf);
}

// 线程函数：处理一个客户端
void *handle_client(void *arg) {
    int client_fd = *(int *)arg;
    free(arg);

    char buf[BUFSIZE];
    ssize_t n = read(client_fd, buf, BUFSIZE - 1);
    if (n <= 0) {
        close(client_fd);
        return NULL;
    }
    buf[n] = '\0';

    char method[16], path[256], version[16];
    sscanf(buf, "%s %s %s", method, path, version);

    printf("请求: %s %s\n", method, path);

    if (strcmp(path, "/") == 0) {
        strcpy(path, "/index.html");
    }

    char filepath[512];
    snprintf(filepath, sizeof(filepath), "%s%s", WWW_ROOT, path);

    send_file(client_fd, filepath);
    close(client_fd);
    return NULL;
}

int main(void) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(1);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(server_fd, 5) < 0) {
        perror("listen");
        exit(1);
    }

    printf("HTTP 服务器启动，访问 http://localhost:%d\n", PORT);

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

        // 把 client_fd 复制到堆上
        int *pclient = malloc(sizeof(int));
        *pclient = client_fd;

        // 创建线程处理
        pthread_t tid;
        if (pthread_create(&tid, NULL, handle_client, pclient) != 0) {
            perror("pthread_create");
            free(pclient);
            close(client_fd);
            continue;
        }

        // 线程自动回收
        pthread_detach(tid);
    }

    close(server_fd);
    return 0;
}
