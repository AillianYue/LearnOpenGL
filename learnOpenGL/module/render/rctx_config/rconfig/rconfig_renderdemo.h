#pragma once
#include <string>

namespace learnOpenGL {
namespace config {

class RConfigRenderDemo {
private:

public:
    RConfigRenderDemo(){};
    ~RConfigRenderDemo(){};

    const std::string VERT_SHADER_PATH = std::string(RESOURCE_PATH) + "shader/rdemo.vert";
    const std::string FRAG_SHADER_PATH = std::string(RESOURCE_PATH) + "shader/rdemo.frag";

};

}
}