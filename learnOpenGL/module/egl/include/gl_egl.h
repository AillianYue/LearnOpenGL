#pragma once

#define EGL_NO_X11
#include "X11/Xlib.h"
#include "EGL/egl.h"
#include "EGL/eglext.h"
#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"
#include "spdlog/spdlog.h"

namespace egl {

enum class GL_SFC_Type : int8_t {NO_SURFACE = 0, WINDOW_SURFACE, PBUFFER_SURFACE };
struct EglObj {
    EGLDisplay display;
    EGLConfig config;
    EGLContext context;
    EGLSurface surface;
    Display* xDisplay;
    Window xWindow;
};

class EglPipe {
private:
    std::shared_ptr<EglObj> m_eglObj;

public:
    EglPipe() = default;
    virtual ~EglPipe();

    GLboolean Init();
    GLboolean AddCtx(EGLContext ctx = EGL_NO_CONTEXT);
    GLboolean AddWin(int w, int h);
    GLboolean AddSfc(GL_SFC_Type type);
    GLboolean EglSwap();
    
    EGLContext GetCtx();
    EGLConfig GetCfg();

};
}