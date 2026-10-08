# 简易 Linux Shell

用 C 语言实现的一个迷你命令行解释器。

## 功能

- 执行外部命令（ls、cat、grep 等）
- 内建命令：cd、pwd、exit、export
- 输入重定向 `<`
- 输出重定向 `>`
- 管道 `|`（支持多个）
- 后台运行 `&`
- 信号处理：Ctrl+C 只中断当前命令，不退出 Shell

## 编译运行

make
./myshell

## 清理

make clean

## 示例
