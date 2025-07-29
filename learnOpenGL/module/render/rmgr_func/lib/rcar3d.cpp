#include "rcar3d.h"

namespace learnOpenGL {
namespace render {

RenderCar3D::~RenderCar3D() {
    // 自动释放智能指针资源
}

bool RenderCar3D::Init() {
    if (m_isInit) return true;

    // 创建3D着色器
    m_shader = std::make_shared<opengl::Shader>(VERT_SHADER.c_str(), FRAG_SHADER.c_str());
    // 初始化3D网格（加载OBJ和纹理）
    m_mesh = std::make_shared<Mesh3D>(OBJ_PATH);
    // 初始化摄像机
    m_camera = std::make_shared<opengl::Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    // 初始化变换矩阵
    // 模型矩阵：轻微旋转模型使其正面朝向相机
    m_model = glm::rotate(m_model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    m_model = glm::scale(m_model, glm::vec3(0.01f));  // 缩放模型（根据OBJ实际大小调整）

    // 视图矩阵：相机位置在(0, 3, 5)，看向原点
    m_view = glm::lookAt(glm::vec3(0.0f, 3.0f, 5.0f),  // 相机位置
                         glm::vec3(0.0f, 0.0f, 0.0f),  // 目标点
                         glm::vec3(0.0f, 1.0f, 0.0f)); // 上方向

    m_isInit = true;
    spdlog::info("{} Init() success", m_name);
    return true;
}

bool RenderCar3D::Draw(int x, int y, int w, int h) {
    if (!m_isInit) return false;

    // 设置视口
    glViewport(x, y, w, h);

    // 启用深度测试（3D渲染必需，处理遮挡关系）
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader->Use();

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(m_camera->Zoom), (float)w / (float)h, 0.1f, 100.0f);
    glm::mat4 view = m_camera->GetViewMatrix();
    m_shader->SetMat4("projection", projection);
    m_shader->SetMat4("view", view);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    m_shader->SetMat4("model", model);
    m_mesh->Draw(m_shader);

    return true;
}

bool RenderCar3D::Update(bool flag) {
    // // 可选：更新模型动画（如旋转）
    // if (flag) {
    //     m_model = glm::rotate(m_model, glm::radians(0.5f), glm::vec3(0.0f, 1.0f, 0.0f)); // 绕Y轴旋转
    // }
    return true;
}

bool RenderCar3D::Clear() {
    return true;
}

}
}