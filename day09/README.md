# 学生管理系统

一个用 C 语言写的命令行学生管理系统，用链表存储数据。

## 功能

- 添加学生
- 删除学生
- 修改学生
- 查找学生
- 显示所有学生
- 按成绩排序
- 保存到文件
- 从文件加载

## 编译运行

make
./app

## 清理

make clean

## 项目结构
day09/
├── include/
│ └── student.h 函数声明和结构体定义
├── src/
│ ├── student.c 函数实现
│ └── main.c 菜单和主函数
└── Makefile

text

## 技术点

- C 语言链表操作
- 文件 I/O（fopen、fprintf、fscanf、fclose）
- 多文件工程结构
- Makefile 自动化编译
- Valgrind 内存检查
