#pragma once
#include <thread>
#include <mutex>
#include <queue>

#include "gl_egl.h"
#include "rfunc.h"


namespace learnOpenGL {
namespace flow {

class RmgrDataLoader {
private:
    std::thread m_th;
    std::mutex m_mtx;
    std::condition_variable m_cv;

    std::queue<std::shared_ptr<render::RBase>> m_queue;
    std::shared_ptr<egl::EglPipe> m_eglPipe;
    std::shared_ptr<egl::EglPipe> m_eglPipeDataLoader;

    bool m_isRun = true;

public:
    RmgrDataLoader(std::shared_ptr<egl::EglPipe> eglPipe);
    ~RmgrDataLoader();

    bool Run();
    bool Push(std::shared_ptr<render::RBase> rbase);
    bool PushAsync(std::shared_ptr<render::RBase> rbase);
};

}
}