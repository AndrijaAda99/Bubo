#ifndef BUBO_LIGHTS_H
#define BUBO_LIGHTS_H

#include <glm/vec3.hpp>
#include <renderer/Shader.h>

namespace bubo {

    class DirectionalLight {
    public:
        DirectionalLight();
        ~DirectionalLight() = default;

        const glm::vec3 &getDirection() const { return m_direction; }
        const glm::vec3 &getAmbient() const { return m_ambient; }
        const glm::vec3 &getDiffuse() const { return m_diffuse; }
        const glm::vec3 &getSpecular() const { return m_specular; }

        void setDirection(const glm::vec3 &direction) { m_direction = direction; }
        void setAmbient(const glm::vec3 &ambient) { m_ambient = ambient; }
        void setDiffuse(const glm::vec3 &diffuse) { m_diffuse = diffuse; }
        void setSpecular(const glm::vec3 &specular) { m_specular = specular; }

    private:
        void makeDefaultDirectionalLight();

    private:
        glm::vec3 m_direction;

        glm::vec3 m_ambient;
        glm::vec3 m_diffuse;
        glm::vec3 m_specular;

    };

    class PointLight {
    public:
        PointLight();
        ~PointLight() = default;

        const glm::vec3 &getPosition() const { return m_position; }
        const glm::vec3 &getAmbient() const { return m_ambient; }
        const glm::vec3 &getDiffuse() const { return m_diffuse; }
        const glm::vec3 &getSpecular() const { return m_specular; }

        const float getConstantFactor() const { return m_constant; }
        const float getLinearFactor() const { return m_linear; }
        const float getQuadraticFactor() const { return m_quadratic; }

        void setPosition(const glm::vec3 &position) { m_position = position; }
        void setAmbient(const glm::vec3 &ambient) { m_ambient = ambient; }
        void setDiffuse(const glm::vec3 &diffuse) { m_diffuse = diffuse; }
        void setSpecular(const glm::vec3 &specular) { m_specular = specular; }

        void setConstantFactor(const float constant) { m_constant = constant; }
        void setLinearFactor(const float linear) { m_linear = linear; }
        void setQuadraticFactor(const float quadratic) { m_quadratic = quadratic; }

    private:
        void makeRandomPointLight();

    private:
        glm::vec3 m_position;

        glm::vec3 m_ambient;
        glm::vec3 m_diffuse;
        glm::vec3 m_specular;

        float m_constant;
        float m_linear;
        float m_quadratic;

    };

    class Lights {
    public:
        static void init(const unsigned int numOfPointLights);
        static void destroy();

        static void onUpdate(const float currentTime, const float deltaTime);
        static const DirectionalLight &getDirectionalLight() { return s_lights->directionalLight; }
        static const std::vector<PointLight> &getPointLights() { return s_lights->pointLights; }

        static unsigned int getNumOfPointLights();

    private:
        struct Lights_t {
            DirectionalLight directionalLight;
            std::vector<PointLight> pointLights;
        };

        static std::unique_ptr<Lights_t> s_lights;

    };


}

#endif //BUBO_LIGHTS_H
