# 简易 Linux Shell

用 C 语言实现的一个迷你命令行解释器。

## 功能

- 执行外部命令（ls、cat、grep 等）
- 内建命令：cd、pwd、exit
- 输入重定向 `<`
- 输出重定向 `>`
- 管道 `|`（支持多个）

## 编译运行

gcc -Wall -Wextra -g myshell.c -o myshell
./myshell

## 示例

myshell> ls -l
myshell> cd /tmp
myshell> ls > out.txt
myshell> cat < out.txt
myshell> ls | grep txt
myshell> ls | grep txt | wc -l
myshell> exit

## 技术点

- 进程管理：fork、execvp、wait
- 文件描述符：open、dup2、close
- 管道：pipe
- 内建命令：chdir、getcwd、getenv
