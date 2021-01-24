#include <glm/glm.hpp>
#include "scene/Lights.h"

namespace bubo {

    std::unique_ptr<Lights::Lights_t> Lights::s_lights = std::make_unique<Lights::Lights_t>();

    DirectionalLight::DirectionalLight() {
        makeDefaultDirectionalLight();
    }

    void DirectionalLight::makeDefaultDirectionalLight() {
        m_direction = glm::vec3(-1.0f, -1.0f, -1.0f);
        m_ambient = glm::vec3(0.2f, 0.2f, 0.2f);
        m_diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
        m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    PointLight::PointLight() {
        makeRandomPointLight();
    }

    void PointLight::makeRandomPointLight() {
        m_position = glm::vec3(10.0f * (rand() / (float) RAND_MAX),
                               10.0f * (rand() / (float) RAND_MAX),
                               10.0f * (rand() / (float) RAND_MAX - 25.0f));

        m_ambient = glm::vec3(0.02f, 0.02f, 0.02f);
        m_diffuse = glm::vec3(0.9f * (rand() / (float) RAND_MAX),
                              0.9f * (rand() / (float) RAND_MAX),
                              0.9f * (rand() / (float) RAND_MAX));
        m_specular = glm::vec3(0.1f, 0.1f, 0.1f);

        m_constant = 1.0f;
        m_linear = 0.07;
        m_quadratic = 0.017f;
    }

    void Lights::init(const unsigned int numOfPointLights) {
        srand(2);

        s_lights->directionalLight = DirectionalLight();
        s_lights->pointLights.resize(numOfPointLights);
        for (int i = 0; i < numOfPointLights; ++i) {
            s_lights->pointLights[i] = PointLight();
        }
    }

    void Lights::destroy() {
        s_lights.reset();
    }

    void Lights::onUpdate(const float currentTime, const float deltaTime) {
        s_lights->directionalLight.setDirection(glm::vec3(sin(currentTime), -1.0f, cos(currentTime)));
    }

    unsigned int Lights::getNumOfPointLights() {
        return s_lights.get()->pointLights.size();
    }

}
