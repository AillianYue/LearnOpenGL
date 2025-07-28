#include <string>

namespace learnOpenGL {
namespace config {

class RConfigCar2D {
public:
    RConfigCar2D(){}
    ~RConfigCar2D(){}

    const std::string VERT_SHADER  = std::string(RESOURCE_PATH) + "shader/car2d/car2d.vs";
    const std::string FRAG_SHADER  = std::string(RESOURCE_PATH) + "shader/car2d/car2d.fs";
    const std::string TEXTURE_PATH = std::string(RESOURCE_PATH) + "texture/car2d/BODY_CE_CB.png";
};

}
}