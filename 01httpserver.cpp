#include "httplib.h"
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

int main() {
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

    // 启动服务器
    svr.listen("0.0.0.0", 8080);

    return 0;
}
