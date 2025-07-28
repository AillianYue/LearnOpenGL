#include "rparam.h"


namespace learnOpenGL {
namespace config {
bool RParam::Init() {
    if(m_isInit) {
        spdlog::warn("RParam::Init() has been called.");
        return true;
    }
    do {
        if(!ApplyParamDefault()) {
            spdlog::error("RParam::Init() failed.");
        }
        // if(!ApplyParamYaml()) {
        //     spdlog::error("RParam::Init() failed.");
        // }

        m_isInit = true;
        spdlog::info("RParam::Init() success.");
        return true;
    } while (0);

    spdlog::error("RParam::Init() failed.");
    return false;
}
bool RParam::ApplyParamDefault() {
    std::string yamlPath = std::string(RESOURCE_PATH) + "config/param.yaml";
    YAML::Node yamlNode = YAML::LoadFile(yamlPath);
    try
    {
        yamlNode = YAML::LoadFile(yamlPath.c_str());
    }
    catch(const std::exception& e)
    {
        spdlog::error("RParam::ApplyParamDefault() load yaml failed. {}", e.what());
    }
    
    if(!ApplyParamView(m_adjustParam, yamlNode)) {
        spdlog::error("ApplyParamScreen failed");
        return false;
    }
    if(!ApplyPrmRenderDemo(m_adjustParam, yamlNode)) {
        spdlog::error("ApplyPrmRenderDemo failed");
        return false;
    }
    return true;
}
bool RParam::ApplyParamView(AdjustParam& param, YAML::Node& node) {
    param.paramWin.WinSize.x = node["Param"]["RenderSize"]["WinSize"]["x"].as<int>();
    param.paramWin.WinSize.y = node["Param"]["RenderSize"]["WinSize"]["y"].as<int>();
    param.paramWin.WinSize.w = node["Param"]["RenderSize"]["WinSize"]["w"].as<int>();
    param.paramWin.WinSize.h = node["Param"]["RenderSize"]["WinSize"]["h"].as<int>();

    param.paramWin.AreaLeft.x = node["Param"]["RenderSize"]["LeftSize"]["x"].as<int>();
    param.paramWin.AreaLeft.y = node["Param"]["RenderSize"]["LeftSize"]["y"].as<int>();
    param.paramWin.AreaLeft.w = node["Param"]["RenderSize"]["LeftSize"]["w"].as<int>();
    param.paramWin.AreaLeft.h = node["Param"]["RenderSize"]["LeftSize"]["h"].as<int>();

    param.paramWin.AreaRight.x = node["Param"]["RenderSize"]["RightSize"]["x"].as<int>();
    param.paramWin.AreaRight.y = node["Param"]["RenderSize"]["RightSize"]["y"].as<int>();
    param.paramWin.AreaRight.w = node["Param"]["RenderSize"]["RightSize"]["w"].as<int>();
    param.paramWin.AreaRight.h = node["Param"]["RenderSize"]["RightSize"]["h"].as<int>();
    return true;
}

bool RParam::ApplyPrmRenderDemo(AdjustParam &param, YAML::Node &node)
{
    param.paramRenderDemo.demoText = node["Param"]["RenderDemo"]["demoText"].as<std::string>();
    return true;
}
}
}