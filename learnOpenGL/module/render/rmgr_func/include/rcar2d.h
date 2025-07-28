#pragma once

#include "rbase.h"
#include "rtex2d.h"
#include "gl_shader.h"
#include "stb_image.h"

namespace learnOpenGL {
namespace render {

class RenderCar2D : public RBase {
public:
    using RBase::RBase; 
    RenderCar2D(const std::string m_name, flow::RCtxData& rCtxData, flow::RCtxWin& rCtxWin)
    : RBase(m_name, rCtxData, rCtxWin) {}
    ~RenderCar2D() override;
    bool Init() override;
    bool Draw(int x, int y, int w, int h) override;
    bool Update(bool flag = false) override;
    bool Clear() override;

private:
    bool m_isInit = false;
    unsigned int m_vbo;
    unsigned int m_tex;
    std::vector<float> m_vert = {
        // positions  // texture 
        -1.0f, -1.0f, 0.0f, 0.0f,  // left down
         1.0f, -1.0f, 1.0f, 0.0f,  // right down
        -1.0f,  1.0f, 0.0f, 1.0f,  // left top
         1.0f,  1.0f, 1.0f, 1.0f,  // right top
    };
    std::vector<unsigned short> m_indx;
    std::shared_ptr<opengl::Shader> m_shader;
    std::shared_ptr<MeshTex2D> m_mesh;
    const std::string VERT_SHADER  = std::string(RESOURCE_PATH) + "shader/car2d/car2d.vs";
    const std::string FRAG_SHADER  = std::string(RESOURCE_PATH) + "shader/car2d/car2d.fs";
    const std::string TEXTURE_PATH = std::string(RESOURCE_PATH) + "texture/car2d/BODY_CE_CB.png";
};

}
}