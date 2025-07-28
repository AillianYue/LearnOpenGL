#include "rmgr.h"

namespace learnOpenGL {
namespace flow {

#define RPrmIns learnOpenGL::config::RParam::GetInstance()
#define RCfgIns learnOpenGL::config::RConfig::GetInstance()

bool RMgr::Init() {
    do {
        if(m_isInited) {
            spdlog::error("RMgr::Init() is already init");
            return true;
        }

        RPrmIns.Init();
        // const auto& WinPrm = RCfgIns.GetWinParam();
        const auto& WinPrm = RPrmIns.GetWinParam(); // 先用这个死值，后面在用上面的

        int w = WinPrm.WinSize.w;
        int h = WinPrm.WinSize.h;

        m_eglPipe = std::make_shared<egl::EglPipe>();
        m_eglPipe->Init();
        m_eglPipe->AddCtx();

        m_rRenderDataLoader = std::make_shared<RmgrDataLoader>(m_eglPipe); // 暂时先注释
        m_eglPipe->AddWin(w, h);
        m_eglPipe->AddSfc(egl::GL_SFC_Type::WINDOW_SURFACE);

        m_rCtxData = std::make_shared<RCtxData>(m_eglPipe);
        m_rCtxData->Init();
        m_rCtxWin = std::make_shared<RCtxWin>(m_eglPipe);
        m_rCtxWin->Init();

        // 创建渲染任务
        // auto rRenderDemo = std::make_shared<render::RenderDemo>("RenderDemo", *m_rCtxData, *m_rCtxWin);
        auto rCar2D      = std::make_shared<render::RenderCar2D>("RenderCar2D", *m_rCtxData, *m_rCtxWin);
        
        m_rCopyFbo = std::make_shared<render::RCopyFbo>("RCopyFbo",*m_rCtxData, *m_rCtxWin);

        // 添加到队列进行初始化
        // m_rRenderDataLoader->PushAsync(); // 异步
        // m_rRenderDataLoader->Run();
        // m_rRenderDataLoader->Push(rRenderDemo);
        m_rRenderDataLoader->Push(rCar2D);

        m_rRenderDataLoader->Push(m_rCopyFbo);

        // 添加任务到执行队列
        // m_taskLeft.emplace_back(rRenderDemo);
        m_taskLeft.emplace_back(rCar2D);

        // m_taskRight.emplace_back();

        // 添加数据更新
        // m_updatePrmReq.emplace_back(rRenderDemo);

        m_isInited = true;
        spdlog::info("RMgr::Init() success");
        return true;
    } while(0);
    spdlog::error("RMgr::Init() failed");
    return false;
}

bool RMgr::Run() {
    if(!m_isInited) {
        spdlog::error("RMgr::Run() is already init");
        return false;
    }
    // 数据更新
    if(!m_rCtxData->Update()) {
        spdlog::error("RMgr::Run() Update failed");
        return false;
    }

    // 消息更新
    // spdlog::info("RMgr::Run() update message TODO");

    // 渲染
    if(!Render()) {
        spdlog::error("RMgr::Run() Render is failed");
        return false;
    }
    // spdlog::info("RMgr::Run() success");
    return true;
}

bool RMgr::Display() {
    if(!m_isInited) {
        spdlog::error("RMgr::Display() is already init");
        return false;
    }
    m_rCtxWin->BindFboWin(FBO_ID::FBO_DEFAULT);
    m_rCtxWin->SwapWin();
    // spdlog::info("RMgr::Display() success");
    return true;
}


bool RMgr::Clear(float r, float g, float b, float a) {
    if(!m_isInited) {
        spdlog::error("RMgr::Clear() is not inited.");
        return false;
    }
    if(!m_rCtxWin->Update()) {
        spdlog::error("RMgr::Clear() is failed.");
        return false;
    }

    m_rCtxWin->BindFboWin(FBO_ID::FBO_DEFAULT);
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_rCtxWin->BindFboWin(FBO_ID::FBO_LEFT);
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_rCtxWin->BindFboWin(FBO_ID::FBO_RIGHT);
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    return true;
}

bool RMgr::Render() {
    if(!m_isInited) {
        spdlog::error("RMgr::Render() is failed");
        return false;
    }
    // 渲染
    {
        m_rCtxWin->BindFboWin(FBO_ID::FBO_LEFT);
        const auto& WinPrm = RPrmIns.GetWinParam(); // 先用这个死值，后面在用上面的
        int x = WinPrm.AreaLeft.x;
        int y = WinPrm.AreaLeft.y;
        int w = WinPrm.AreaLeft.w;
        int h = WinPrm.AreaLeft.h;
        for(auto& task : m_taskLeft) {
            task->Draw(x, y, w, h);
        }
    }
    // 渲染
    {
        m_rCtxWin->BindFboWin(FBO_ID::FBO_RIGHT);
        const auto& WinPrm = RPrmIns.GetWinParam(); // 先用这个死值，后面在用上面的
        int x = WinPrm.AreaRight.x;
        int y = WinPrm.AreaRight.y;
        int w = WinPrm.AreaRight.w;
        int h = WinPrm.AreaRight.h;
        for(auto& task : m_taskRight) {
            task->Draw(x, y, w, h);
        }
    }
    {
        m_rCtxWin->BindFboWin(FBO_ID::FBO_DEFAULT);
        const auto& WinPrm = RPrmIns.GetWinParam(); // 先用这个死值，后面在用上面的
        int x = WinPrm.WinSize.x;
        int y = WinPrm.WinSize.y;
        int w = WinPrm.WinSize.w;
        int h = WinPrm.WinSize.h;
        m_rCopyFbo->Draw(x, y, w, h);
    }



    return true;
}


}
}