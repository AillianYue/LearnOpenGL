#include "rctx_data.h"

namespace learnOpenGL {
namespace flow {

#define RPrmIns learnOpenGL::config::RParam::GetInstance()
bool RCtxData::Init()
{
    do {
        
        m_updateRenderDemoData = std::make_shared<UpdateRenderDemoData>();
        // 视图参数
        // const auto& winPrm = RPrmIns.GetWinParam();
        spdlog::info("RCtxData::Init() success");
        return true;
    } while (0);
    spdlog::error("RCtxData::Init() failed");
    return false;
}

bool RCtxData::Update() {
    // TODO
    // spdlog::info("RCtxData::Update() TODO");
    return true;
}
}
}