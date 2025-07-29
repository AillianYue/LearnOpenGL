#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "gl_mesh.h"
#include "gl_shader.h"
#include "gl_camera.h"

namespace learnOpenGL {
namespace render {
using namespace std;

class Mesh3D {
public:
    // model data 
    vector<opengl::Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<opengl::Mesh>    meshes;
    string directory;
    bool gammaCorrection;
    Mesh3D(string const &path, bool gamma = false) : gammaCorrection(gamma) { LoadModel(path);}
    void Draw(std::shared_ptr<opengl::Shader> shader);
    
private:
    void LoadModel(string const &path);
    void ProcessNode(aiNode *node, const aiScene *scene);
    opengl::Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
    vector<opengl::Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
    unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);
};

}
}