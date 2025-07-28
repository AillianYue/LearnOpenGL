#include "gl_egl.h"


namespace egl {

EglPipe::~EglPipe() {
    eglMakeCurrent(m_eglObj->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(m_eglObj->display, m_eglObj->context);
    eglDestroyContext(m_eglObj->display, m_eglObj->surface);
    eglTerminate(m_eglObj->display);
    XDestroyWindow(m_eglObj->xDisplay, m_eglObj->xWindow);
    XCloseDisplay(m_eglObj->xDisplay);
    glFinish();
}

GLboolean EglPipe::Init() {
    m_eglObj = std::make_shared<EglObj>();
    static EGLDisplay gs_display = EGL_NO_DISPLAY;
    static Display* gs_xdisplay = nullptr;
    if(gs_display == EGL_NO_DISPLAY) {
        if(gs_xdisplay == nullptr) {
            gs_xdisplay = XOpenDisplay(nullptr);
            if (gs_xdisplay == nullptr){
                spdlog::error("EglPipe::Init() can not connect X server");
                return GL_FALSE;
            }
        }
        gs_display = eglGetDisplay((EGLNativeDisplayType)gs_xdisplay);
    }
    m_eglObj->xDisplay = gs_xdisplay;
    m_eglObj->display = gs_display;
    if(m_eglObj->display == EGL_NO_DISPLAY) {
        spdlog::error("EglPipe::Init() eglGetDisplay failed: 0x{}", eglGetError());
        return GL_FALSE;
    }

    if(!eglInitialize(m_eglObj->display, nullptr, nullptr)) {
        spdlog::error("EglPipe::Init() eglInitialize failed: 0x{}", eglGetError());
        return GL_FALSE;
    }

    if(!eglBindAPI(EGL_OPENGL_ES_API)) {
        spdlog::error("EglPipe::Init() eglBindAPI failed: 0x{}", eglGetError());
        return GL_FALSE;
    }


    return GL_TRUE;
}
GLboolean EglPipe::AddCtx(EGLContext ctx) {
    EGLint ctxattr[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    m_eglObj->context = eglCreateContext(m_eglObj->display, this->GetCfg(), ctx, ctxattr);
    if(m_eglObj->context == EGL_NO_CONTEXT) {
        spdlog::error("EglPipe::AddCtx() eglCreateContext failed: 0x{}", eglGetError());
        return GL_FALSE;
    }
    eglMakeCurrent(m_eglObj->display, EGL_NO_SURFACE, EGL_NO_SURFACE, m_eglObj->context);
    return GL_TRUE;
}

GLboolean EglPipe::AddWin(int w, int h) {
    Window root = DefaultRootWindow(m_eglObj->xDisplay);
    XSetWindowAttributes swa;
    swa.event_mask = ExposureMask | PointerMotionMask | KeyPressMask;
    m_eglObj->xWindow = XCreateWindow(m_eglObj->xDisplay, root, 0, 0, w, h, 0, CopyFromParent, InputOutput, CopyFromParent, CWEventMask, &swa);
    XSelectInput(m_eglObj->xDisplay, m_eglObj->xWindow, ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask);
    XMapWindow(m_eglObj->xDisplay, m_eglObj->xWindow);
    return GL_TRUE;
}
GLboolean EglPipe::AddSfc(GL_SFC_Type type) {
    switch(type) {
        case GL_SFC_Type::WINDOW_SURFACE:
            m_eglObj->surface = eglCreateWindowSurface(m_eglObj->display, this->GetCfg(), m_eglObj->xWindow, nullptr);
            if(m_eglObj->surface == EGL_NO_SURFACE) {
                spdlog::error("EglPipe::AddSfc() eglCreateWindowSurface failed: 0x{}", eglGetError());
            }
        break;
        case GL_SFC_Type::PBUFFER_SURFACE:
            m_eglObj->surface = eglCreatePbufferSurface(m_eglObj->display, this->GetCfg(), nullptr);
            if(m_eglObj->surface == EGL_NO_SURFACE) {
                spdlog::error("EglPipe::AddSfc() eglCreatePbufferSurface failed: 0x{}", eglGetError());
            }
        break;
        case GL_SFC_Type::NO_SURFACE:
            m_eglObj->surface = EGL_NO_SURFACE;
        break;
        default:
        spdlog::error("EglPipe::AddSfc() surface type error, invalid surface type");
    }
    eglMakeCurrent(m_eglObj->display, m_eglObj->surface, m_eglObj->surface, m_eglObj->context);
    return GL_TRUE;
}
GLboolean EglPipe::EglSwap() {
    GLboolean ret = eglSwapBuffers(m_eglObj->display, m_eglObj->surface);
    if(ret == EGL_FALSE) {
        spdlog::error("EglPipe::EglSwap() eglSwapBuffers failed: 0x{}", eglGetError());
    }
    return GL_TRUE;
}

EGLContext EglPipe::GetCtx()
{
    return m_eglObj->context;
}

EGLConfig EglPipe::GetCfg()
{
    EGLint attr[] = {
        EGL_BUFFER_SIZE, 16,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 16,
        EGL_NONE,
    };
    EGLConfig ecfg;
    EGLint cfgSize;
    if(!eglChooseConfig(m_eglObj->display, attr, &ecfg, 1, &cfgSize)) {
        spdlog::error("EglPipe::GetCfg() eglChooseConfig failed: 0x{}", eglGetError());
    }
    if(cfgSize != 1) {
        spdlog::error("EglPipe::GetCfg() eglChooseConfig failed, Config Size = {} ", cfgSize);
    }
    m_eglObj->config;
    return ecfg;
}
}