# cpp-httpserver-basic-demo
最最基本的cpp实现httpserver服务的demo

## 使用库
- [cpp-httplib](https://github.com/yhirose/cpp-httplib.git) — 一个 C++11 单文件、头文件库，用于跨平台的 HTTP/HTTPS 请求处理。


## demo使用方法

1. 编译运行

    ```cpp
    g++ -std=c++17 -Wall -Wextra 01httpserver.cpp -o 01httpserver && "/home/weisiyuan/cpp/http_demo/"01httpserver
    ```

2. 新开一个终端，开一个Python HTTP 服务器

    ```bash
    python3 -m http.server 8012  # 启动一个简单的 HTTP 服务器，监听 8012 端口
    ```

3. 访问 http://127.0.0.1:8012/time.html，点击获取时间即可

    http://localhost:8080/hi ：返回 Hello World! 字符串。
    http://localhost:8080/get_time ：返回当前时间。


4. 也可以使用curl测试
    ```bash
    curl http://localhost:8080/get_time
    ```