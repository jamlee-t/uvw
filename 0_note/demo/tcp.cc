#define UVW_AS_LIB
#include <iostream>
#include <memory>

#include <uvw.hpp>

void listen(uvw::Loop &loop) {
    // 创建 TcpHandle 资源
    std::shared_ptr<uvw::TCPHandle> tcp = loop.resource<uvw::TCPHandle>();

    // 监听 listen 事件
    tcp->once<uvw::ListenEvent>([](const uvw::ListenEvent &, uvw::TCPHandle &srv) {
        std::shared_ptr<uvw::TCPHandle> client = srv.loop().resource<uvw::TCPHandle>();

        client->on<uvw::CloseEvent>([ptr = srv.shared_from_this()](const uvw::CloseEvent &, uvw::TCPHandle &) { ptr->close(); });
        client->on<uvw::EndEvent>([](const uvw::EndEvent &, uvw::TCPHandle &client) { client.close(); });

        srv.accept(*client);
        client->read();
    });

    tcp->bind("127.0.0.1", 4242);
    tcp->listen();
}

void conn(uvw::Loop &loop) {
    // 创建 TcpHandle 对象。传入了模板参数 uvw::TCPHandle
    auto tcp = loop.resource<uvw::TCPHandle>();

    // 监听事件 Error。所以 resource 也继承了 Emitter 类
    tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent &, uvw::TCPHandle &) { /* handle errors */ });

    // 执行 1 次连接事件
    tcp->once<uvw::ConnectEvent>([](const uvw::ConnectEvent &, uvw::TCPHandle &tcp) {
        auto dataWrite = std::unique_ptr<char[]>(new char[2]{ 'b', 'c' });
        tcp.write(std::move(dataWrite), 2);
        tcp.close();
    });

    tcp->connect(std::string{"127.0.0.1"}, 4242);
}

int main() {
    // 创建 Loop 类对象实例。
    auto loop = uvw::Loop::getDefault();
    std::cout << loop->alive() << std::endl;
    // listen(*loop);
    // conn(*loop);
    loop->run();
}