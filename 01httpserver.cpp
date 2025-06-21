#include "httplib.h"
#include <thread>
#include <string>
#include <ctime>

// 创建 HTTP 服务器对象
httplib::Server svr;

// 示例函数，返回当前时间
std::string get_current_time() {
    std::time_t t = std::time(nullptr);
    std::tm* tm_ptr = std::localtime(&t);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S\n", tm_ptr);
    printf("Current time: %s\n", buffer);
    return std::string(buffer);
}

bool server() {
    // 设置跨域头，允许所有来源访问
    svr.set_default_headers({{"Access-Control-Allow-Origin", "*"}}); // 允许所有域名跨域访问

    // 设置 GET 请求的处理方式
    svr.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    // 新的路由处理函数，返回当前时间
    svr.Get("/get_time", [](const httplib::Request &, httplib::Response &res) {
        std::string time = get_current_time();
        res.set_content(time, "text/plain");
    });

    for (int port = 10000; port < 65535; port++) {
        if (svr.bind_to_port("localhost", port)) {
            std::cout << "Server started on port " << port << std::endl;
            return svr.listen_after_bind();
        } else {
            std::cout << "Failed to bind to port " << port << std::endl;
        }
    }
    throw std::runtime_error("Failed to start server");
    return false;
}

void start_server() {
    static std::thread server_thread(server);
    server_thread.detach();
}


int main() {
    start_server();
    printf("Server started.\n");
    int count = 0;
    while (true) {
        printf("Count: %d ", count++);
        printf("Waiting for requests...\n");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}