#include <fstream>
#include "renderer/Shader.h"

#include "glad/glad.h"

namespace bubo {

    Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath) {
        init(parseShader(vertexShaderPath).c_str(), parseShader(fragmentShaderPath).c_str());
    }

    Shader::~Shader() {
        destroy();
    }

    int Shader::compileShader(unsigned int type, const char *shaderSrc) {
        unsigned int shaderID = glCreateShader(type);
        glShaderSource(shaderID, 1, &shaderSrc, nullptr);
        glCompileShader(shaderID);

        checkShaderCompilationError(type, shaderID);

        return shaderID;
    }

    void Shader::init(const char *vertexShaderSource, const char *fragmentShaderSource) {

        int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
        int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

        m_shaderProgram = glCreateProgram();

        glAttachShader(m_shaderProgram, vertexShader);
        glAttachShader(m_shaderProgram, fragmentShader);

        glLinkProgram(m_shaderProgram);
        checkProgramLinkError(m_shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

    }

    void Shader::destroy() const {
        glDeleteProgram(m_shaderProgram);
    }

    void Shader::use() const {
        glUseProgram(m_shaderProgram);
    }

    void Shader::checkShaderCompilationError(unsigned int type, unsigned int shaderID) {
        int success;
        char infoLog[512];
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);

        std::stringstream errorMessage;
        errorMessage << "Failed to compile ";
        switch (type) {
            case GL_VERTEX_SHADER: errorMessage << "vertex"; break;
            case GL_FRAGMENT_SHADER: errorMessage << "fragment"; break;
            default: errorMessage << "unknown";
        }
        errorMessage << " shader!" << std::endl;

        errorMessage << infoLog;
        BUBO_ASSERT(success, errorMessage.str())
    }

    void Shader::checkProgramLinkError(unsigned int programID) {
        int success;
        char infoLog[512];
        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);

        std::stringstream errorMessage;
        errorMessage << "Failed to compile shader program!" << std::endl;
        errorMessage << infoLog;

        BUBO_ASSERT(success, errorMessage.str())
    }

    std::string Shader::parseShader(const char *filepath) {
        std::stringstream source;
        std::fstream stream(filepath);
        std::string line;
        while (getline(stream, line)) {
            source << line << std::endl;
        }
        return source.str();
    }

}
