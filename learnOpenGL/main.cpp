#include <chrono>
#include <thread>
#include <iostream>

#include "rmgr.h"

#define RMgrIns learnOpenGL::flow::RMgr::getInstance()
void RenderLoop() {
    pthread_setname_np(pthread_self(), "RenderLoop");
    RMgrIns.Init();
    static int8_t fps{0};
    auto nowTmp = std::chrono::steady_clock::now();
    while (true) {
        fps++;
        auto now = std::chrono::steady_clock::now();
        if(now - nowTmp >= std::chrono::seconds(1)) {
            printf("fps: %d\n", fps);
            nowTmp = now;
            fps = 0;
        }

        RMgrIns.Clear();
        RMgrIns.Run();
        RMgrIns.Display();

        std::this_thread::sleep_until(now + std::chrono::milliseconds(20));
    }
}

int main() {
    std::thread th1(RenderLoop);
    if (th1.joinable()) th1.join();
    return 0;
}