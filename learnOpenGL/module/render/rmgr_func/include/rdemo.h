#pragma once

#include "rbase.h"
#include "gl_shader.h"

namespace learnOpenGL {
namespace render {

class RenderDemo : public RBase {
public:
    using RBase::RBase; 
    RenderDemo(const std::string m_name, flow::RCtxData& rCtxData, flow::RCtxWin& rCtxWin)
    : RBase(m_name, rCtxData, rCtxWin) {}
    ~RenderDemo() override;
    bool Init() override;
    bool Draw(int x, int y, int w, int h) override;
    bool Update(bool flag = false) override;
    bool Clear() override;

    bool InitOpenGl();

private:
    bool m_isInit = false;
    unsigned int m_vbo;
    std::vector<float> m_vert = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
    };
    std::vector<unsigned short> m_indx;
    std::shared_ptr<opengl::Shader> m_shader;
    const std::string VERT_SHADER = std::string(RESOURCE_PATH) + "shader/demo/rdemo.vs";
    const std::string FRAG_SHADER = std::string(RESOURCE_PATH) + "shader/demo/rdemo.fs";
};

}
}