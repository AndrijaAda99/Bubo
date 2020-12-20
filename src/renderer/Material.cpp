#include "renderer/Material.h"


namespace bubo {

    Material::Material(Shader *shader) : m_shader(shader) {}

    Material::~Material() {}

    void Material::setTexture(const std::string &name, const Texture *value, const unsigned int unit) {
        m_samplers[name].texture = value;
        m_samplers[name].unit = unit;

        m_shader->bind();
        m_shader->setInt(name, unit);
    }

    void Material::setFloat(const std::string &name, const float value) {
        m_uniforms.floats[name] = value;
    }

    void Material::setVec2(const std::string &name, const glm::vec2 &value) {
        m_uniforms.vec2s[name] = value;
    }

    void Material::setVec3(const std::string &name, const glm::vec3 &value) {
        m_uniforms.vec3s[name] = value;
    }

    void Material::setVec4(const std::string &name, const glm::vec4 &value) {
        m_uniforms.vec4s[name] = value;
    }

    void Material::setMat3(const std::string &name, const glm::mat3 &value) {
        m_uniforms.mat3s[name] = value;
    }

    void Material::setMat4(const std::string &name, const glm::mat4 &value) {
        m_uniforms.mat4s[name] = value;
    }

    void Material::setSamplers() {
        m_shader->bind();
        for (auto sampler : m_samplers) {
            auto texture = sampler.second.texture;
            auto unit = sampler.second.unit;
            texture->bind(unit);
        }
    }

    void Material::setUniforms() {
        m_shader->bind();
        for (auto uniform : m_uniforms.floats) {
            m_shader->setFloat(uniform.first, uniform.second);
        }
        for (auto uniform : m_uniforms.vec2s) {
            m_shader->setFloat2(uniform.first, uniform.second);
        }
        for (auto uniform : m_uniforms.vec3s) {
            m_shader->setFloat3(uniform.first, uniform.second);
        }
        for (auto uniform : m_uniforms.vec4s) {
            m_shader->setFloat4(uniform.first, uniform.second);
        }
        for (auto uniform : m_uniforms.mat3s) {
            m_shader->setMat3(uniform.first, uniform.second);
        }
        for (auto uniform : m_uniforms.mat4s) {
            m_shader->setMat4(uniform.first, uniform.second);
        }

    }

    void Material::setShader(Shader *shader) {
        m_shader = shader;
        m_samplers.clear();
        m_uniforms.floats.clear();
        m_uniforms.vec2s.clear();
        m_uniforms.vec3s.clear();
        m_uniforms.vec4s.clear();
        m_uniforms.mat3s.clear();
        m_uniforms.mat4s.clear();
    }

}
