#include <iostream>
#include <memory>
#include <uvw.hpp>

int main() {
    auto loop = uvw::Loop::getDefault();
    auto handle1 = loop->resource<uvw::IdleHandle>();
    bool checkIdleEvent = false;

    // 调用回调函数
    handle1->on<uvw::IdleEvent>([&checkIdleEvent](const auto &, auto &hndl) {
        std::cout << "idle1 hello world" << std::endl;
        hndl.stop();
        hndl.close();
    });
    handle1->start();

    auto handle2 = loop->resource<uvw::IdleHandle>();
    handle2->on<uvw::IdleEvent>([&checkIdleEvent](const auto &, auto &hndl) {
        std::cout << "idle2 hello world" << std::endl;
        hndl.stop();
        hndl.close();
    });
    handle2->start();

    loop->run();
}