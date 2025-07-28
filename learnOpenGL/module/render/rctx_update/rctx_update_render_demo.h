#pragma once
#include "rctx_update_base.h"

namespace learnOpenGL {
namespace flow {

class UpdateRenderDemoData : public RCtxUpdateBase<UpdateRenderDemoData> {
public:
    UpdateRenderDemoData() : RCtxUpdateBase() {};
    ~UpdateRenderDemoData() override = default;
public:
    RenderDemoData demoData;  // 包含实际数据

protected:
    bool DoUpdateMock(std::shared_ptr<UpdateRenderDemoData> updPrm) override {
        // 通过参数访问其他实例的数据
        updPrm->demoData.a++;
        return true;
    }
};

}
}