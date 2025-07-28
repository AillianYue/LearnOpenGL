#pragma once

#include <memory>
#include "rconfig_base.h"
#include "rconfig_renderdemo.h"

namespace learnOpenGL {
namespace config {

class RConfig {
public:
    static RConfig& GetInstance() {
        static RConfig instance;
        return instance;
    }
    RConfig(const RConfig&) = delete;
    RConfig& operator=(const RConfig&) = delete;
    
    std::shared_ptr<RConfigBase> GetRConfigBase() const { return m_rConfigBase; }
    std::shared_ptr<RConfigRenderDemo> GetRConfigRenderDemo() const { return m_rConfigRenderDemo; }

private:
    RConfig() {
        m_rConfigBase = std::make_shared<RConfigBase>();
        m_rConfigRenderDemo = std::make_shared<RConfigRenderDemo>();
    }

private:
    std::shared_ptr<RConfigBase> m_rConfigBase;
    std::shared_ptr<RConfigRenderDemo> m_rConfigRenderDemo;
};

} // namespace config
} // namespace learnOpenGL