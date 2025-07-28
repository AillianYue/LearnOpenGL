#pragma once
#include "rbase.h"
#include "gl_shader.h"

namespace learnOpenGL {
namespace render {

class RCopyFbo : public RBase {
public: 
    using RBase::RBase;
    ~RCopyFbo();

    bool Init() override;
    bool Draw(int x, int y, int w, int h) override;
    bool Clear() override;
    bool Update(bool flag = false) override;

protected:
    virtual bool InitOpenGl();
    bool PreProcess();
    bool CopyTex2Win(uint32_t vbo, uint32_t tex);
    // bool Draw(int x, int y, int w, int h, unsigned int fboTex);

private:
template<typename T> bool CvtData2Buffer(uint32_t& buffer, std::vector<T>& data);   

protected:
    bool m_isInit = false;
    unsigned int m_vboWin{0};
    unsigned int m_vboLeft{0};
    unsigned int m_vboRight{0};
    // unsigned int m_ebo{0};

    const std::string VERT_SHADER = std::string(RESOURCE_PATH) + "shader/copyfbo/copyfbo.vs";
    const std::string FRAG_SHADER = std::string(RESOURCE_PATH) + "shader/copyfbo/copyfbo.fs";

    std::vector<float> m_vertWin;
    std::vector<float> m_vertLeft;
    std::vector<float> m_vertRight;
    
    // std::vector<unsigned short> m_indx;

    std::shared_ptr<opengl::Shader> m_shader;



};
}
}