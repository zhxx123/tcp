#include <iostream>
#include <mnserver.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
class SessionClientHandle : public mnserver::TCPSessionHandler
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
        std::cout << "onMessage" << std::endl;
        std::string msg=message.read_string();
        std::cout<<"recv: "<<msg<<std::endl;
        sendMsg();
    }

    // 关闭事件
    virtual void onClosed() override
    {
        std::cout << "on_closed" << std::endl;
    }
    void sendMsg()
    {
        std::string msg;
        std::cout<<"input:\n>";
        std::cin>>msg;
        mnserver::NetMessage message(msg.c_str(),msg.size());
        send(message);
    }
};

mnserver::MessageFilterPointer CreateMessageFilter()
{
    return std::make_shared<mnserver::MessageFilter>();
}

mnserver::SessionHandlePointer CreateSessionHandler()
{
    return std::make_shared<SessionClientHandle>();
}

int main(int argc, char *argv[])
{
    std::string ip="127.0.0.1";
    if(argc>1) ip="10.0.0.2";
    mnserver::IOServiceThreadManager io(1);
    asio::ip::tcp::endpoint ep(asio::ip::address_v4::from_string(ip), 4400);
    mnserver::TCPClient client(io, CreateSessionHandler, CreateMessageFilter);
    const std::function<void(asio::error_code)> cb;
    client.async_connect(ep,cb);
    io.run();

    return 0;
}

