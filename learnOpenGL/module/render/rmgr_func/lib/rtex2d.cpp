#include "rtex2d.h"

namespace learnOpenGL {
namespace render {
MeshTex2D::MeshTex2D(const std::string &path, const std::vector<float> &vert) {
    m_vert = vert;
    if(!InitOpenGl()) {
        spdlog::error("{} Failed to init opengl", path);
    }
    if(!InitPngTexture(path, m_tex)) {
        spdlog::error("{} Failed to init tex", path);
    }
}

MeshTex2D::~MeshTex2D() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteTextures(1, &m_tex);
}

bool MeshTex2D::InitOpenGl() {
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vert.size(), m_vert.data(), GL_STATIC_DRAW);
    return true;
}
bool MeshTex2D::InitPngTexture(const std::string& path, unsigned int& tex) {
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        // glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return true;
}
bool MeshTex2D::Draw(std::shared_ptr<opengl::Shader> shader) {
    shader->Use();

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    shader->SetInt("Tex2D", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_tex);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    return true;
}

}
}