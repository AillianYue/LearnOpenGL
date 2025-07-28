#pragma once
#include "gl_egl.h"
#include "gl_fbo.h"
#include "rparam.h"

#include "spdlog/spdlog.h"

namespace learnOpenGL {
namespace flow {

enum class FBO_ID : int8_t {FBO_DEFAULT = 0, FBO_LEFT, FBO_RIGHT, FBO_SIZE };

class RCtxWin {
private:
    std::shared_ptr<egl::EglPipe> m_eglPipe;
    std::vector<std::shared_ptr<opengl::FrameBuffer>> m_fboWin;
    std::vector<std::shared_ptr<opengl::FrameBuffer>> m_fboTex;

public:
    RCtxWin(std::shared_ptr<egl::EglPipe> eglPipe) : m_eglPipe(eglPipe) {}
    ~RCtxWin() {};

    bool Init();
    bool Update();
    bool SwapWin();

    // uint32_t BindWin(bool update = false);
    bool BindFboWin(FBO_ID id);
    // uint32_t SetFboTex(FBO_ID id);
    // uint32_t GetFboWin(FBO_ID id);
    uint32_t GetFboTex(FBO_ID id);
};







}
}