#include <iostream>
#include "mnserver.h"
#include <cstring>

class SessionServerHandle : public mnserver::TCPSessionHandler
{
public:
    // 连接事件
    virtual void onConnection() override
    {
        std::cout << "on_connected" << std::endl;
        std::string hello="hello "+remote_endpoint().address().to_string();
        mnserver::NetMessage message(hello.c_str(),hello.size());
        send(message);
    }

    // 接收消息事件
    virtual void onMessage(mnserver::NetMessage &message) override
    {
        std::cout << "onMessage" << std::endl;
        std::string msg=message.read_string();
        std::cout<<"server recv: "<<msg<<" "<<msg.size()<<std::endl;
        mnserver::NetMessage messages(msg.c_str(),msg.size());
        send(messages);
    }

    // 关闭事件
    virtual void onClosed() override
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
    return std::make_shared<SessionServerHandle>();
}

int main(int argc, char *argv[])
{
    mnserver::IOServiceThreadManager io(1);
    asio::ip::tcp::endpoint ep(asio::ip::address_v4(), 4400);
    mnserver::TCPServer server(ep, io, CreateSessionHandler, CreateMessageFilter);
    io.run();

    return 0;
}

