#pragma once

#include "gl_egl.h"
#include "rctx_data.h"
#include "rctx_win.h"

namespace learnOpenGL {
namespace render {

class RBase {
protected:
    bool m_isInit;
    std::string m_name;
    flow::RCtxData& m_rCtxData;
    flow::RCtxWin& m_rCtxWin;

public:
    RBase(const std::string m_name, flow::RCtxData& rCtxData, flow::RCtxWin& rCtxWin)
    : m_isInit{false}, m_name(m_name), m_rCtxData(rCtxData), m_rCtxWin(rCtxWin) {}
    virtual ~RBase() = default;

    virtual bool Init() = 0;
    virtual bool Draw(int x, int y, int w, int h) = 0;
    virtual bool Update(bool flag = false) = 0;
    virtual bool Clear() = 0;

};

}
}