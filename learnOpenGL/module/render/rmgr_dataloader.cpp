#include "rmgr_dataloader.h"

namespace learnOpenGL {
namespace flow {

RmgrDataLoader::RmgrDataLoader(std::shared_ptr<egl::EglPipe> eglPipe) : m_eglPipe (eglPipe) {
    m_th = std::thread([&]() {
        pthread_setname_np(pthread_self(), "EglSharedContext");

        m_eglPipeDataLoader = std::make_shared<egl::EglPipe>();
        m_eglPipeDataLoader->Init();
        m_eglPipeDataLoader->AddCtx(m_eglPipe->GetCtx());
        spdlog::info("RmgrDataLoader init success");
        while (m_isRun) {
            std::shared_ptr<render::RBase> rbase;
            {
                std::unique_lock<std::mutex> lk(m_mtx);
                m_cv.wait(lk, [&] { return m_queue.size(); });
                rbase = m_queue.front();
                m_queue.pop();
            }
            if (rbase == nullptr) {
                continue;
            }
            rbase->Init();
        }
    }
    );
}

RmgrDataLoader::~RmgrDataLoader() {
    {
        std::lock_guard<std::mutex> lk(m_mtx);
        m_isRun = false;
    }
    m_cv.notify_all(); // 使用 notify_all 确保唤醒
    if(m_th.joinable()) {
        m_th.join();
    }
}

bool RmgrDataLoader::Push(std::shared_ptr<render::RBase> rbase) {
    if(rbase == nullptr) {
        spdlog::error("RmgrDataLoader::Push rbase is nullptr");
        return false;
    }
    rbase->Init();
    return true;
}

bool RmgrDataLoader::PushAsync(std::shared_ptr<render::RBase> rbase) {
    if(rbase == nullptr) {
        spdlog::error("RmgrDataLoader::PushAsync rbase is nullptr");
        return false;
    }
    std::unique_lock<std::mutex> lk(m_mtx);
    m_queue.push(rbase);
    m_cv.notify_one();
    return true;
}

bool RmgrDataLoader::Run() {
#if 0
    {
        std::unique_lock<std::mutex> lk(m_mtx);
        while (!m_queue.empty()) {
            std::shared_ptr<render::RBase> rbase = m_queue.front();
            m_queue.pop();
            if(rbase == nullptr) {
                spdlog::error("RmgrDataLoader::Run rbase is nullptr");
                continue;
            }
            rbase->Init();
        }
    }
#else
    m_cv.notify_all();
#endif
    return true;
}

}
}