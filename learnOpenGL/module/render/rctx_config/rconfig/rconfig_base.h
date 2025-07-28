#pragma once
#include <string>

namespace learnOpenGL {
namespace config {

class RConfigBase {
public:
    RConfigBase(){};
    ~RConfigBase(){};
    const std::string CONFIG_ROOT_PATH = std::string(RESOURCE_PATH);
};

}
}