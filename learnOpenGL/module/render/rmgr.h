#pragma once
#include <mutex>
#include <atomic>

#include "rctx_win.h"
#include "rctx_data.h"
#include "rparam.h"
#include "spdlog/spdlog.h"

#include "rfunc.h"
#include "rmgr_dataloader.h"

namespace learnOpenGL {
namespace flow {

class RMgr {
public:
    RMgr(const RMgr&) = delete;
    RMgr& operator=(const RMgr&) = delete;
    static RMgr& getInstance() {
        static RMgr instance; // C++11保证局部静态变量初始化线程安全
        return instance;
    }

    bool Init();
    bool Clear(float r = 0.2f, float g = 0.2f,  float b = 0.2f, float a = 1.0f);
    bool Run();
    bool Display();

private:
    RMgr() = default;
    ~RMgr() {};
    bool Render();

private:
    std::atomic<bool> m_isInited = false;
    std::shared_ptr<egl::EglPipe> m_eglPipe;
    std::shared_ptr<RCtxWin> m_rCtxWin;
    std::shared_ptr<RCtxData> m_rCtxData;
    
    std::vector<std::shared_ptr<render::RBase>> m_taskLeft;
    std::vector<std::shared_ptr<render::RBase>> m_taskRight;
    std::vector<std::shared_ptr<render::RBase>> m_updatePrmReq;

    std::shared_ptr<RmgrDataLoader> m_rRenderDataLoader;

    std::shared_ptr<render::RBase> m_rCopyFbo;
};

}
}