#pragma once

#include "GLES2/gl2.h"
#include "GLES3/gl32.h"
#include "spdlog/spdlog.h"

namespace opengl {

class FrameBuffer {
private:
    unsigned int m_tex{0};
    unsigned int m_fbo{0};
public:
    FrameBuffer(int w, int h, bool isMipmap = false);
    FrameBuffer(int w, int h, unsigned int texId);
    ~FrameBuffer();

    bool Bind();
    bool BindDefault();
    unsigned int GetTexId() const;
    unsigned int GetFboId() const;


};




} // namespace opengl
