#include "rdemo.h"

namespace learnOpenGL {
namespace render {

RenderDemo::~RenderDemo() {}

bool RenderDemo::Init() {
    if(m_isInit) {
        spdlog::info("RenderDemo::Init() already");
        return true;
    }
    if(!InitOpenGl()) {
        spdlog::error("RenderDemo::Init() InitOpenGl() error");
        return false;
    }
    spdlog::info("{} VERT_SHADER = {}", m_name, VERT_SHADER);
    spdlog::info("{} FRAG_SHADER = {}", m_name, FRAG_SHADER);
    m_shader = std::make_shared<opengl::Shader>(VERT_SHADER.c_str(), FRAG_SHADER.c_str());
    
    const auto& RenderDemoPrm = learnOpenGL::config::RParam::GetInstance().GetRenderDemoParam();
    spdlog::info("{} Init() {}", m_name, RenderDemoPrm.demoText);
    m_isInit = true;
    spdlog::info("{} Init() success", m_name);
    return true;
}

bool RenderDemo::InitOpenGl() {
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vert.size(), m_vert.data(), GL_STATIC_DRAW);
    return true;
}
bool RenderDemo::Draw(int x, int y, int w, int h) {
    // spdlog::info("RenderDemo::Draw() success");
    glViewport(x, y, w, h);
    m_shader->Use();
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    return true;
}
bool RenderDemo::Update(bool flag) {
    spdlog::info("RenderDemo::Update() success");
    return true;
}
bool RenderDemo::Clear() {
    spdlog::info("RenderDemo::Clear() success");
    return true;
}
}
}