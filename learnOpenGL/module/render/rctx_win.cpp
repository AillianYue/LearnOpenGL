#include "rctx_win.h"

namespace learnOpenGL {
namespace flow {

bool RCtxWin::Init() {
    m_fboTex.resize(static_cast<int8_t>(FBO_ID::FBO_SIZE));
    m_fboWin.resize(static_cast<int8_t>(FBO_ID::FBO_SIZE));
    // TODO: Get Win Size and Scale
    const auto& winPrm = learnOpenGL::config::RParam::GetInstance().GetWinParam();
    {
        int w = winPrm.AreaLeft.w;
        int h = winPrm.AreaLeft.h;
        m_fboTex[static_cast<int8_t>(FBO_ID::FBO_LEFT)] = std::make_shared<opengl::FrameBuffer>(w, h);
    }
    {
        int w = winPrm.AreaRight.w;
        int h = winPrm.AreaRight.h;
        m_fboTex[static_cast<int8_t>(FBO_ID::FBO_RIGHT)] = std::make_shared<opengl::FrameBuffer>(w, h);
    }
    {
        // int w = 0;
        // int h = 0;
        m_fboTex[0] = nullptr;
        // m_fboWin[static_cast<int8_t>(FBO_ID::FBO_DEFAULT)] = std::make_shared<opengl::FrameBuffer>(w, h);
        // m_fboWin[static_cast<int8_t>(FBO_ID::FBO_LEFT)] = std::make_shared<opengl::FrameBuffer>(w, h);
        // m_fboWin[static_cast<int8_t>(FBO_ID::FBO_RIGHT)] = std::make_shared<opengl::FrameBuffer>(w, h);

    }
    spdlog::info("RCtxWin::Init() success");
    return true;
}

bool RCtxWin::Update() {
    // TODO: Update 
    return true;
}

bool RCtxWin::SwapWin() {
    m_eglPipe->EglSwap();
    return true;
}

// uint32_t RCtxWin::BindWin(bool update)
// {
//     static uint32_t s_winFboCnt = 0;
//     uint32_t winFboCur = s_winFboCnt;
//     s_winFboCnt = (update)? (s_winFboCnt + 1) % static_cast<uint32_t>(FBO_ID::FBO_SIZE) : s_winFboCnt;

//     if(winFboCur < 0 || winFboCur >= static_cast<uint32_t>(FBO_ID::FBO_SIZE)) {
//         spdlog::error("RCtxWin::BindWin() Invalid FBO_ID");
//         return 0xFFFFFFFF;
//     }
//     m_fboWin[winFboCur]->Bind();
//     return m_fboWin[winFboCur]->GetTexId();
// }

bool RCtxWin::BindFboWin(FBO_ID id)
{
    if(static_cast<int8_t>(id) < 0 || static_cast<int8_t>(id) >= static_cast<int8_t>(FBO_ID::FBO_SIZE)) {
        spdlog::error("RCtxWin::BindFboWin() Invalid FBO_ID");
        return 0xFFFFFFFF;
    }
    if(static_cast<int8_t>(id) == 0) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return true;
    }
    m_fboTex[static_cast<int8_t>(id)]->Bind();
    return true;
}

// uint32_t RCtxWin::SetFboTex(FBO_ID id) {
//     if(static_cast<int8_t>(id) < 0 || static_cast<int8_t>(id) >= static_cast<int8_t>(FBO_ID::FBO_SIZE)) {
//         spdlog::error("RCtxWin::SetFboTex() Invalid FBO_ID");
//         return 0xFFFFFFFF;
//     }
//     m_fboTex[static_cast<int8_t>(id)]->GetTexId();
//     return 0;
// }



// uint32_t RCtxWin::GetFboWin(FBO_ID id) {
//     if(static_cast<int8_t>(id) < 0 || static_cast<int8_t>(id) >= static_cast<int8_t>(FBO_ID::FBO_SIZE)) {
//         spdlog::error("RCtxWin::GetFboWin() Invalid FBO_ID");
//         return 0xFFFFFFFF;
//     }
//     return m_fboWin[static_cast<int8_t>(id)]->GetFboId(); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// }

uint32_t RCtxWin::GetFboTex(FBO_ID id) {
    if(static_cast<int8_t>(id) < 0 || static_cast<int8_t>(id) >= static_cast<int8_t>(FBO_ID::FBO_SIZE)) {
        spdlog::error("RCtxWin::GetFboTex() Invalid FBO_ID");
        return 0xFFFFFFFF;
    }
    return m_fboTex[static_cast<int8_t>(id)]->GetTexId();
}

}
}