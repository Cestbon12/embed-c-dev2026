#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("用法: %s <源文件> <目标文件>\n", argv[0]);
        return 1;
    }

    int src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1) {
        perror("打开源文件失败");
        exit(1);
    }

    int dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd == -1) {
        perror("创建目标文件失败");
        close(src_fd);
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        ssize_t total_written = 0;
        char *p = buffer;

        while (total_written < bytes_read) {
            ssize_t bytes_written = write(dst_fd, p + total_written, bytes_read - total_written);
            if (bytes_written == -1) {
                perror("写入失败");
                close(src_fd);
                close(dst_fd);
                exit(1);
            }
            total_written += bytes_written;
        }
    }

    if (bytes_read == -1) {
        perror("读取失败");
        close(src_fd);
        close(dst_fd);
        exit(1);
    }

    close(src_fd);
    close(dst_fd);
    printf("文件复制成功!\n");
    return 0;
}
