#include "renderer/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace bubo {

    PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far) {
        m_projection = glm::perspective(glm::radians(fov), aspect, near, far);
        updateViewProjection();
    }

    void PerspectiveCamera::updateViewProjection() {
        glm::vec3 newForward;
        newForward.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
        newForward.y = sin(glm::radians(m_pitch));
        newForward.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));

        m_forward = glm::normalize(newForward);
        m_right = glm::normalize(glm::cross(m_forward, glm::vec3(0.0f, 1.0f, 0.0f)));
        m_up = glm::cross(m_right, m_forward);

        m_view = glm::lookAt(m_position, m_position + m_forward, m_up);
        m_viewProjection = m_projection * m_view;
    }

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) {
        m_projection = glm::ortho(left, right, bottom, top);
        updateViewProjection();
    }

    void OrthographicCamera::updateViewProjection() {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) *
                              glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0, 0, 1));
        m_view = glm::inverse(transform);

        m_viewProjection = m_projection * m_view;
    }

}
