#include "rcopy_fbo.h"


namespace learnOpenGL {
namespace render {
RCopyFbo::~RCopyFbo() {
    if (m_vboWin) {
        glDeleteBuffers(1, &m_vboWin);
    }
    if (m_vboLeft) {
        glDeleteBuffers(1, &m_vboLeft);
    }
    if (m_vboRight) {
        glDeleteBuffers(1, &m_vboRight);
    }

    // if (m_ebo) {
    //     glDeleteBuffers(1, &m_ebo);
    // }
}

bool RCopyFbo::Init() {
    if(m_isInit) {
        spdlog::info("RCopyFbo is already initialized");
        return true;
    }
    do {
        if(!PreProcess()) {
            spdlog::error("RCopyFbo::Init() PreProcess() failed");
        }
        if(!InitOpenGl()) {
            spdlog::error("RCopyFbo::Init() InitOpenGl() failed");
        }
        m_isInit = true;
        spdlog::info("RCopyFbo::Init() InitOpenGl() success");
        return true;
    } while (0);
    spdlog::error("RCopyFbo::Init() failed");
    return false;
}

bool RCopyFbo::InitOpenGl()
{
    spdlog::info("COPYFBO VERT_SHADER = {}", VERT_SHADER);
    spdlog::info("COPYFBO FRAG_SHADER = {}", FRAG_SHADER);
    m_shader = std::make_unique<opengl::Shader>(VERT_SHADER.c_str(), FRAG_SHADER.c_str());

    glGenBuffers(1, &m_vboWin);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboWin);
    glBufferData(GL_ARRAY_BUFFER, sizeof(decltype(m_vertWin)::value_type) * m_vertWin.size(), m_vertWin.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_vboLeft);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboLeft);
    glBufferData(GL_ARRAY_BUFFER, sizeof(decltype(m_vertLeft)::value_type) * m_vertLeft.size(), m_vertLeft.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_vboRight);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboRight);
    glBufferData(GL_ARRAY_BUFFER, sizeof(decltype(m_vertRight)::value_type) * m_vertRight.size(), m_vertRight.data(), GL_STATIC_DRAW);

    return true;
}
bool RCopyFbo::Draw(int x, int y, int w, int h)
{
    if(!m_isInit) {
        
        return false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(x, y, w, h);
    m_shader->Use();
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vboWin);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertWin.size(), m_vertWin.data(), GL_STATIC_DRAW);

    glActiveTexture(GL_TEXTURE0);
    m_shader->SetInt("ourTexture", 0);

    CopyTex2Win(m_vboLeft, m_rCtxWin.GetFboTex(flow::FBO_ID::FBO_LEFT));
    CopyTex2Win(m_vboRight, m_rCtxWin.GetFboTex(flow::FBO_ID::FBO_RIGHT));

    return true;
}
bool RCopyFbo::CopyTex2Win(uint32_t vbo, uint32_t tex)
{
    if(vbo == 0 || tex == 0) {
        return false;
    }
    glBindTexture(GL_TEXTURE_2D, tex);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // glDrawElements(GL_TRIANGLES, num, GL_UNSIGNED_SHORT, (void*)0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    return true;
}

bool RCopyFbo::Clear()
{
    if(m_isInit) {
        return false;
    }
    return true;
}
bool RCopyFbo::Update(bool flag)
{
    if(m_isInit) {
        return false;
    }
    if(!PreProcess()) {
        spdlog::error("RCopyFbo::Update() PreProcess() failed");
    }
    if(m_vertWin.size() != 0) {
        glBindBuffer(GL_ARRAY_BUFFER, m_vboWin);
        glBufferData(GL_ARRAY_BUFFER, sizeof(decltype(m_vertWin)::value_type) * m_vertWin.size(), m_vertWin.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    return true;
}

bool RCopyFbo::PreProcess()
{
    const auto& winPrm = learnOpenGL::config::RParam::GetInstance().GetWinParam();
    // float xLeft = winPrm.AreaLeft.x;
    // float yLeft = winPrm.AreaLeft.y;
    float wLeft = winPrm.AreaLeft.w;
    // float hLeft = winPrm.AreaLeft.h;
    // float xRight = winPrm.AreaRight.x;
    // float yRight = winPrm.AreaRight.y;
    // float wRight = winPrm.AreaRight.w;
    // float hRight = winPrm.AreaRight.h;
    // float xWin = winPrm.WinSize.x;
    // float yWin = winPrm.WinSize.y;
    float wWin = winPrm.WinSize.w;
    // float hWin = winPrm.WinSize.h;

    float xLeftLD  = -1.0;
    float yLeftLD  = -1.0;
    float xLeftRD  = (wLeft - wWin / 2.0) / (wWin / 2.0);
    float yLeftRD  = yLeftLD;
    float xLeftLU  = xLeftLD;
    float yLeftLU  = 1.0;
    float xLeftRU  = xLeftRD;
    float yLeftRU  = yLeftLU;
    float xRightLD = xLeftRD;
    float yRightLD = yLeftRD;
    float xRightRD = 1.0;
    float yRightRD = yRightLD;
    float xRightLU = xRightLD;
    float yRightLU = 1.0;
    float xRightRU = xRightRD;
    float yRightRU = yRightLU;

    m_vertWin =  {
        -1.0f,-1.0f, 0.0f, 0.0f, 0.0f,
         1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    };
    m_vertLeft = {
        xLeftLD, yLeftLD, 0.0f, 0.0f, 0.0f,
        xLeftRD, yLeftRD, 0.0f, 1.0f, 0.0f,
        xLeftLU, yLeftLU, 0.0f, 0.0f, 1.0f,
        xLeftRU, yLeftRU, 0.0f, 1.0f, 1.0f,
    };
    m_vertRight = {
        xRightLD, yRightLD, 0.0f, 0.0f, 0.0f,
        xRightRD, yRightRD, 0.0f, 1.0f, 0.0f,
        xRightLU, yRightLU, 0.0f, 0.0f, 1.0f,
        xRightRU, yRightRU, 0.0f, 1.0f, 1.0f,
    };

    // m_indx = {0, 1, 2, 2, 3, 0};
    return true;
}

}
}