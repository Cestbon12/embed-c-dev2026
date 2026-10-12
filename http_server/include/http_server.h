#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H
#include <netinet/in.h>
#define PORT 8080
#define BUFSIZE 4096
#define WWW_ROOT "./www"

// HTTP 请求信息
struct HttpRequest {
    char method[16];      // GET、POST 等
    char path[256];       // 请求路径
    char version[16];     // HTTP/1.1
};

// 传给线程的参数
struct ClientArg {
    int fd;                        // 客户端 fd
    struct sockaddr_in addr;       // 客户端地址
};

// ============ handler.c ============
// 处理一个客户端连接（线程函数）
void *handle_client(void *arg);

// ============ file.c ============
// 根据文件后缀返回 Content-Type
const char *get_content_type(const char *path);

// 发送错误响应（404 等）
void send_error(int client_fd, const char *status, const char *body);

// 发送文件内容
void send_file(int client_fd, const char *filepath);

// ============ log.c ============
// 打印访问日志
void log_access(const char *client_ip, const char *method,
                const char *path, int status);

#endif
