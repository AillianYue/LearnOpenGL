#pragma once
#include <memory> // 引入智能指针头文件
#include "rctx_type.h"
# include "spdlog/spdlog.h"

namespace learnOpenGL {
namespace flow {

template<typename T>
class RCtxUpdateBase {
public:
    RCtxUpdateBase() = default;
    virtual ~RCtxUpdateBase() = default;
    // 使用 shared_ptr 管理参数
    bool DoRender(std::shared_ptr<T> updPrm) {
        return DoUpdateMock(updPrm); // 透传给虚函数
    }

protected:
    virtual bool DoUpdateMock(std::shared_ptr<T> updPrm) = 0;
};

}
}