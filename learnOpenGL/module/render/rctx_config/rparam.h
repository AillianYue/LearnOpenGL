#pragma once
#include <atomic>
#include "rconfig_type.h"
#include "spdlog/spdlog.h"
#include "yaml-cpp/yaml.h"
namespace learnOpenGL {
namespace config {


class RParam {
private:
    std::atomic<bool> m_isInit;
    AdjustParam m_adjustParam;
    // WinParam m_winParam;

private:
    RParam() = default;  // 私有构造函数
    ~RParam() = default; // 私有析构函数
    
    // 禁用拷贝和赋值
    RParam(const RParam&) = delete;
    RParam& operator=(const RParam&) = delete;

public:
    static RParam& GetInstance() {
        static RParam s_Instance;  // C++11保证线程安全
        return s_Instance;
    }
    bool Init();
    bool ApplyParamDefault();

    bool ApplyParamView(AdjustParam& param, YAML::Node& node);
    bool ApplyPrmRenderDemo(AdjustParam& param, YAML::Node& node);

public:
    const WinParam& GetWinParam() const { return m_adjustParam.paramWin; };
    const ParamRenderDemo& GetRenderDemoParam() const { return m_adjustParam.paramRenderDemo; };
};


} // namespace config
} // namespace learnOpenGL