#include "renderer/Camera.h"

#include <core/Input.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#define NORMALIZE_IF_NOT_ZERO(vector) { if (vector != glm::vec3(0.0f)) { vector = glm::normalize(vector); } }

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

    void PerspectiveCamera::setPerspective(float fov, float aspect, float near, float far) {
        m_projection = glm::perspective(glm::radians(fov), aspect, near, far);
        updateViewProjection();
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

    PerspectiveCameraController::PerspectiveCameraController(const float cameraSpeed,
                                                             const float sensitivity,
                                                             const float dumping)
            : m_camera(45.0f, 800.0f / 600.0f, 0.1f, 100.0f),
              m_cameraSpeed(cameraSpeed),
              m_cameraSensitivity(sensitivity),
              m_dumping(dumping) {
        m_targetPosition = glm::vec3(m_camera.getPosition().x, m_camera.getPosition().y, m_camera.getPosition().z);
        m_targetYaw = m_camera.getYaw();
        m_targetPitch = m_camera.getPitch();
    }

    PerspectiveCameraController::PerspectiveCameraController(const PerspectiveCamera &camera,
                                                             const float cameraSpeed,
                                                             const float sensitivity,
                                                             const float dumping)
            : m_camera(camera),
              m_cameraSpeed(cameraSpeed),
              m_cameraSensitivity(sensitivity),
              m_dumping(dumping) {
        m_targetPosition = glm::vec3(m_camera.getPosition().x, m_camera.getPosition().y, m_camera.getPosition().z);
        m_targetYaw = m_camera.getYaw();
        m_targetPitch = m_camera.getPitch();
    }

    void PerspectiveCameraController::onKeyPressed(float deltaTime) {
        glm::vec3 direction(0.0f);

        if (Input::isKeyPressed(KEY_S)) {
            direction -= m_camera.getForward();
            NORMALIZE_IF_NOT_ZERO(direction);
        }
        if (Input::isKeyPressed(KEY_W)) {
            direction += m_camera.getForward();
            NORMALIZE_IF_NOT_ZERO(direction);
        }
        if (Input::isKeyPressed(KEY_A)) {
            direction -= m_camera.getRight();
            NORMALIZE_IF_NOT_ZERO(direction);
        }
        if (Input::isKeyPressed(KEY_D)) {
            direction += m_camera.getRight();
            NORMALIZE_IF_NOT_ZERO(direction);
        }
        if (Input::isKeyPressed(KEY_Q)) {
            direction -= m_camera.getUp();
            NORMALIZE_IF_NOT_ZERO(direction);
        }
        if (Input::isKeyPressed(KEY_E)) {
            direction += m_camera.getUp();
            NORMALIZE_IF_NOT_ZERO(direction);
        }

        m_targetPosition += direction * m_cameraSpeed * deltaTime;

    }

    void PerspectiveCameraController::onMouseMoved(float deltaX, float deltaY, float deltaTime) {

        m_targetYaw   += deltaX * m_cameraSensitivity * deltaTime;
        m_targetPitch += deltaY * m_cameraSensitivity * deltaTime;

#if 0
        if (m_targetYaw == 0.0f) {
            m_targetYaw = 0.1f;
        }
        if (m_targetPitch == 0.0f) {
            m_targetPitch = 0.1f;
        }
#endif

        if (m_targetPitch > 89.0f) {
            m_targetPitch = 89.0f;
        }
        if (m_targetPitch < -89.0f) {
            m_targetPitch = -89.0f;
        }

    }

    void PerspectiveCameraController::onUpdate(float deltaTime) {

        onKeyPressed(deltaTime);

        m_camera.setPosition(glm::mix(m_camera.getPosition(), m_targetPosition, m_dumping * deltaTime));
        m_camera.setYawPitch(glm::mix(m_camera.getYaw(), m_targetYaw, 0.5f * m_dumping * deltaTime),
                             glm::mix(m_camera.getPitch(), m_targetPitch, 0.5f * m_dumping * deltaTime));

        m_camera.updateViewProjection();

    }

    void PerspectiveCameraController::setPerspective(float fov, float aspect, float near, float far) {
        m_camera.setPerspective(fov, aspect, near, far);
    }

}
