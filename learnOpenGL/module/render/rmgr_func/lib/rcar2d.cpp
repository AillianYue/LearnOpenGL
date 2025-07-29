#include "rcar2d.h"

namespace learnOpenGL {
namespace render {

RenderCar2D::~RenderCar2D() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteTextures(1, &m_tex);
}

bool RenderCar2D::Init() {
    if(m_isInit) {
        spdlog::info("{} is init", m_name);
        return true;
    }
    spdlog::info("{} VERT_SHADER = {}", m_name, VERT_SHADER);
    spdlog::info("{} FRAG_SHADER = {}", m_name, FRAG_SHADER);
    m_shader = std::make_shared<opengl::Shader>(VERT_SHADER.c_str(), FRAG_SHADER.c_str());

    m_mesh = std::make_shared<Mesh2D>(TEXTURE_PATH, m_vert);

    m_isInit = true;
    spdlog::info("{} Init() success", m_name);
    return true;
}

bool RenderCar2D::Draw(int x, int y, int w, int h) {
    glViewport(x, y, w, h);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    m_mesh->Draw(m_shader);

    return true;
}

bool RenderCar2D::Update(bool flag) {
    return true;
}

bool RenderCar2D::Clear() {
    return true;
}


}
}