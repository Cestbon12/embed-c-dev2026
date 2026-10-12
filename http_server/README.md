# HTTP Server

用 C 语言实现的多线程 HTTP 服务器。

## 功能

- 静态文件服务（HTML、CSS、JS、JSON、图片、文本等）
- 自动根据文件后缀识别 Content-Type
- 多线程并发处理客户端请求
- 访问日志（时间、客户端 IP、请求方法、路径、状态码）
- 支持 HTTP 状态码：200、400、404、405、500
- UTF-8 编码支持

## 编译

make

## 运行

./http_server

然后访问 http://localhost:8080

## 项目结构

