#ifndef MYSHELL_H
#define MYSHELL_H

#define MAX_LINE 1024
#define MAX_ARGS 64

// 解析后的命令结构
struct Command {
    char *args[MAX_ARGS];     // 参数数组
    int argc;                  // 参数个数
    char *infile;              // < 后面的文件
    char *outfile;             // > 后面的文件
    int pipe_pos[MAX_ARGS];    // 管道位置
    int pipe_count;            // 管道数量
    int background;            // 是否后台运行
};

// 解析输入行，填充 Command 结构
// 返回 0 成功，-1 表示空行
int parse_line(char *line, struct Command *cmd);

// 处理内建命令，返回 1 表示已处理，0 表示不是内建命令
int handle_builtin(struct Command *cmd);

// 执行外部命令（fork + exec + wait，处理重定向和管道）
void execute_command(struct Command *cmd);

#endif
