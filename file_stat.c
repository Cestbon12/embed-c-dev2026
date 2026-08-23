#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("用法: %s <文件名>\n", argv[0]);
        return 1;
    }

    struct stat file_info;
    
    if (stat(argv[1], &file_info) == -1) {
        perror("获取文件信息失败");
        exit(1);
    }

    printf("文件: %s\n", argv[1]);
    printf("大小: %ld 字节\n", file_info.st_size);
    printf("权限: %o\n", file_info.st_mode & 0777);
    printf("最后修改时间: %s", ctime(&file_info.st_mtime));

    return 0;
}
