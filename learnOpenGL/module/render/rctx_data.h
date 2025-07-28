#pragma once

#include "gl_egl.h"
#include "rctx_update.h"
#include "rctx_type.h"
#include "rparam.h"
#include "spdlog/spdlog.h"

namespace learnOpenGL {
namespace flow {


class RCtxData { 
private:
    std::shared_ptr<egl::EglPipe> m_eglPipe;

    std::shared_ptr<UpdateRenderDemoData> m_updateRenderDemoData;
    
    // Render Data Structure
    RenderDemoData m_rendeDemorData;


public:
    RCtxData(std::shared_ptr<egl::EglPipe> eglPipe) : m_eglPipe(eglPipe) {};
    ~RCtxData(){};

    bool Init();
    bool Update();

    // Get Render Data
    const RenderDemoData& GetRenderData() const { return m_rendeDemorData; };



};


}
}