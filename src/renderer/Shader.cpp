#include <fstream>
#include "renderer/Shader.h"

#include "glad/glad.h"

#include <glm/gtc/type_ptr.hpp>

namespace bubo {

    Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
        init(parseShader(vertexShaderPath), parseShader(fragmentShaderPath));
    }

    Shader::~Shader() {
        destroy();
    }

    unsigned int Shader::compileShader(unsigned int type, const char *shaderSrc) {
        unsigned int shaderID = glCreateShader(type);
        glShaderSource(shaderID, 1, &shaderSrc, nullptr);
        glCompileShader(shaderID);

        checkShaderCompilationError(type, shaderID);

        return shaderID;
    }

    void Shader::init(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {

        unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
        unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

        m_shaderProgramID = glCreateProgram();

        glAttachShader(m_shaderProgramID, vertexShader);
        glAttachShader(m_shaderProgramID, fragmentShader);

        glLinkProgram(m_shaderProgramID);
        checkProgramLinkError();

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

    }

    void Shader::destroy() const {
        glDeleteProgram(m_shaderProgramID);
    }

    void Shader::checkShaderCompilationError(unsigned int type, unsigned int shaderID) {

        int success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

        if (!success) {

            GLint length;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

            std::vector<GLchar> infoLog(length);
            glGetShaderInfoLog(shaderID, length, nullptr, &infoLog[0]);

            BUBO_DEBUG_ERROR("Error while compiling shader source!\n{0}", infoLog.data());

            glDeleteShader(shaderID);

            switch (type) {
                case GL_VERTEX_SHADER:
                    BUBO_ASSERT(success, "Failed to compile vertex shader!")
                case GL_FRAGMENT_SHADER:
                    BUBO_ASSERT(success, "Failed to compile fragment shader!")
                default:
                    BUBO_ASSERT(success, "Failed to compile unknown shader!")
            }
        }

    }

    void Shader::checkProgramLinkError() {

        int success;
        glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &success);

        if (!success) {
            GLint length;
            glGetProgramiv(m_shaderProgramID, GL_INFO_LOG_LENGTH, &length);

            std::vector<GLchar> infoLog(length);
            glGetProgramInfoLog(m_shaderProgramID, length, nullptr, &infoLog[0]);

            BUBO_DEBUG_ERROR("{0}", infoLog.data());
            BUBO_ASSERT(success, "Failed to compile shader program!")
        }

    }

    std::string Shader::parseShader(const std::string& filepath) {
        std::stringstream source;
        std::fstream stream(filepath);
        std::string line;
        while (getline(stream, line)) {
            source << line << std::endl;
        }
        return source.str();
    }

    void Shader::bind() const {
        glUseProgram(m_shaderProgramID);
    }

    void Shader::unbind() const {
        glUseProgram(0);
    }

    void Shader::setInt(const std::string &name, int value) {
        GLint location = glGetUniformLocation(m_shaderProgramID, name.c_str());
        glUniform1i(location, value);
    }

    void Shader::setFloat(const std::string &name, float value) {
        GLint location = glGetUniformLocation(m_shaderProgramID, name.c_str());
        glUniform1f(location, value);
    }

    void Shader::setVec2(const std::string &name, const glm::vec2 &value) {
        GLint location = glGetUniformLocation(m_shaderProgramID, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void Shader::setVec3(const std::string &name, const glm::vec3 &value) {
        GLint location = glGetUniformLocation(m_shaderProgramID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void Shader::setVec4(const std::string &name, const glm::vec4 &value) {
        GLint location = glGetUniformLocation(m_shaderProgramID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void Shader::setMat3(const std::string &name, const glm::mat3 &value) {
        GLint location = glGetUniformLocation(m_shaderProgramID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    void Shader::setMat4(const std::string &name, const glm::mat4 &value) {
        GLint location = glGetUniformLocation(m_shaderProgramID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    std::map<std::string, Shader*> ShaderLibrary::m_shaders;

    void ShaderLibrary::makeDefaultShaders() {
        ShaderLibrary::m_shaders["defaultShader"] = new Shader("../../res/shaders/vertex.shader", "../../res/shaders/fragment.shader");
        ShaderLibrary::m_shaders["framebufferShader"] = new Shader("../../res/shaders/framebuffer_vertex.shader", "../../res/shaders/framebuffer_fragment.shader");
        ShaderLibrary::m_shaders["posterizationShader"] = new Shader("../../res/shaders/posterization_vertex.shader", "../../res/shaders/posterization_fragment.shader");
        ShaderLibrary::m_shaders["skyboxShader"] = new Shader("../../res/shaders/skybox_vertex.shader", "../../res/shaders/skybox_fragment.shader");
    }

    void ShaderLibrary::add(const std::string &name, Shader *shader) {
        if (m_shaders.find(name) != m_shaders.end()) {
            m_shaders[name] = shader;
        }
    }

    Shader *ShaderLibrary::get(const std::string &name) {
        return m_shaders.find(name)->second;
    }

    void ShaderLibrary::destroyShaders() {
        for (auto shader : m_shaders) {
            delete shader.second;
        }
    }

}
