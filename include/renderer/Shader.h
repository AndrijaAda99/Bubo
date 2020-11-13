#ifndef BUBO_SHADER_H
#define BUBO_SHADER_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

namespace bubo {

    class Shader {
    public:
        Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        ~Shader();

        void bind() const;
        void unbind() const;

        void setBool(const std::string& name, bool value);
        void setInt(const std::string& name, int value);
        void setIntArray(const std::string& name, int* values, uint32_t count);
        void setFloat(const std::string& name, float value);
        void setFloat3(const std::string& name, const glm::vec3& value);
        void setFloat4(const std::string& name, const glm::vec4& value);
        void setMat3(const std::string& name, const glm::mat3& value);
        void setMat4(const std::string& name, const glm::mat4& value);

    private:
        void init(const std::string& shaderSrc, const std::string& fragmentSrc);
        void destroy() const;

        unsigned int compileShader(unsigned int type, const char* shaderSource);

        std::string parseShader(const std::string& filepath);

        void checkShaderCompilationError(unsigned int type, unsigned int shaderID);
        void checkProgramLinkError();

    private:
        unsigned int m_shaderProgramID = 0;

    };

}

#endif //BUBO_SHADER_H
