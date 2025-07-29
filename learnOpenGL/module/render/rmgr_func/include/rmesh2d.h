#pragma once

#include <vector>
#include <memory>
#include "gl_shader.h"
#include "stb_image.h"

namespace learnOpenGL {
namespace render {

class Mesh2D {
public:
    Mesh2D(const std::string& path, const std::vector<float>& vert);
    ~Mesh2D();
    bool Draw(std::shared_ptr<opengl::Shader> shader);
private:
    bool InitOpenGl();
    bool InitPngTexture(const std::string& path, unsigned int& tex);
    bool m_isInit = false;
    unsigned int m_vbo{0};
    unsigned int m_tex{0};
    std::vector<float> m_vert;
};

}
}