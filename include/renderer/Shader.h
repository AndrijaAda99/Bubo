#ifndef BUBO_SHADER_H
#define BUBO_SHADER_H

namespace bubo {

    class Shader {
    public:
        Shader(const char *vertexShaderPath, const char *fragmentShaderPath);
        ~Shader();

        void use() const;

    private:
        void init(const char *shaderSrc, const char *fragmentSrc);
        void destroy() const;

        static std::string parseShader(const char *filepath);

        int compileShader(unsigned int type, const char* shaderSource);
        void checkShaderCompilationError(unsigned int type, unsigned int shaderID);
        void checkProgramLinkError(unsigned int programID);

    private:
        int m_shaderProgram = 0;

    };

}

#endif //BUBO_SHADER_H
