#pragma once
#include "rbase.h"
#include "rmesh3d.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace learnOpenGL {
namespace render {

class RenderCar3D : public RBase {
public:
    using RBase::RBase;
    RenderCar3D(const std::string m_name, flow::RCtxData& rCtxData, flow::RCtxWin& rCtxWin)
        : RBase(m_name, rCtxData, rCtxWin) {}
    ~RenderCar3D() override;
    bool Init() override;
    bool Draw(int x, int y, int w, int h) override;
    bool Update(bool flag = false) override;
    bool Clear() override;

private:
    bool m_isInit = false;
    std::shared_ptr<opengl::Shader> m_shader;
    std::shared_ptr<Mesh3D> m_mesh;
    std::shared_ptr<opengl::Camera> m_camera;

    // 3D变换矩阵
    glm::mat4 m_model = glm::mat4(1.0f);    // 模型矩阵（控制模型自身旋转、缩放）
    glm::mat4 m_view = glm::mat4(1.0f);     // 视图矩阵（控制相机位置和朝向）
    glm::mat4 m_projection = glm::mat4(1.0f); // 投影矩阵（控制透视效果）

    // 模型和纹理路径
    const std::string OBJ_PATH = std::string(RESOURCE_PATH) + "texture/car3d/backpack.obj";
    
    const std::string VERT_SHADER = std::string(RESOURCE_PATH) + "shader/car3d/car3d.vs";
    const std::string FRAG_SHADER = std::string(RESOURCE_PATH) + "shader/car3d/car3d.fs";
};

}
}