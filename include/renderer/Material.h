#ifndef BUBO_MATERIAL_H
#define BUBO_MATERIAL_H

#include "Shader.h"
#include "Texture.h"


namespace bubo {

    struct Uniforms_t {
        std::map<std::string, float> floats;
		std::map<std::string, glm::vec2> vec2s;
		std::map<std::string, glm::vec3> vec3s;
		std::map<std::string, glm::vec4> vec4s;
        std::map<std::string, glm::mat4> mat3s;
        std::map<std::string, glm::mat4> mat4s;
    };

    struct Sampler2D_t {
        std::shared_ptr<Texture> texture;
        unsigned int unit;
    };

    class Material {
    public:
        Material(std::shared_ptr<Shader> shader);
        ~Material();

        void setShader(std::shared_ptr<Shader> shader);
        const std::shared_ptr<Shader> getShader() const { return m_shader; }

        void setTexture(const std::string &name, const std::shared_ptr<Texture> value, const unsigned int unit);
        void setFloat(const std::string &name, const float value);
        void setVec2(const std::string &name, const glm::vec2 &value);
        void setVec3(const std::string &name, const glm::vec3 &value);
        void setVec4(const std::string &name, const glm::vec4 &value);
        void setMat3(const std::string &name, const glm::mat3 &value);
        void setMat4(const std::string &name, const glm::mat4 &value);

        void setSamplers();
        void setUniforms();

    private:
        std::shared_ptr<Shader> m_shader;
        std::map<std::string, Sampler2D_t> m_samplers;
        Uniforms_t m_uniforms;

    };

}

#endif //BUBO_MATERIAL_H
