## 简介
基于C++14和ASIO实现高并发TCP网络框架，基于[https://github.com/zhangpanyi/eddyserver](https://github.com/zhangpanyi/eddyserver/)进行改进。

## 特点
* 简单易用
* IO多线程处理，逻辑主线程处理

## 使用
```
git clone https://github.com/zhxx123
git submodule update --init --recursive
mkdir build && cd build
cmake ..
```

## 示例代码
```c++
#include <iostream>
#include <mnserver.h>

class SessionHandle : public mnserver::TCPSessionHandler
{
public:
    // 连接事件
    virtual void onConnection() override
    {
        std::cout << "on_connected" << std::endl;
    }

    // 接收消息事件
    virtual void onMessage(mnserver::NetMessage &message) override
    {
        std::cout << "on_message" << std::endl;
        send(message);
    }

    // 关闭事件
    virtual void on_closed() override
    {
        std::cout << "on_closed" << std::endl;
    }
};

mnserver::MessageFilterPointer CreateMessageFilter()
{
    return std::make_shared<mnserver::MessageFilter>();
}

mnserver::SessionHandlePointer CreateSessionHandler()
{
    return std::make_shared<SessionHandle>();
}

int main(int argc, char *argv[])
{
    mnserver::IOServiceThreadManager io(4);
    asio::ip::tcp::endpoint ep(asio::ip::address_v4::from_string("127.0.0.1"), 4400);
    mnserver::TCPServer server(ep, io, CreateSessionHandler, CreateMessageFilter);
    io.run();

    return 0;
}
```
